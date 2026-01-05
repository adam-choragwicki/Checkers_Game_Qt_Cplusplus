#include "piece_state_manager.h"
#include <QDebug>

void PieceStateManager::reset()
{
    resetSelectedPiece();
}

void PieceStateManager::resetSelectedPiece()
{
    selectedPiece_.reset();
}

Piece& PieceStateManager::getSelectedPiece() const
{
    if (!selectedPiece_)
    {
        qFatal("Error, trying to dereference selected piece, but no piece is selected");
    }

    return selectedPiece_->get();
}

void PieceStateManager::switchSelectedPiece(Piece& piece)
{
    Q_ASSERT(selectedPiece_->get().getState() == Piece::State::SELECTED);

    deselectPiece(selectedPiece_->get());

    selectedPiece_ = piece;
}

void PieceStateManager::onPieceClicked(Piece& piece)
{
    if (piece.getState() == Piece::State::ACTIVE)
    {
        if (selectedPiece_.has_value())
        {
            // Another piece is already in SELECTED state, it needs to be degraded to ACTIVE state before setting a new piece to SELECTED state
            switchSelectedPiece(piece);
        }

        piece.setState(Piece::State::SELECTED);
        selectedPiece_ = piece;
    }
    else
    {
        qDebug() << "C++: Ignoring click on piece" << piece.getId() << "because it is not active";
    }
}

void PieceStateManager::selectPiece(Piece& piece)
{
    piece.setState(Piece::State::SELECTED);
}

void PieceStateManager::deselectPiece(Piece& piece)
{
    Q_ASSERT(piece.getState() == Piece::State::SELECTED);
    piece.setState(Piece::State::ACTIVE);
    resetSelectedPiece();
}

void PieceStateManager::disablePiece(Piece& piece)
{
    if (piece.getState() != Piece::State::DISABLED)
    {
        piece.setState(Piece::State::DISABLED);
    }
}

void PieceStateManager::activatePiece(Piece& piece)
{
    piece.setState(Piece::State::ACTIVE);
}

bool PieceStateManager::isAnyPieceSelected() const
{
    return selectedPiece_.has_value();
}
