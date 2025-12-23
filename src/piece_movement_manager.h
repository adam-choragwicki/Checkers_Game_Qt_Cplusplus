#pragma once

#include "piece.h"
#include "common.h"
#include "pieces_placement.h"
#include <set>

namespace PieceMovementManager
{
    std::vector<Piece*> whichPiecesCanMove(Player activePlayer, const PiecesPlacement& piecesPlacement);
    bool checkIfPieceCanMove(const Piece& piece, const PiecesPlacement& piecesPlacement);
    bool checkMovePossibility(const Piece& piece, const PiecesPlacement& piecesPlacement, const Coordinates& targetTileCoordinates);
    std::set<Coordinates> generatePossiblePieceMovementOptionsCoordinates(const Piece& piece);
}
