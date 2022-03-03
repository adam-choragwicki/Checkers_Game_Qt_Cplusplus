#pragma once

#include "piece.h"
#include "common.h"

namespace PieceMovementManager
{
    std::vector<Piece*> whichPiecesCanMove(Player activePlayer, const CoordinatesToPiecesMapping& coordinatesToPiecesMapping);
    bool checkIfPieceCanMove(const Piece* piece, const CoordinatesToPiecesMapping& coordinatesToPiecesMapping);
    bool checkMovePossibility(const Piece* piece, const CoordinatesToPiecesMapping& coordinatesToPiecesMapping, const Coordinates& targetTileCoordinates);
    std::vector<Coordinates> generatePossiblePieceMovementOptionsCoordinates(const Piece* piece);
}
