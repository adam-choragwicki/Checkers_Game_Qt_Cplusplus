#include "game_engine.h"
#include "logic.h"
#include "tile.h"
#include "piece.h"
#include "log_manager.h"
#include "active_piece_manager.h"

GameEngine::GameEngine()
{
    QObject::connect(&checkerboard_, &Checkerboard::tileClickedSignal, this, &GameEngine::processTileClickedSlot);
    startGame();
}

void GameEngine::startGame()
{
    logFile << "NEW GAME" << std::endl;

    PlayerManager::resetActivePlayer();

    checkerboard_.createAllPieces();

    checkAndMarkPlayerMoveOptions(PlayerManager::getActivePlayer());
}

void GameEngine::clearPreviousGame()
{
    checkerboard_.removeAllPieces();

    Piece* activePiece = ActivePieceManager::getActivePiece();

    if(activePiece)
    {
        activePiece->setActiveState(false);
    }
}

void GameEngine::restartGame()
{
    clearPreviousGame();
    startGame();
}

void GameEngine::checkAndMarkPlayerMoveOptions(Player player)
{
    if(isMultiCaptureInProgress())
    {
        return;
    }

    std::vector<Piece*> piecesWhichCanCapture = logic::whichPiecesCanCapture(player, checkerboard_.getCoordinatesToPiecesMapping());

    if(piecesWhichCanCapture.empty())
    {
        std::vector<Piece*> piecesWhichCanMove = logic::whichPiecesCanMove(player, checkerboard_.getCoordinatesToPiecesMapping());
        checkerboard_.markPiecesWhichCanMove(piecesWhichCanMove);
    }
    else
    {
        checkerboard_.markPiecesWhichCanMove(piecesWhichCanCapture);
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
    if(logic::checkIfPieceCanCapture(activePiece, checkerboard_.getCoordinatesToPiecesMapping()))
    {
        if(logic::checkCapturePossibility(activePiece, checkerboard_.getCoordinatesToPiecesMapping(), targetTileCoordinates))
        {
            capturePiece(activePiece, targetTileCoordinates);

            if(logic::checkIfPieceCanCapture(activePiece, checkerboard_.getCoordinatesToPiecesMapping()))
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
    else if(logic::checkIfPieceCanMove(activePiece, checkerboard_.getCoordinatesToPiecesMapping()))
    {
        if(logic::checkMovePossibility(activePiece, checkerboard_.getCoordinatesToPiecesMapping(), targetTileCoordinates))
        {
            movePiece(activePiece, targetTileCoordinates);

            checkEligibilityAndPromotePiece(activePiece);

            activePiece->setActiveState(false);
            endTurn();
        }
    }
    else
    {
        throw std::logic_error("ERROR, PIECE CANNOT CAPTURE AND CANNOT MOVE");
    }

    emit sceneUpdateSignal();
}

void GameEngine::unmarkAllPieces()
{
    for(auto& coordinatesToPiecesPair : checkerboard_.getCoordinatesToPiecesMapping())
    {
        Piece* piece = coordinatesToPiecesPair.second;

        if(piece && (piece->isMarkedActive() || piece->isMarkedMoveAvailable()))
        {
            piece->unmark();
        }
    }
}

void GameEngine::movePiece(Piece* piece, const Coordinates& targetTileCoordinates)
{
    logFile << piece << " moves to " << targetTileCoordinates << std::endl;

    Coordinates pieceCoordinates(piece->getRow(), piece->getColumn());

    checkerboard_.getCoordinatesToPiecesMapping()[pieceCoordinates] = nullptr;
    checkerboard_.getCoordinatesToPiecesMapping()[targetTileCoordinates] = piece;
    piece->moveToTile(targetTileCoordinates);
}

void GameEngine::capturePiece(Piece* piece, const Coordinates& targetTileCoordinates)
{
    Coordinates coordinatesOfPieceBetween((targetTileCoordinates.getRow() + piece->getRow()) / 2, (targetTileCoordinates.getColumn() + piece->getColumn()) / 2);

    logFile << piece << " captures " << coordinatesOfPieceBetween << " and lands on " << targetTileCoordinates << std::endl;

    movePiece(piece, targetTileCoordinates);
    delete checkerboard_.getCoordinatesToPiecesMapping().at(coordinatesOfPieceBetween);
    checkerboard_.getCoordinatesToPiecesMapping()[coordinatesOfPieceBetween] = nullptr;
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
    if(logic::checkPromotionEligibility(piece))
    {
        piece->promote();
    }
}

bool GameEngine::isMultiCaptureInProgress()
{
    return multiCaptureInProgressPiece_ != nullptr;
}

void GameEngine::processNewGameButtonClicked()
{
    restartGame();
}
