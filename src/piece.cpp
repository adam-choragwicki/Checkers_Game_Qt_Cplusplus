#include "piece.h"
#include "selected_piece_manager.h"
#include <QDebug>

Piece::Piece(const Coordinates& coordinates, Player player, bool promoted) : coordinates_(coordinates), player_(player)
{
    state_ = State::DISABLED;

    if (promoted)
    {
        promote();
    }

    id_ = ++counter_;

    qDebug() << "Piece created:" << id_;
}

void Piece::setState(State newState)
{
    if (state_ == State::DISABLED)
    {
        if (newState == State::ACTIVE)
        {
            /* New turn */
        }
        else if (newState == State::DISABLED)
        {
            /* Do nothing */
        }
        else
        {
            throw std::runtime_error("Error, unsupported piece state transition");
        }
    }
    else if (state_ == State::ACTIVE)
    {
        if (newState == State::SELECTED)
        {
            SelectedPieceManager::switchSelectedPiece(this);
        }
        else if (newState == State::DISABLED)
        {
            /* End turn */
        }
        else if (state_ == State::ACTIVE)
        {
            /* Do nothing */
        }
        else
        {
            throw std::runtime_error("Error, unsupported piece state transition");
        }
    }
    else if (state_ == State::SELECTED)
    {
        if (newState == State::ACTIVE)
        {
            /* ACTIVE piece clicked */
        }
        else if (newState == State::DISABLED)
        {
            /* End turn */
            SelectedPieceManager::resetSelectedPiece();
        }
        else
        {
            throw std::runtime_error("Error, unsupported piece state transition");
        }
    }
    else
    {
        throw std::runtime_error("Error, piece is in unsupported state");
    }

    state_ = newState;

    qDebug() << "Piece" << id_ << "state changed to" << static_cast<int>(state_);

    emit stateChanged();
}

void Piece::moveToTile(const Coordinates& newCoordinates)
{
    emit startAnimatedMovement(coordinates_, newCoordinates);
}

void Piece::promote()
{
    promoted_ = true;
    emit promoted();
}

std::ostream& operator<<(std::ostream& os, const Piece& piece)
{
    os << "(" << piece.getRow() << "," << piece.getColumn() << ")";
    return os;
}

void Piece::processEndMovement(const Coordinates& newCoordinates)
{
    coordinates_ = newCoordinates;
}

bool Piece::isDisabled() const
{
    return state_ == State::DISABLED;
}

bool Piece::isActive() const
{
    return state_ == State::ACTIVE;
}

bool Piece::isSelected() const
{
    return state_ == State::SELECTED;
}

void Piece::setDisabled()
{
    setState(State::DISABLED);
}

void Piece::setActive()
{
    setState(State::ACTIVE);
}

void Piece::setSelected()
{
    setState(State::SELECTED);
}
