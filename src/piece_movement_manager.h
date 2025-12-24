#pragma once

#include "piece.h"
#include "common.h"
#include "pieces_manager.h"
#include <set>

namespace PieceMovementManager
{
    std::vector<Piece*> whichPiecesCanMove(Player activePlayer, const PiecesManager& piecesPlacement);
    bool checkIfPieceCanMove(const Piece& piece, const PiecesManager& piecesPlacement);
    bool checkMovePossibility(const Piece& piece, const PiecesManager& piecesPlacement, const Coordinates& targetTileCoordinates);
    std::set<Coordinates> generatePossiblePieceMovementOptionsCoordinates(const Piece& piece);
}
