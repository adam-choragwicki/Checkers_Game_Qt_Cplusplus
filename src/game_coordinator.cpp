#include "game_coordinator.h"
#include "piece_managers/piece_movement_manager.h"
#include "piece_managers/piece_state_manager.h"
#include "piece_managers/piece_promotion_manager.h"

GameCoordinator::GameCoordinator(Model& model, QmlHelper& qmlHelper, IStateActions& stateActions) : model_(model),
                                                                                                    qmlHelper_(qmlHelper),
                                                                                                    stateActions_(stateActions),
                                                                                                    pieceStateManager_(model_.getPieceStateManager()),
                                                                                                    multiCaptureManager_(model_.getMultiCaptureManager()),
                                                                                                    piecesManager_(model_.getPiecesManager())
{
    stateActions_.setGameState(GameStateType::ReadyToStart);
}

void GameCoordinator::startGame()
{
    stateActions_.setGameState(GameStateType::Running);
    startNewTurn();
}

void GameCoordinator::restartGame()
{
    qInfo() << "Restarting game";

    QMetaObject::invokeMethod(qmlHelper_.getGameInput(), "refocus");

    model_.reset();

    turnCounter_ = 0;

    stateActions_.setGameState(GameStateType::ReadyToStart);

    startGame();
}

void GameCoordinator::checkAndMarkPlayerMoveOptions(const Player& player)
{
    // If multi capture is in progress, it has the highest priority
    if (multiCaptureManager_.isMultiCaptureInProgress())
    {
        const int multiCapturingPieceId = multiCaptureManager_.getMulticapturingPiece().getId();

        qDebug() << "Multi capture is in progress";
        qDebug().noquote() << QString("Checking if multi capturing piece %1 can capture any further piece").arg(multiCapturingPieceId);

        if (PieceCaptureManager::checkIfPieceCanCapture(multiCaptureManager_.getMulticapturingPiece(), piecesManager_))
        {
            qDebug().noquote() << QString("Multi capturing piece %1 can capture at least one more piece").arg(multiCapturingPieceId);
            // no need to do anything here, the multi-capturing piece just stays activated
            return;
        }

        qDebug().noquote() << QString("Multi capturing piece %1 cannot capture any more pieces. Ending multi capture and checking for other move options").arg(multiCapturingPieceId);
        multiCaptureManager_.endMultiCapture();
    }

    if (const std::vector<Piece*> piecesWhichCanCapture = PieceCaptureManager::whichPiecesCanCapture(player, piecesManager_); piecesWhichCanCapture.empty())
    {
        qDebug().noquote() << QString("%1 has no pieces which can capture").arg(player.toString());

        if (const std::vector<Piece*> piecesWhichCanMove = PieceMovementManager::whichPiecesCanMove(player, piecesManager_); piecesWhichCanMove.empty())
        {
            qDebug().noquote() << QString("%1 has no pieces which can move, game over").arg(player.toString());
            endGame(model_.getPlayerManager().getActivePlayer(), GameEndReason::NO_MOVES_LEFT);
        }
        else
        {
            qDebug().noquote() << QString("%1 has %2 pieces which can move").arg(player.toString()).arg(piecesWhichCanMove.size());
            piecesManager_.markPiecesWhichCanMove(piecesWhichCanMove);
        }
    }
    else
    {
        qDebug().noquote() << QString("%1 has %2 pieces which can capture").arg(player.toString(), piecesWhichCanCapture.size());
        piecesManager_.markPiecesWhichCanMove(piecesWhichCanCapture);
    }
}

void GameCoordinator::processPieceClicked(const int pieceId)
{
    if (Piece* piece = piecesManager_.findPieceById(pieceId))
    {
        Q_ASSERT(pieceId == piece->getId());

        pieceStateManager_.onPieceClicked(*piece);
    }
    else
    {
        qFatal("Piece with id %d not found", pieceId);
    }
}

