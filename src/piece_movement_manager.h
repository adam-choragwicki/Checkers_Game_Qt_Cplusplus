#pragma once

#include "piece.h"
#include "pieces_manager.h"
#include <set>

namespace PieceMovementManager
{
    std::vector<Piece*> whichPiecesCanMove(Player activePlayer, const PiecesManager& piecesManager);
    bool checkIfPieceCanMove(const Piece& piece, const PiecesManager& piecesManager);
    bool checkMovePossibility(const Piece& piece, const PiecesManager& piecesManager, const Coordinates& targetTileCoordinates);
    std::set<Coordinates> generatePossiblePieceMovementOptionsCoordinates(const Piece& piece);
}
