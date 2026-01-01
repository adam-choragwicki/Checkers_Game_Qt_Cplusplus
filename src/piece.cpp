#include "piece.h"
#include "selected_piece_manager.h"
#include <QDebug>

Piece::Piece(const Coordinates& coordinates, const Player player, const bool promoted) : STARTING_COORDINATES_(coordinates), coordinates_(coordinates), player_(player)
{
    state_ = State::DISABLED;

    if (promoted)
    {
        promote();
    }

    id_ = instanceCounter_++;

    // qDebug() << "Piece created:" << id_;
}

void Piece::reset()
{
    coordinates_ = STARTING_COORDINATES_;
    alive_ = true;
    promoted_ = false;
    state_ = State::DISABLED;

    emit pieceChanged(id_);
}

void Piece::setState(const State newState)
{
    auto handleIllegalStateTransition = [this, newState]()
    {
        throw std::runtime_error("Error, unsupported piece state transition from state " + std::to_string(static_cast<int>(state_)) + " to state " + std::to_string(static_cast<int>(newState)) + "");
    };

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
            handleIllegalStateTransition();
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
        else if (newState == State::ACTIVE)
        {
            /* Do nothing */
        }
        else
        {
            handleIllegalStateTransition();
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
            handleIllegalStateTransition();
        }
    }
    else
    {
        Q_UNREACHABLE();
    }

    state_ = newState;

    qDebug() << "C++: Piece" << id_ << "state changed to" << static_cast<int>(state_);

    // qDebug() << "C++: Piece" << id_ << " Emitting pieceChanged signal";

    emit pieceChanged(id_); // TODO only state changes here
}

void Piece::setAnimationEnabled(const bool enabled)
{
    animationEnabled_ = enabled;
    emit pieceChanged(id_);
}

void Piece::onClicked()
{
    if (state_ == State::ACTIVE)
    {
        qDebug() << "C++: Setting piece" << id_ << "as selected";
        setState(State::SELECTED);
    }
    else
    {
        qDebug() << "C++: Ignoring click on piece" << id_ << "because it is not active";
    }
}

void Piece::moveToCoordinates(const Coordinates& newCoordinates)
{
    qDebug() << "C++: Moving piece" << id_ << "to coordinates" << newCoordinates;

    coordinates_ = newCoordinates;

    emit pieceChanged(id_);
}

void Piece::promote()
{
    promoted_ = true;
    emit pieceChanged(id_);
}

std::ostream& operator<<(std::ostream& os, const Piece& piece)
{
    os << "(" << piece.getRow() << "," << piece.getColumn() << ")";
    return os;
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

void Piece::setAlive(const bool alive)
{
    alive_ = alive;
    emit pieceChanged(id_);
}
