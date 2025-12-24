#pragma once

#include "piece.h"
#include "common.h"
#include "pieces_manager.h"
#include <set>

namespace PieceCaptureManager
{
    std::vector<Piece*> whichPiecesCanCapture(Player activePlayer, const PiecesManager& piecesPlacement);
    bool checkCapturePossibility(const Piece& piece, const PiecesManager& piecesPlacement, const Coordinates& targetTileCoordinates);
    bool checkIfPieceCanCapture(const Piece& piece, const PiecesManager& piecesPlacement);
    std::set<Coordinates> generatePossiblePieceCaptureOptionsCoordinates(const Piece& piece);
}
