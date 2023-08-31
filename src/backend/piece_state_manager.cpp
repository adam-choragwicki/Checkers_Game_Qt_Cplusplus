#include "piece_state_manager.h"

void PieceStateManager::selectPiece(Piece& piece)
{
    piece.setSelected();
}

void PieceStateManager::deselectPiece(Piece& piece)
{
    piece.setActive();
}

void PieceStateManager::disablePiece(Piece& piece)
{
    piece.setDisabled();
}

void PieceStateManager::markPieceHasValidMovePossible(Piece& piece)
{
    piece.setActive();
}
