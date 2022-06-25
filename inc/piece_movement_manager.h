#pragma once

#include "piece.h"
#include "common.h"
#include "pieces_placement.h"

namespace PieceMovementManager
{
    QVector<Piece*> whichPiecesCanMove(Player activePlayer, const PiecesPlacement& piecesPlacement);
    bool checkIfPieceCanMove(const Piece* piece, const PiecesPlacement& piecesPlacement);
    bool checkMovePossibility(const Piece* piece, const PiecesPlacement& piecesPlacement, const Coordinates& targetTileCoordinates);
    QVector<Coordinates> generatePossiblePieceMovementOptionsCoordinates(const Piece* piece);
}
