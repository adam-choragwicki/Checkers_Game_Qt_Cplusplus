#include "game_engine.h"
#include "tile.h"
#include "piece.h"
#include "log_manager.h"
#include "active_piece_manager.h"
#include "piece_capture_manager.h"
#include "piece_movement_manager.h"
#include "piece_promotion_manager.h"

GameEngine::GameEngine(const QVector<Tile*>& playableTiles)
{
    for(Tile* playableTile : playableTiles)
    {
        QObject::connect(playableTile, &Tile::clickedSignal, this, &GameEngine::processTileClickedSlot);
    }

    logFile << "NEW GAME" << std::endl;

    PlayerManager::resetActivePlayer();

    piecesPlacement_.createAllPieces();

    checkAndMarkPlayerMoveOptions(PlayerManager::getActivePlayer());
}

void GameEngine::checkAndMarkPlayerMoveOptions(Player player)
{
    if(isMultiCaptureInProgress())
    {
        return;
    }

    QVector<Piece*> piecesWhichCanCapture = PieceCaptureManager::whichPiecesCanCapture(player, piecesPlacement_);

    if(piecesWhichCanCapture.empty())
    {
        QVector<Piece*> piecesWhichCanMove = PieceMovementManager::whichPiecesCanMove(player, piecesPlacement_);
        piecesPlacement_.markPiecesWhichCanMove(piecesWhichCanMove);
    }
    else
    {
        piecesPlacement_.markPiecesWhichCanMove(piecesWhichCanCapture);
    }
}

void GameEngine::processTileClickedSlot(const Coordinates& targetTileCoordinates)
{
    Piece* activePiece = ActivePieceManager::getActivePiece();

    if(activePiece)
    {
        processMove(targetTileCoordinates);
        activePiece->setActiveState(false);
    }

    unmarkAllPieces();

    if(isMultiCaptureInProgress())
    {
        multiCaptureInProgressPiece_->setActiveState(true);
    }
    else
    {
        unmarkAllPieces();
        checkAndMarkPlayerMoveOptions(PlayerManager::getActivePlayer());
    }
}

void GameEngine::processMove(const Coordinates& targetTileCoordinates)
{
    Piece* activePiece = ActivePieceManager::getActivePiece();

    /*If any capture is possible then any capture has to be the next move*/
    if(PieceCaptureManager::checkIfPieceCanCapture(activePiece, piecesPlacement_))
    {
        if(PieceCaptureManager::checkCapturePossibility(activePiece, piecesPlacement_, targetTileCoordinates))
        {
            capturePiece(activePiece, targetTileCoordinates);

            if(PieceCaptureManager::checkIfPieceCanCapture(activePiece, piecesPlacement_))
            {
                multiCaptureInProgressPiece_ = activePiece;
                return;
            }
            else
            {
                multiCaptureInProgressPiece_ = nullptr;
                activePiece->setActiveState(false);
            }

            checkEligibilityAndPromotePiece(activePiece);

            activePiece->setActiveState(false);
            endTurn();
        }
        else
        {
            /*Capture was possible but player chose other tile so no move was taken and active piece is reset*/
            activePiece->setActiveState(false);
            return;
        }
    }
    else if(PieceMovementManager::checkIfPieceCanMove(activePiece, piecesPlacement_))
    {
        if(PieceMovementManager::checkMovePossibility(activePiece, piecesPlacement_, targetTileCoordinates))
        {
            movePiece(activePiece, targetTileCoordinates);

            checkEligibilityAndPromotePiece(activePiece);

            activePiece->setActiveState(false);
            endTurn();
        }
    }
    else
    {
        throw std::runtime_error("Piece is in undefined state, cannot capture and cannot move");
    }

    emit sceneUpdateSignal();
}

void GameEngine::unmarkAllPieces()
{
    for(const auto& piece : piecesPlacement_.getPieces())
    {
        if(piece->isMarkedActive() || piece->isMarkedMoveAvailable())
        {
            piece->unmark();
        }
    }
}

void GameEngine::movePiece(Piece* piece, const Coordinates& targetTileCoordinates)
{
    logFile << piece << " moves to " << targetTileCoordinates << std::endl;
    piece->moveToTile(targetTileCoordinates);
}

void GameEngine::capturePiece(Piece* piece, const Coordinates& targetTileCoordinates)
{
    Coordinates coordinatesOfPieceBetween((targetTileCoordinates.getRow() + piece->getRow()) / 2, (targetTileCoordinates.getColumn() + piece->getColumn()) / 2);

    logFile << piece << " captures " << coordinatesOfPieceBetween << " and lands on " << targetTileCoordinates << std::endl;

    movePiece(piece, targetTileCoordinates);

    piecesPlacement_.removePieceAtCoordinates(coordinatesOfPieceBetween);
}

void GameEngine::endTurn()
{
    if(PlayerManager::getActivePlayer() == Player::down)
    {
        PlayerManager::setActivePlayer(Player::up);
    }
    else if(PlayerManager::getActivePlayer() == Player::up)
    {
        PlayerManager::setActivePlayer(Player::down);
    }
}

void GameEngine::checkEligibilityAndPromotePiece(Piece* piece)
{
    if(PiecePromotionManager::checkPromotionEligibility(piece))
    {
        piece->promote();
    }
}

bool GameEngine::isMultiCaptureInProgress()
{
    return multiCaptureInProgressPiece_ != nullptr;
}
