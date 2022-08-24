#pragma once

#include "piece.h"

class SelectedPieceManager
{
public:
    SelectedPieceManager() = delete;

    static bool isAnyPieceSelected() {return selectedPiece_ != nullptr;}
    static Piece* getSelectedPiece() {return selectedPiece_;}

    static void resetSelectedPiece()
    {
        switchSelectedPiece(nullptr);
    }

    static void switchSelectedPiece(Piece* piece)
    {
        if(isAnyPieceSelected())
        {
            selectedPiece_->deselect();
        }

        selectedPiece_ = piece;
    }

private:
    inline static Piece* selectedPiece_ = nullptr;
};
