#pragma once

#include "model.h"
// #include "game_loop.h"
#include "qml_helper.h"

#include "piece_capture_manager.h"
#include "piece_movement_manager.h"
#include "piece_state_manager.h"
#include "piece_promotion_manager.h"
#include "state_machine/game_state_manager.h"

class GameCoordinator : public QObject
{
    Q_OBJECT

signals:
    void endGame(Player losingPlayer, GameEndReason gameEndReason);

public:
    // explicit GameCoordinator(Model& model, GameLoop& gameLoop);
    explicit GameCoordinator(Model& model); // TODO game loop or not?

    void setQmlHelper(QmlHelper* qmlHelper);

    void startGameLoop(); // TODO remove or not?
    void stopGameLoop(); // TODO remove or not?

    void restartGame();

    void checkAndMarkPlayerMoveOptions(Player player)
    {
        if (model_.getMultiCaptureManager().isMultiCaptureInProgress())
        {
            qDebug() << "Multi capture in progress";

            if (PieceCaptureManager::checkIfPieceCanCapture(*model_.getMultiCaptureManager().getMulticapturingPiece(), model_.getPiecesManager()))
            {
                std::vector<Piece*> piecesWhichCanCapture{model_.getMultiCaptureManager().getMulticapturingPiece()};
                model_.getPiecesManager().markPiecesWhichCanMove(piecesWhichCanCapture);
                return;
            }
            else
            {
                model_.getMultiCaptureManager().endMultiCapture();
            }
        }

        std::vector<Piece*> piecesWhichCanCapture = PieceCaptureManager::whichPiecesCanCapture(player, model_.getPiecesManager());

        if (piecesWhichCanCapture.empty())
        {
            qDebug() << "Player" << static_cast<int>(player) << "has no pieces which can capture";

            std::vector<Piece*> piecesWhichCanMove = PieceMovementManager::whichPiecesCanMove(player, model_.getPiecesManager());

            if (piecesWhichCanMove.empty())
            {
                qInfo() << "Player" << static_cast<int>(player) << "has no pieces which can move, game over";
                // endGame(model_.getPlayerManager().getActivePlayer(), GameEndReason::NO_MOVES_LEFT);
                emit endGame(model_.getPlayerManager().getActivePlayer(), GameEndReason::NO_MOVES_LEFT);
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

    void processPieceMove(Piece& piece, const Coordinates& targetTileCoordinates)
    {
        /*If any capture is possible, then any capture has to be the next move*/
        if (PieceCaptureManager::checkIfPieceCanCapture(piece, model_.getPiecesManager()))
        {
            if (PieceCaptureManager::checkCapturePossibility(piece, model_.getPiecesManager(), targetTileCoordinates))
            {
                capturePiece(piece, targetTileCoordinates);

                if (checkEligibilityAndPromotePiece(piece))
                {
                    model_.getMultiCaptureManager().endMultiCapture();

                    /*Turn ends immediately after promotion, no immediate backward capture is possible*/
                    endTurn();
                }
                else if (PieceCaptureManager::checkIfPieceCanCapture(piece, model_.getPiecesManager()))
                {
                    model_.getMultiCaptureManager().startMultiCapture(piece);
                    disableAllPieces();
                    checkAndMarkPlayerMoveOptions(model_.getPlayerManager().getActivePlayer());
                }
                else
                {
                    endTurn();
                }
            }
            else
            {
                /*Capture was possible but player chose another tile, so no move was taken and a selected piece is reset*/
                PieceStateManager::deselectPiece(piece);
            }
        }
        else if (PieceMovementManager::checkIfPieceCanMove(piece, model_.getPiecesManager()))
        {
            if (PieceMovementManager::checkMovePossibility(piece, model_.getPiecesManager(), targetTileCoordinates))
            {
                movePiece(piece, targetTileCoordinates);
                checkEligibilityAndPromotePiece(piece);
                endTurn();
            }
        }
        else
        {
            throw std::runtime_error("Error, piece is in undefined state, cannot capture and cannot move");
        }
    }

    void movePiece(Piece& piece, const Coordinates& targetTileCoordinates)
    {
        piece.moveToTile(targetTileCoordinates);
    }

    void capturePiece(Piece& piece, const Coordinates& targetTileCoordinates)
    {
        Coordinates coordinatesOfPieceBetween((targetTileCoordinates.getRow() + piece.getRow()) / 2, (targetTileCoordinates.getColumn() + piece.getColumn()) / 2);

        movePiece(piece, targetTileCoordinates);

        model_.getPiecesManager().killPieceAtCoordinates(coordinatesOfPieceBetween); // TODO add delay, piece should be removed after animation is finished
        // view_.removePieceFrontendAtCoordinates(coordinatesOfPieceBetween);
    }

    void endTurn()
    {
        qDebug() << "============================================= END TURN =============================================";
        if (model_.getPiecesManager().didAnyPlayerRunOutOfPieces())
        {
            const Player playerWithNoPiecesLeft = model_.getPiecesManager().getPlayerWithNoPiecesLeft();

            qDebug() << "Player" << static_cast<int>(playerWithNoPiecesLeft) << "has no pieces left";

            // endGame(playerWithNoPiecesLeft, GameEndReason::NO_PIECES_LEFT);
            emit endGame(playerWithNoPiecesLeft, GameEndReason::NO_PIECES_LEFT);
        }

        disableAllPieces();
        model_.getPlayerManager().switchPlayer();
        checkAndMarkPlayerMoveOptions(model_.getPlayerManager().getActivePlayer());
    }

    void disableAllPieces()
    {
        for (const auto& piece: model_.getPiecesManager().getPieces())
        {
            if (!piece->isDisabled())
            {
                PieceStateManager::disablePiece(*piece);
            }
        }
    }

    bool checkEligibilityAndPromotePiece(Piece& piece)
    {
        if (PiecePromotionManager::checkPromotionEligibility(piece))
        {
            piece.promote();
            qDebug() << "Piece" << piece.getId() << "has been promoted";
            return true;
        }

        return false;
    }

private:
    Model& model_;
    // GameLoop& gameLoop_;
    QmlHelper* qmlHelper_{};
};
