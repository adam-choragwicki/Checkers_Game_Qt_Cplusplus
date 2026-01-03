#pragma once

#include "piece.h"
#include "pieces_manager.h"
#include <set>

class PieceMovementManager
{
public:
    static std::vector<Piece*> whichPiecesCanMove(const Player& activePlayer, const PiecesManager& piecesManager);
    static bool checkIfPieceCanMove(const Piece& piece, const PiecesManager& piecesManager);
    static bool checkMovePossibility(const Piece& piece, const PiecesManager& piecesManager, const Coordinates& targetTileCoordinates);

private:
    static std::set<Coordinates> generatePossiblePieceMovementOptionsCoordinates(const Piece& piece);
};
