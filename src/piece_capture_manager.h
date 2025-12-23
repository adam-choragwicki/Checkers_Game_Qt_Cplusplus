#pragma once

#include "piece.h"
#include "common.h"
#include "pieces_placement.h"
#include <set>

namespace PieceCaptureManager
{
    std::vector<Piece*> whichPiecesCanCapture(Player activePlayer, const PiecesPlacement& piecesPlacement);
    bool checkCapturePossibility(const Piece& piece, const PiecesPlacement& piecesPlacement, const Coordinates& targetTileCoordinates);
    bool checkIfPieceCanCapture(const Piece& piece, const PiecesPlacement& piecesPlacement);
    std::set<Coordinates> generatePossiblePieceCaptureOptionsCoordinates(const Piece& piece);
}
