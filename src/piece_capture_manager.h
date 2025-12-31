#pragma once

#include "piece.h"
#include "game_end_reason.h"
#include "pieces_manager.h"
#include <set>

namespace PieceCaptureManager
{
    std::vector<Piece*> whichPiecesCanCapture(Player activePlayer, const PiecesManager& piecesManager);
    bool checkCapturePossibility(const Piece& piece, const PiecesManager& piecesManager, const Coordinates& targetTileCoordinates);
    bool checkIfPieceCanCapture(const Piece& piece, const PiecesManager& piecesManager);
    std::set<Coordinates> generatePossiblePieceCaptureOptionsCoordinates(const Piece& piece);
}
