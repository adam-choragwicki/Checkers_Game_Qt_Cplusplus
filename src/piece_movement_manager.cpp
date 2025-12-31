#include "piece_movement_manager.h"

bool PieceMovementManager::checkMovePossibility(const Piece& piece, const PiecesManager& piecesManager, const Coordinates& targetTileCoordinates)
{
    if (!piecesManager.isPieceAtCoordinates(targetTileCoordinates))
    {
        /*Check if this movement is one of possible movements*/
        const std::set<Coordinates> moveOptions = generatePossiblePieceMovementOptionsCoordinates(piece);
        return moveOptions.contains(targetTileCoordinates);
    }

    return false;
}

std::vector<Piece*> PieceMovementManager::whichPiecesCanMove(const Player activePlayer, const PiecesManager& piecesManager)
{
    std::vector<Piece*> piecesWhichCanMove;

    for (const auto& piece: piecesManager.getPieces())
    {
        if (piece->getPlayer() == activePlayer)
        {
            if (checkIfPieceCanMove(*piece, piecesManager))
            {
                piecesWhichCanMove.push_back(piece.get());
            }
        }
    }

    return piecesWhichCanMove;
}

std::set<Coordinates> PieceMovementManager::generatePossiblePieceMovementOptionsCoordinates(const Piece& piece)
{
    const Player piecePlayer = piece.getPlayer();
    std::vector<std::pair<int, int>> validRowColumnMovementOffsets;

    if (piece.isPromoted())
    {
        validRowColumnMovementOffsets = {
            {-1, -1},
            {-1, +1},
            {+1, -1},
            {+1, +1}
        };
    }
    else
    {
        if (piecePlayer == Player::SOUTH)
        {
            /*Movement UP is permitted*/
            validRowColumnMovementOffsets = {
                {-1, -1},
                {-1, +1}
            };
        }
        else if (piecePlayer == Player::NORTH)
        {
            /*Movement DOWN is permitted*/
            validRowColumnMovementOffsets = {
                {+1, -1},
                {+1, +1}
            };
        }
    }

    const Coordinates pieceCoordinates = piece.getCoordinates();
    std::set<Coordinates> validMovementCoordinates;

    for (auto& validRowColumnMovementOffset: validRowColumnMovementOffsets)
    {
        if (Coordinates::validateCoordinates(pieceCoordinates + validRowColumnMovementOffset))
        {
            validMovementCoordinates.emplace(pieceCoordinates + validRowColumnMovementOffset);
        }
    }

    return validMovementCoordinates;
}

bool PieceMovementManager::checkIfPieceCanMove(const Piece& piece, const PiecesManager& piecesManager)
{
    std::set<Coordinates> moveOptions = generatePossiblePieceMovementOptionsCoordinates(piece);

    return std::ranges::any_of(moveOptions, [&piece, &piecesManager](const Coordinates& moveOption)
    {
        return checkMovePossibility(piece, piecesManager, moveOption);
    });
}
