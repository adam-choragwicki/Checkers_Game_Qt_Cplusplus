#include "piece_movement_manager.h"

bool PieceMovementManager::checkMovePossibility(const Piece& piece, const PiecesManager& piecesPlacement, const Coordinates& targetTileCoordinates)
{
    if(!piecesPlacement.isPieceAtCoordinates(targetTileCoordinates))
    {
        /*Check if this movement is one of possible movements*/
        std::set<Coordinates> moveOptions = generatePossiblePieceMovementOptionsCoordinates(piece);
        return moveOptions.contains(targetTileCoordinates);
    }
    else
    {
        return false;
    }
}

std::vector<Piece*> PieceMovementManager::whichPiecesCanMove(Player activePlayer, const PiecesManager& piecesPlacement)
{
    std::vector<Piece*> piecesWhichCanMove;

    for(const auto& piece : piecesPlacement.getPieces())
    {
        if(piece->getPlayer() == activePlayer)
        {
            if(checkIfPieceCanMove(*piece, piecesPlacement))
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

    if(piece.isPromoted())
    {
        validRowColumnMovementOffsets = {{-1, -1},
                                         {-1, +1},
                                         {+1, -1},
                                         {+1, +1}};
    }
    else
    {
        if(piecePlayer == Player::SOUTH)
        {
            /*Movement UP is permitted*/
            validRowColumnMovementOffsets = {{-1, -1},
                                             {-1, +1}};
        }
        else if(piecePlayer == Player::NORTH)
        {
            /*Movement DOWN is permitted*/
            validRowColumnMovementOffsets = {{+1, -1},
                                             {+1, +1}};
        }
    }

    const Coordinates pieceCoordinates = piece.getCoordinates();
    std::set<Coordinates> validMovementCoordinates;

    for(auto& validRowColumnMovementOffset : validRowColumnMovementOffsets)
    {
        if(Coordinates::validateCoordinates(pieceCoordinates + validRowColumnMovementOffset))
        {
            validMovementCoordinates.emplace(pieceCoordinates + validRowColumnMovementOffset);
        }
    }

    return validMovementCoordinates;
}

bool PieceMovementManager::checkIfPieceCanMove(const Piece& piece, const PiecesManager& piecesPlacement)
{
    std::set<Coordinates> moveOptions = generatePossiblePieceMovementOptionsCoordinates(piece);

    return std::ranges::any_of(moveOptions, [&piece, &piecesPlacement](const Coordinates& moveOption)
    {
        return checkMovePossibility(piece, piecesPlacement, moveOption);
    });
}