void GameCoordinator::processTileClicked(const Coordinates& targetTileCoordinates)
{
    /*Ignore clicking on a tile unless any piece is selected*/
    if (pieceStateManager_.isAnyPieceSelected())
    {
        Piece& selectedPiece = pieceStateManager_.getSelectedPiece();

        if (const Coordinates selectedPieceCoordinates = selectedPiece.getCoordinates(); selectedPieceCoordinates == targetTileCoordinates)
        {
            qDebug().noquote() << QString("C++: Ignoring click on tile %1 because the selected piece is on it").arg(targetTileCoordinates);
            return;
        }

        // If a move is already happening, ignore input
        if (model_.isMoveInProgress())
        {
            return;
        }

        // Lock the input. It will be unlocked after the animation finishes or if the move is rejected
        model_.setMoveInProgress(true);
        bool moveAccepted = false;
        bool moveIsCapture = false;
        std::optional<std::reference_wrapper<Piece>> victimPiece;

        /*If any capture is possible, then any capture has to be the next move*/
        if (PieceCaptureManager::checkIfPieceCanCapture(selectedPiece, piecesManager_))
        {
            if (PieceCaptureManager::checkCapturePossibility(selectedPiece, piecesManager_, targetTileCoordinates))
            {
                // Calculate victim piece coordinates BEFORE moving the attacking piece
                const Coordinates victimPieceCoordinates = getCapturedPieceCoordinates(selectedPiece, targetTileCoordinates);

                // Find the victim piece
                if (piecesManager_.isPieceAtCoordinates(victimPieceCoordinates))
                {
                    victimPiece = piecesManager_.getPieceAtCoordinates(victimPieceCoordinates);
                }

                moveIsCapture = true;
                moveAccepted = true;
            }
            else
            {
                qDebug().noquote() << QString("C++: Invalid capture attempt - piece %1 can capture, but this particular capture by moving to %2 is illegal").arg(selectedPiece.getId()).arg(targetTileCoordinates);
                pieceStateManager_.deselectPiece(selectedPiece);
                model_.setMoveInProgress(false);
                return;
            }
        }
        // Check if a normal move is possible
        else if (PieceMovementManager::checkIfPieceCanMove(selectedPiece, piecesManager_))
        {
            if (PieceMovementManager::checkMovePossibility(selectedPiece, piecesManager_, targetTileCoordinates))
            {
                moveAccepted = true;
            }
            else
            {
                qDebug().noquote() << QString("C++: Invalid move attempt - piece %1 can move, but this particular move to %2 is illegal").arg(selectedPiece.getId()).arg(targetTileCoordinates);
                pieceStateManager_.deselectPiece(selectedPiece);
                model_.setMoveInProgress(false);
                return;
            }
        }

        if (moveAccepted)
        {
            if (moveIsCapture)
            {
                model_.getPieceMovementAnimationManager()->setDoublePieceMovementAnimationDuration();
            }
            else
            {
                model_.getPieceMovementAnimationManager()->setBasicPieceMovementAnimationDuration();
            }

            // update logical position
            movePieceToCoordinates(selectedPiece, targetTileCoordinates);

            Piece* piecePtr = &selectedPiece;

            model_.getPieceMovementAnimationManager()->start([this, piecePtr, moveIsCapture, victimPiece]()
            {
                onPieceAnimationFinished(piecePtr, moveIsCapture, victimPiece);
            });
        }
        else
        {
            qDebug().noquote() << QString("C++: Ignoring click on tile %1 because move from %2 to %1 is illegal").arg(targetTileCoordinates).arg(selectedPiece.getCoordinates());
        }
    }
    else
    {
        qDebug().noquote() << QString("C++: Ignoring click on tile %1 because no piece is selected").arg(targetTileCoordinates);
    }
}

