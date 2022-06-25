#pragma once

#include "piece.h"
#include "common.h"
#include "pieces_placement.h"

namespace PieceCaptureManager
{
    QVector<Piece*> whichPiecesCanCapture(Player activePlayer, const PiecesPlacement& piecesPlacement);
    bool checkCapturePossibility(const Piece* piece, const PiecesPlacement& piecesPlacement, const Coordinates& targetTileCoordinates);
    bool checkIfPieceCanCapture(const Piece* piece, const PiecesPlacement& piecesPlacement);
    QVector<Coordinates> generatePossiblePieceCaptureOptionsCoordinates(const Piece* piece);
}
