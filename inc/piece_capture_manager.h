#pragma once

#include "piece.h"
#include "common.h"

namespace PieceCaptureManager
{
    std::vector<Piece*> whichPiecesCanCapture(Player activePlayer, const CoordinatesToPiecesMapping& coordinatesToPiecesMapping);
    bool checkCapturePossibility(const Piece* piece, const CoordinatesToPiecesMapping& coordinatesToPiecesMapping, const Coordinates& targetTileCoordinates);
    bool checkIfPieceCanCapture(const Piece* piece, const CoordinatesToPiecesMapping& coordinatesToPiecesMapping);
    std::vector<Coordinates> generatePossiblePieceCaptureOptionsCoordinates(const Piece* piece);
}
