#include "game_coordinator.h"
#include "piece_movement_manager.h"
#include "piece_state_manager.h"
#include "piece_promotion_manager.h"
#include "selected_piece_manager.h"

GameCoordinator::GameCoordinator(Model& model, IStateActions* stateActions) : model_(model), stateActions_(stateActions)
{
    checkAndMarkPlayerMoveOptions(model_.getPlayerManager().getActivePlayer());
}

void GameCoordinator::setQmlHelper(QmlHelper* qmlHelper)
{
    qmlHelper_ = qmlHelper;
}

void GameCoordinator::restartGame()
{
    qInfo() << "Restarting game";

    if (qmlHelper_)
    {
        // Restore keyboard focus to GameInput
        QMetaObject::invokeMethod(qmlHelper_->getGameInput(), "refocus");
    }

    model_.reset();

    checkAndMarkPlayerMoveOptions(model_.getPlayerManager().getActivePlayer());
}

void GameCoordinator::checkAndMarkPlayerMoveOptions(Player player)
{
    if (model_.getMultiCaptureManager().isMultiCaptureInProgress())
    {
        qDebug() << "Multi capture in progress";

        if (PieceCaptureManager::checkIfPieceCanCapture(*model_.getMultiCaptureManager().getMulticapturingPiece(), model_.getPiecesManager()))
        {
            const std::vector piecesWhichCanCapture{model_.getMultiCaptureManager().getMulticapturingPiece()};
            model_.getPiecesManager().markPiecesWhichCanMove(piecesWhichCanCapture);
            return;
        }

        model_.getMultiCaptureManager().endMultiCapture();
    }

    if (const std::vector<Piece*> piecesWhichCanCapture = PieceCaptureManager::whichPiecesCanCapture(player, model_.getPiecesManager()); piecesWhichCanCapture.empty())
    {
        qDebug() << "Player" << static_cast<int>(player) << "has no pieces which can capture";

        if (const std::vector<Piece*> piecesWhichCanMove = PieceMovementManager::whichPiecesCanMove(player, model_.getPiecesManager()); piecesWhichCanMove.empty())
        {
            qInfo() << "Player" << static_cast<int>(player) << "has no pieces which can move, game over";
            endGame(model_.getPlayerManager().getActivePlayer(), GameEndReason::NO_MOVES_LEFT);
        }
        else
        {
            qDebug() << "Player" << static_cast<int>(player) << "has pieces which can move";
            model_.getPiecesManager().markPiecesWhichCanMove(piecesWhichCanMove);
        }
    }
    else
    {
        qDebug() << "Player" << static_cast<int>(player) << "has pieces which can capture";
        model_.getPiecesManager().markPiecesWhichCanMove(piecesWhichCanCapture);
    }
}

void GameCoordinator::processTileClicked(const Coordinates& targetTileCoordinates)
{
    /*Ignore clicking on a tile unless any piece is selected*/
    if (SelectedPieceManager::isAnyPieceSelected())
    {
        Piece& selectedPiece = SelectedPieceManager::getSelectedPiece();

        if (!model_.isMoveInProgress())
        {
            model_.setMoveInProgress(true);

            /*If any capture is possible, then any capture has to be the next move*/
            if (PieceCaptureManager::checkIfPieceCanCapture(selectedPiece, model_.getPiecesManager()))
            {
                if (PieceCaptureManager::checkCapturePossibility(selectedPiece, model_.getPiecesManager(), targetTileCoordinates))
                {
                    capturePiece(selectedPiece, targetTileCoordinates);

                    if (checkEligibilityAndPromotePiece(selectedPiece))
                    {
                        model_.getMultiCaptureManager().endMultiCapture();

                        /*Turn ends immediately after promotion, no immediate backward capture is possible*/
                        endTurn();
                    }
                    else if (PieceCaptureManager::checkIfPieceCanCapture(selectedPiece, model_.getPiecesManager()))
                    {
                        model_.getMultiCaptureManager().startMultiCapture(selectedPiece);
                        model_.getPiecesManager().disableAllPieces();
                        checkAndMarkPlayerMoveOptions(model_.getPlayerManager().getActivePlayer());
                    }
                    else
                    {
                        endTurn();
                    }
                }
                else
                {
                    /*Capture was possible but player chose another tile, so no move was taken, and a selected piece is reset*/
                    PieceStateManager::deselectPiece(selectedPiece);
                }
            }
            else if (PieceMovementManager::checkIfPieceCanMove(selectedPiece, model_.getPiecesManager()))
            {
                if (PieceMovementManager::checkMovePossibility(selectedPiece, model_.getPiecesManager(), targetTileCoordinates))
                {
                    movePieceToCoordinates(selectedPiece, targetTileCoordinates);
                    checkEligibilityAndPromotePiece(selectedPiece);
                    endTurn();
                }
            }
            else
            {
                throw std::runtime_error("Error, piece is in undefined state, cannot capture and cannot move");
            }

            model_.setMoveInProgress(false);
        }
    }
    else
    {
        /*Ignore clicking on a tile unless any piece is selected*/
        qDebug() << "Ignoring click on a tile, because no piece is selected";
    }
}

void GameCoordinator::movePieceToCoordinates(Piece& piece, const Coordinates& targetTileCoordinates)
{
    piece.moveToCoordinates(targetTileCoordinates);
}

void GameCoordinator::capturePiece(Piece& piece, const Coordinates& targetTileCoordinates)
{
    const Coordinates coordinatesOfPieceBetween((targetTileCoordinates.getRow() + piece.getRow()) / 2, (targetTileCoordinates.getColumn() + piece.getColumn()) / 2);

    movePieceToCoordinates(piece, targetTileCoordinates);

    model_.getPiecesManager().killPieceAtCoordinates(coordinatesOfPieceBetween); // TODO add delay, piece should be removed after animation is finished
}

void GameCoordinator::endTurn()
{
    qDebug() << "============================================= END TURN =============================================";
    if (model_.getPiecesManager().didAnyPlayerRunOutOfPieces())
    {
        const Player playerWithNoPiecesLeft = model_.getPiecesManager().getPlayerWithNoPiecesLeft();

        qDebug() << "Player" << static_cast<int>(playerWithNoPiecesLeft) << "has no pieces left";
        endGame(playerWithNoPiecesLeft, GameEndReason::NO_PIECES_LEFT);
    }

    model_.getPiecesManager().disableAllPieces();
    model_.getPlayerManager().switchPlayer();
    checkAndMarkPlayerMoveOptions(model_.getPlayerManager().getActivePlayer());
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

void GameCoordinator::endGame(const Player losingPlayer, const GameEndReason gameEndReason)
{
    // NOTE the function accepts LOSING player as a parameter
    qInfo() << "Ending game";

    const QString playerString = losingPlayer == Player::SOUTH ? "SOUTH" : "NORTH";
    QString message;

    if (gameEndReason == GameEndReason::NO_MOVES_LEFT)
    {
        message = "Player " + playerString + " has no moves left";
    }
    else if (gameEndReason == GameEndReason::NO_PIECES_LEFT)
    {
        message = "Player " + playerString + " has no pieces left";
    }
    else
    {
        Q_UNREACHABLE();
    }

    qDebug() << message;
    model_.setGameEndReason(message);

    if (losingPlayer == Player::SOUTH)
    {
        stateActions_->setGameState(GameStateType::EndedVictoryNorthPlayer);
    }
    else if (losingPlayer == Player::NORTH)
    {
        stateActions_->setGameState(GameStateType::EndedVictorySouthPlayer);
    }
    else
    {
        Q_UNREACHABLE();
    }
}
