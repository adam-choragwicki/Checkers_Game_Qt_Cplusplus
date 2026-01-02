#pragma once

#include "piece.h"
#include "piece_state_manager.h"

class SelectedPieceManager
{
public:
    SelectedPieceManager() = delete;

    static bool isAnyPieceSelected() { return selectedPiece_.has_value(); }

    static Piece& getSelectedPiece()
    {
        if (!selectedPiece_)
        {
            qFatal("Error, trying to dereference selected piece, but no piece is selected");
        }

        return selectedPiece_->get();
    }

    static void resetSelectedPiece()
    {
        selectedPiece_.reset();
    }

    static void switchSelectedPiece(Piece& piece)
    {
        if (selectedPiece_)
        {
            PieceStateManager::deselectPiece(selectedPiece_->get());
        }

        selectedPiece_ = piece;
    }

private:
    inline static std::optional<std::reference_wrapper<Piece>> selectedPiece_;
};
