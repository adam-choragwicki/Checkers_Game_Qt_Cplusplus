#pragma once

#include <QString>

class Player
{
public:
    enum class Position : int { North = 1, South = 2 };

    Player(const Position position_, const QString& color_) noexcept : position(position_), color(color_)
    {}

    QString toString() const
    {
        return position == Position::North ? QStringLiteral("NORTH PLAYER") : QStringLiteral("SOUTH PLAYER");
    }

    QString getColor() const noexcept // TODO not used, convey color to QML eventually
    {
        return color;
    }

    int toInt() const noexcept
    {
        return static_cast<int>(position);
    }

    // comparisons
    bool operator==(const Player& other) const
    {
        return position == other.position;
    }

    bool operator!=(const Player& other) const
    {
        return !(*this == other);
    }

private:
    Position position;
    QString color;
};

// global (immutable) player descriptors — cheap to copy, stable lifetime
inline const Player NORTH_PLAYER{Player::Position::North, QStringLiteral("red")};
inline const Player SOUTH_PLAYER{Player::Position::South, QStringLiteral("black")};
