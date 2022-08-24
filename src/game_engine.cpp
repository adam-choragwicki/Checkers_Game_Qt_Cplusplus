#include "game_engine.h"
#include "tile.h"
#include "piece.h"
#include "log_manager.h"
#include "selected_piece_manager.h"
#include "piece_capture_manager.h"
#include "piece_movement_manager.h"
#include "piece_promotion_manager.h"

GameEngine::GameEngine(const QVector<Tile*>& playableTiles)
{
    for(Tile* playableTile : playableTiles)
    {
        QObject::connect(playableTile, &Tile::clickedSignal, this, &GameEngine::processTileClickedSlot);
    }

    LOG(INFO) << "NEW GAME";

    piecesPlacement_.createAllPieces();

    checkAndMarkPlayerMoveOptions(playerManager_.getActivePlayer());
}

void GameEngine::checkAndMarkPlayerMoveOptions(Player player)
{
    if(multiCaptureManager_.isMultiCaptureInProgress())
    {
        if(PieceCaptureManager::checkIfPieceCanCapture(multiCaptureManager_.getMulticapturingPiece(), piecesPlacement_))
        {
            QVector<Piece*> piecesWhichCanCapture{multiCaptureManager_.getMulticapturingPiece()};
            piecesPlacement_.markPiecesWhichCanMove(piecesWhichCanCapture);
            return;
        }
        else
        {
            multiCaptureManager_.endMultiCapture();
        }
    }

    QVector<Piece*> piecesWhichCanCapture = PieceCaptureManager::whichPiecesCanCapture(player, piecesPlacement_);

    if(piecesWhichCanCapture.empty())
    {
        QVector<Piece*> piecesWhichCanMove = PieceMovementManager::whichPiecesCanMove(player, piecesPlacement_);

        if(piecesWhichCanMove.empty())
        {
            endGame(playerManager_.getActivePlayer(), GameEndReason::NoMovesLeft);
        }
        else
        {
            piecesPlacement_.markPiecesWhichCanMove(piecesWhichCanMove);
        }
    }
    else
    {
        piecesPlacement_.markPiecesWhichCanMove(piecesWhichCanCapture);
    }
}

void GameEngine::processTileClickedSlot(const Coordinates& targetTileCoordinates)
{
    if(!moveInProgress_)
    {
        moveInProgress_ = true;

        /*Ignore clicking on tile unless any piece is selected*/
        if(SelectedPieceManager::isAnyPieceSelected())
        {
            Piece* selectedPiece = SelectedPieceManager::getSelectedPiece();
            processPieceMove(selectedPiece, targetTileCoordinates);
        }

        emit sceneUpdateSignal();

        moveInProgress_ = false;
    }
}

void GameEngine::processPieceMove(Piece* piece, const Coordinates& targetTileCoordinates)
{
    /*If any capture is possible then any capture has to be the next move*/
    if(PieceCaptureManager::checkIfPieceCanCapture(piece, piecesPlacement_))
    {
        if(PieceCaptureManager::checkCapturePossibility(piece, piecesPlacement_, targetTileCoordinates))
        {
            capturePiece(piece, targetTileCoordinates);

            if(checkEligibilityAndPromotePiece(piece))
            {
                multiCaptureManager_.endMultiCapture();

                /*Turn ends immediately after promotion, no immediate backward capture is possible*/
                endTurn();
            }
            else if(PieceCaptureManager::checkIfPieceCanCapture(piece, piecesPlacement_))
            {
                multiCaptureManager_.startMultiCapture(piece);
                disableAllPieces();
                checkAndMarkPlayerMoveOptions(playerManager_.getActivePlayer());
            }
            else
            {
                endTurn();
            }
        }
        else
        {
            /*Capture was possible but player chose other tile so no move was taken and selected piece is reset*/
            piece->deselect();
        }
    }
    else if(PieceMovementManager::checkIfPieceCanMove(piece, piecesPlacement_))
    {
        if(PieceMovementManager::checkMovePossibility(piece, piecesPlacement_, targetTileCoordinates))
        {
            movePiece(piece, targetTileCoordinates);
            checkEligibilityAndPromotePiece(piece);
            endTurn();
        }
    }
    else
    {
        throw std::runtime_error("Piece is in undefined state, cannot capture and cannot move");
    }
}

void GameEngine::disableAllPieces()
{
    for(const auto& piece : piecesPlacement_.getPieces())
    {
        piece->disable();
    }
}

void GameEngine::movePiece(Piece* piece, const Coordinates& targetTileCoordinates)
{
    LOG(INFO) << piece << " moves to " << targetTileCoordinates;
    piece->moveToTile(targetTileCoordinates);
}

void GameEngine::capturePiece(Piece* piece, const Coordinates& targetTileCoordinates)
{
    Coordinates coordinatesOfPieceBetween((targetTileCoordinates.getRow() + piece->getRow()) / 2, (targetTileCoordinates.getColumn() + piece->getColumn()) / 2);

    LOG(INFO) << piece << " captures " << coordinatesOfPieceBetween << " and lands on " << targetTileCoordinates;

    movePiece(piece, targetTileCoordinates);

    piecesPlacement_.removePieceAtCoordinates(coordinatesOfPieceBetween);
}

void GameEngine::endTurn()
{
    if(piecesPlacement_.didAnyPlayerRunOutOfPieces())
    {
        endGame(piecesPlacement_.getPlayerWithNoPiecesLeft(), GameEndReason::NoPiecesLeft);
    }

    disableAllPieces();
    playerManager_.switchPlayer();
    checkAndMarkPlayerMoveOptions(playerManager_.getActivePlayer());
}

bool GameEngine::checkEligibilityAndPromotePiece(Piece* piece)
{
    if(PiecePromotionManager::checkPromotionEligibility(piece))
    {
        piece->promote();
        return true;
    }

    return false;
}

void GameEngine::endGame(Player losingPlayer, GameEndReason gameEndReason)
{
    emit dialogRestartGameSignal(losingPlayer, gameEndReason);
}
