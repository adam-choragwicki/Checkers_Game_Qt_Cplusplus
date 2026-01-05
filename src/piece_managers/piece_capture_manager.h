#pragma once

#include "../piece.h"
#include "../pieces_manager.h"
#include <set>

class PieceCaptureManager
{
public:
    static std::vector<Piece*> whichPiecesCanCapture(const Player& activePlayer, const PiecesManager& piecesManager);
    static bool checkIfPieceCanCapture(const Piece& piece, const PiecesManager& piecesManager);
    static bool checkCapturePossibility(const Piece& piece, const PiecesManager& piecesManager, const Coordinates& targetTileCoordinates);

private:
    static std::set<Coordinates> generatePossiblePieceCaptureOptionsCoordinates(const Piece& piece);
};
