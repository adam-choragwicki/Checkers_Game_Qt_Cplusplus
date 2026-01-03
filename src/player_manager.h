#pragma once

#include <QDebug>

enum class Player
{
    NORTH = 1,
    SOUTH = 2
};

class PlayerManager
{
public:
    PlayerManager()
    {
        activePlayer_ = STARTING_PLAYER;
    }

    void reset()
    {
        activePlayer_ = STARTING_PLAYER;
    }

    Player& getActivePlayer()
    {
        return activePlayer_;
    }

    void switchPlayer()
    {
        activePlayer_ = activePlayer_ == Player::NORTH ? Player::SOUTH : Player::NORTH;
        qDebug() << "SWITCHED PLAYER TO PLAYER" << static_cast<int>(activePlayer_);
    }

private:
    Player activePlayer_;
    static constexpr auto STARTING_PLAYER = Player::SOUTH;
};
