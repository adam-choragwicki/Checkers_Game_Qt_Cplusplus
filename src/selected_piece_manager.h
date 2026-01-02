#pragma once

#include "piece.h"
#include "piece_state_manager.h"
#include <QDebug>

class SelectedPieceManager
{
public:
    SelectedPieceManager() = delete;

    static bool isAnyPieceSelected() { return selectedPiece_ != nullptr; }

    static Piece& getSelectedPiece()
    {
        if (selectedPiece_)
        {
            return *selectedPiece_;
        }

        const QString message("Error, trying to dereference selected piece, but no piece is selected");
        qFatal() << message;
        throw std::runtime_error(message.toStdString());
    }

    static void resetSelectedPiece()
    {
        switchSelectedPiece(nullptr);
    }

    static void switchSelectedPiece(Piece* piece)
    {
        if (isAnyPieceSelected())
        {
            PieceStateManager::deselectPiece(*selectedPiece_);
        }

        selectedPiece_ = piece;
    }

private:
    inline static Piece* selectedPiece_ = nullptr;
};
