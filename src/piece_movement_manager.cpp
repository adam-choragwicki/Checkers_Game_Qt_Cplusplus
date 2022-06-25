#include "piece_movement_manager.h"
#include "tile_manager.h"

bool PieceMovementManager::checkMovePossibility(const Piece* piece, const PiecesPlacement& piecesPlacement, const Coordinates& targetTileCoordinates)
{
    if(TileManager::isTileEmpty(targetTileCoordinates, piecesPlacement))
    {
        /*Check if this movement is one of possible movements*/
        QVector<Coordinates> moveOptions = generatePossiblePieceMovementOptionsCoordinates(piece);
        return moveOptions.contains(targetTileCoordinates);
    }
    else
    {
        return false;
    }
}

QVector<Piece*> PieceMovementManager::whichPiecesCanMove(Player activePlayer, const PiecesPlacement& piecesPlacement)
{
    QVector<Piece*> piecesWhichCanMove;

    for(auto& piece: piecesPlacement.getPieces())
    {
        if(piece->getPlayer() == activePlayer)
        {
            if(checkIfPieceCanMove(piece, piecesPlacement))
            {
                piecesWhichCanMove.push_back(piece);
            }
        }
    }

    return piecesWhichCanMove;
}

QVector<Coordinates> PieceMovementManager::generatePossiblePieceMovementOptionsCoordinates(const Piece* piece)
{
    const Player piecePlayer = piece->getPlayer();
    QVector<std::pair<int, int>> validRowColumnMovementOffsets;

    if(piece->isPromoted())
    {
        validRowColumnMovementOffsets = {{-1, -1}, {-1, +1}, {+1, -1}, {+1, +1}};
    }
    else
    {
        if(piecePlayer == Player::down)
        {
            /*Movement up is permitted*/
            validRowColumnMovementOffsets = {{-1, -1}, {-1, +1}};
        }
        else if(piecePlayer == Player::up)
        {
            /*Movement down is permitted*/
            validRowColumnMovementOffsets = {{+1, -1}, {+1, +1}};
        }
    }

    const Coordinates pieceCoordinates = piece->getCoordinates();
    QVector<Coordinates> validMovementCoordinates;

    for(auto& validRowColumnMovementOffset: validRowColumnMovementOffsets)
    {
        if(Coordinates::validateCoordinates(pieceCoordinates + validRowColumnMovementOffset))
        {
            validMovementCoordinates.emplace_back(pieceCoordinates + validRowColumnMovementOffset);
        }
    }

    return validMovementCoordinates;
}

bool PieceMovementManager::checkIfPieceCanMove(const Piece* piece, const PiecesPlacement& piecesPlacement)
{
    QVector<Coordinates> moveOptions = generatePossiblePieceMovementOptionsCoordinates(piece);

    return std::ranges::any_of(moveOptions, [&piece, &piecesPlacement](const Coordinates& moveOption)
    {
        return checkMovePossibility(piece, piecesPlacement, moveOption);
    });
}
