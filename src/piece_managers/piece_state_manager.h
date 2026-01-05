#pragma once

#include "../piece.h"

class PieceStateManager
{
public:
    void reset();

    void onPieceClicked(Piece& piece);

    void activatePiece(Piece& piece);
    void selectPiece(Piece& piece);
    void disablePiece(Piece& piece);

    bool isAnyPieceSelected() const;
    Piece& getSelectedPiece() const;
    void resetSelectedPiece();
    void deselectPiece(Piece& piece);

private:
    void switchSelectedPiece(Piece& piece);

    std::optional<std::reference_wrapper<Piece>> selectedPiece_;
};
