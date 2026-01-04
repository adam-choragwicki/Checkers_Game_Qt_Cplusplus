#include "game_coordinator.h"
#include "piece_movement_manager.h"
#include "piece_state_manager.h"
#include "piece_promotion_manager.h"
#include "selected_piece_manager.h"

GameCoordinator::GameCoordinator(const GameConfig& gameConfig, Model& model, QmlHelper& qmlHelper, IStateActions& stateActions) : model_(model), qmlHelper_(qmlHelper), stateActions_(stateActions)
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
    if (model_.getMultiCaptureManager().isMultiCaptureInProgress())
    {
        qDebug() << "Multi capture in progress";

        if (PieceCaptureManager::checkIfPieceCanCapture(model_.getMultiCaptureManager().getMulticapturingPiece(), model_.getPiecesManager()))
        {
            const std::vector piecesWhichCanCapture{&model_.getMultiCaptureManager().getMulticapturingPiece()};
            model_.getPiecesManager().markPiecesWhichCanMove(piecesWhichCanCapture);
            return;
        }

        model_.getMultiCaptureManager().endMultiCapture();
    }

    if (const std::vector<Piece*> piecesWhichCanCapture = PieceCaptureManager::whichPiecesCanCapture(player, model_.getPiecesManager()); piecesWhichCanCapture.empty())
    {
        qDebug().noquote() << player.toString() << "has no pieces which can capture";

        if (const std::vector<Piece*> piecesWhichCanMove = PieceMovementManager::whichPiecesCanMove(player, model_.getPiecesManager()); piecesWhichCanMove.empty())
        {
            qDebug().noquote() << player.toString() << "has no pieces which can move, game over";
            endGame(model_.getPlayerManager().getActivePlayer(), GameEndReason::NO_MOVES_LEFT);
        }
        else
        {
            qDebug().noquote() << player.toString() << "has pieces which can move";
            model_.getPiecesManager().markPiecesWhichCanMove(piecesWhichCanMove);
        }
    }
    else
    {
        qDebug().noquote() << player.toString() << "has pieces which can capture";
        model_.getPiecesManager().markPiecesWhichCanMove(piecesWhichCanCapture);
    }
}

void GameCoordinator::processTileClicked(const Coordinates& targetTileCoordinates)
{
    /*Ignore clicking on a tile unless any piece is selected*/
    if (SelectedPieceManager::isAnyPieceSelected())
    {
        Piece& selectedPiece = SelectedPieceManager::getSelectedPiece();

        // If a move is already happening, ignore input
        if (model_.isMoveInProgress())
        {
            return;
        }

        // Lock the input. It will be unlocked after the animation finishes
        model_.setMoveInProgress(true);
        bool moveAccepted = false;
        bool movementIsCapture = false;
        std::optional<std::reference_wrapper<Piece>> victimPiece;

        /*If any capture is possible, then any capture has to be the next move*/
        if (PieceCaptureManager::checkIfPieceCanCapture(selectedPiece, model_.getPiecesManager()))
        {
            if (PieceCaptureManager::checkCapturePossibility(selectedPiece, model_.getPiecesManager(), targetTileCoordinates))
            {
                // Calculate victim piece coordinates BEFORE moving the attacking piece
                const Coordinates victimCoordinates = getCapturedPieceCoordinates(selectedPiece, targetTileCoordinates);

                // Find the victim piece
                if (model_.getPiecesManager().isPieceAtCoordinates(victimCoordinates))
                {
                    victimPiece = model_.getPiecesManager().getPieceAtCoordinates(victimCoordinates);
                }

                movementIsCapture = true;
                moveAccepted = true;
            }
            else
            {
                // Invalid capture attempt // TODO should I do something more here?
                PieceStateManager::deselectPiece(selectedPiece);
                model_.setMoveInProgress(false);
                return;
            }
        }
        // Check if a normal move is possible
        else if (PieceMovementManager::checkIfPieceCanMove(selectedPiece, model_.getPiecesManager()))
        {
            if (PieceMovementManager::checkMovePossibility(selectedPiece, model_.getPiecesManager(), targetTileCoordinates))
            {
                moveAccepted = true;
            }
        }

        if (moveAccepted)
        {
            if (movementIsCapture)
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

            model_.getPieceMovementAnimationManager()->start([this, piecePtr, movementIsCapture, victimPiece]()
            {
                onPieceAnimationFinished(piecePtr, movementIsCapture, victimPiece);
            });
        }
        else
        {
            throw std::runtime_error("Error, piece is in undefined state, cannot capture and cannot move");
        }
    }
}

void GameCoordinator::onPieceAnimationFinished(Piece* piece, const bool movementWasCapture, const std::optional<std::reference_wrapper<Piece>> capturedPiece)
{
    if (movementWasCapture && capturedPiece)
    {
        model_.getPiecesManager().killPiece(*capturedPiece); // kill the specific piece identified earlier
    }

    // 2. Run the rules logic
    if (movementWasCapture)
    {
        if (checkEligibilityAndPromotePiece(*piece))
        {
            model_.getMultiCaptureManager().endMultiCapture();
            endTurn();
        }
        else if (PieceCaptureManager::checkIfPieceCanCapture(*piece, model_.getPiecesManager()))
        {
            // Multi-capture available
            model_.getMultiCaptureManager().startMultiCapture(*piece);
            model_.getPiecesManager().disableAllPieces();
            checkAndMarkPlayerMoveOptions(model_.getPlayerManager().getActivePlayer());
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

    if (model_.getPiecesManager().didAnyPlayerRunOutOfPieces())
    {
        const Player& playerWithNoPiecesLeft = model_.getPiecesManager().getPlayerWithNoPiecesLeft();

        qDebug() << playerWithNoPiecesLeft.toString() << "has no pieces left";
        endGame(playerWithNoPiecesLeft, GameEndReason::NO_PIECES_LEFT);
        return;
    }

    model_.getPiecesManager().disableAllPieces();
    model_.getPlayerManager().switchPlayer();

    startNewTurn();
}

bool GameCoordinator::checkEligibilityAndPromotePiece(Piece& piece)
{
    if (PiecePromotionManager::checkPromotionEligibility(piece))
    {
        piece.promote();
        qDebug() << "Piece" << piece.getId() << "has been promoted";
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
