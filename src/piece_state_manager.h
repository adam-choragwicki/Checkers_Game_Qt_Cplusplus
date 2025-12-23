#pragma once

#include "piece.h"

class PieceStateManager
{
public:
    static void selectPiece(Piece& piece);
    static void deselectPiece(Piece& piece);
    static void disablePiece(Piece& piece);
    static void markPieceHasValidMovePossible(Piece& piece);
};
