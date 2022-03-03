#include "piece_movement_manager.h"
#include "tile_manager.h"

bool PieceMovementManager::checkMovePossibility(const Piece* piece, const CoordinatesToPiecesMapping& coordinatesToPiecesMapping, const Coordinates& targetTileCoordinates)
{
    if(TileManager::isTileEmpty(targetTileCoordinates, coordinatesToPiecesMapping))
    {
        /*Check if this movement is one of possible movements*/
        std::vector<Coordinates> moveOptions = generatePossiblePieceMovementOptionsCoordinates(piece);
        return std::find(moveOptions.begin(), moveOptions.end(), targetTileCoordinates) != moveOptions.end();
    }
    else
    {
        return false;
    }
}

std::vector<Piece*> PieceMovementManager::whichPiecesCanMove(Player activePlayer, const CoordinatesToPiecesMapping& coordinatesToPiecesMapping)
{
    std::vector<Piece*> piecesWhichCanMove;

    for(auto& coordinatesToPiecesPair: coordinatesToPiecesMapping)
    {
        Piece* piece = coordinatesToPiecesPair.second;

        if(piece)
        {
            if(piece->getPlayer() == activePlayer)
            {
                if(checkIfPieceCanMove(piece, coordinatesToPiecesMapping))
                {
                    piecesWhichCanMove.push_back(piece);
                }
            }
        }
    }

    return piecesWhichCanMove;
}

std::vector<Coordinates> PieceMovementManager::generatePossiblePieceMovementOptionsCoordinates(const Piece* piece)
{
    const Coordinates pieceCoordinates(piece->getRow(), piece->getColumn());
    const Player piecePlayer = piece->getPlayer();
    std::vector<std::pair<int, int>> validRowColumnMovementOffsets;

    if(piecePlayer == Player::down)
    {
        /*Movement up is permitted*/
        validRowColumnMovementOffsets.emplace_back(-1, -1);
        validRowColumnMovementOffsets.emplace_back(-1, +1);

        if(piece->isPromoted())
        {
            validRowColumnMovementOffsets.emplace_back(+1, -1);
            validRowColumnMovementOffsets.emplace_back(+1, +1);
        }
    }
    else if(piecePlayer == Player::up)
        {
            /*Movement down is permitted*/
            validRowColumnMovementOffsets.emplace_back(+1, -1);
            validRowColumnMovementOffsets.emplace_back(+1, +1);

            if(piece->isPromoted())
            {
                validRowColumnMovementOffsets.emplace_back(-1, -1);
                validRowColumnMovementOffsets.emplace_back(-1, +1);
            }
        }

    std::vector<Coordinates> validMovementCoordinates;

    for(auto& validRowColumnMovementOffset : validRowColumnMovementOffsets)
    {
        if(Coordinates::validateCoordinates(pieceCoordinates.getRow() + validRowColumnMovementOffset.first,
                                            pieceCoordinates.getColumn() + validRowColumnMovementOffset.second))
        {
            validMovementCoordinates.emplace_back(pieceCoordinates.getRow() + validRowColumnMovementOffset.first,
                                                  pieceCoordinates.getColumn() + validRowColumnMovementOffset.second);
        }
    }

    return validMovementCoordinates;
}

bool PieceMovementManager::checkIfPieceCanMove(const Piece* piece, const CoordinatesToPiecesMapping& coordinatesToPiecesMapping)
{
    std::vector<Coordinates> moveOptions = generatePossiblePieceMovementOptionsCoordinates(piece);

    for(auto& moveOption: moveOptions)
    {
        if(checkMovePossibility(piece, coordinatesToPiecesMapping, moveOption))
        {
            return true;
        }
    }

    return false;
}
