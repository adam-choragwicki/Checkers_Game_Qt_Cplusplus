#include "piece.h"
#include <QDebug>

Piece::Piece(const Coordinates& coordinates, const Player& player, const bool promoted) : STARTING_COORDINATES_(coordinates), coordinates_(coordinates), player_(player)
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
    state_ = newState;

    qDebug().noquote() << "C++: Player" << player_.toString() << "piece" << id_ << "state changed to" << QMetaEnum::fromType<State>().valueToKey(static_cast<int>(state_));

    emit pieceChanged(id_);
}

void Piece::setAnimationEnabled(const bool enabled)
{
    animationEnabled_ = enabled;
    emit pieceChanged(id_);
}

bool Piece::operator==(const Piece& other) const
{
    return id_ == other.id_;
}

void Piece::moveToCoordinates(const Coordinates& newCoordinates)
{
    qDebug().noquote() << "C++: Moving piece" << id_ << "to coordinates" << newCoordinates;

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

void Piece::setAlive(const bool alive)
{
    alive_ = alive;
    emit pieceChanged(id_);
}