void GameCoordinator::onPieceAnimationFinished(Piece* piece, const bool movementWasCapture, const std::optional<std::reference_wrapper<Piece>> capturedPiece)
{
    if (movementWasCapture && capturedPiece)
    {
        piecesManager_.killPiece(*capturedPiece); // kill the specific piece identified earlier
    }

    // 2. Run the rules logic
    if (movementWasCapture)
    {
        if (checkEligibilityAndPromotePiece(*piece))
        {
            multiCaptureManager_.endMultiCapture();
            endTurn();
        }
        else if (PieceCaptureManager::checkIfPieceCanCapture(*piece, piecesManager_))
        {
            // Multi-capture available
            multiCaptureManager_.startMultiCapture(*piece);
            piecesManager_.disableAllButOnePiece(*piece); // keep the multi-capturing piece selected
        }
        else
        {
            endTurn();
        }
    }
    else // Normal move
    {
        checkEligibilityAndPromotePiece(*piece);
        endTurn();
    }

    model_.setMoveInProgress(false); // unlock input
}

Coordinates GameCoordinator::getCapturedPieceCoordinates(const Piece& piece, const Coordinates& targetTileCoordinates) const
{
    // This math is only correct if 'piece' is still at the START position
    return Coordinates((targetTileCoordinates.getRow() + piece.getRow()) / 2, (targetTileCoordinates.getColumn() + piece.getColumn()) / 2);
}

void GameCoordinator::startNewTurn()
{
    ++turnCounter_;
    qDebug() << QString("================================ START TURN %1 ================================").arg(turnCounter_);
    checkAndMarkPlayerMoveOptions(model_.getPlayerManager().getActivePlayer());
}

void GameCoordinator::movePieceToCoordinates(Piece& piece, const Coordinates& targetTileCoordinates)
{
    piece.moveToCoordinates(targetTileCoordinates);
}

void GameCoordinator::endTurn()
{
    qDebug() << QString("=================================== END TURN %1 ===================================").arg(turnCounter_);

    if (piecesManager_.didAnyPlayerRunOutOfPieces())
    {
        const Player& playerWithNoPiecesLeft = piecesManager_.getPlayerWithNoPiecesLeft();

        qDebug() << playerWithNoPiecesLeft.toString() << "has no pieces left";
        endGame(playerWithNoPiecesLeft, GameEndReason::NO_PIECES_LEFT);
        return;
    }

    piecesManager_.disableAllPieces();
    model_.getPlayerManager().switchPlayer();
    pieceStateManager_.resetSelectedPiece();

    startNewTurn();
}

bool GameCoordinator::checkEligibilityAndPromotePiece(Piece& piece)
{
    if (PiecePromotionManager::checkPromotionEligibility(piece))
    {
        piece.promote();
        qDebug().noquote() << QString("Piece %1 has been promoted").arg(piece.getId());
        return true;
    }

    return false;
}

void GameCoordinator::endGame(const Player& losingPlayer, const GameEndReason gameEndReason)
{
    // NOTE the function accepts LOSING player as a parameter
    QString gameEndReasonText;

    if (gameEndReason == GameEndReason::NO_MOVES_LEFT)
    {
        gameEndReasonText = losingPlayer.getColor().toUpper() + " player has no moves left";
    }
    else if (gameEndReason == GameEndReason::NO_PIECES_LEFT)
    {
        gameEndReasonText = losingPlayer.getColor().toUpper() + " player has no pieces left";
    }
    else
    {
        Q_UNREACHABLE();
    }

    qInfo().noquote() << "Game over, reason:" << gameEndReasonText;

    const Player winningPlayer = model_.getPlayerManager().getOtherPlayer(losingPlayer);

    model_.setGameResultInfo(winningPlayer, gameEndReasonText);

    if (losingPlayer == SOUTH_PLAYER)
    {
        stateActions_.setGameState(GameStateType::EndedVictoryNorthPlayer);
    }
    else if (losingPlayer == NORTH_PLAYER)
    {
        stateActions_.setGameState(GameStateType::EndedVictorySouthPlayer);
    }
    else
    {
        Q_UNREACHABLE();
    }
}
