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
    PlayerManager() { activePlayer_ = startingPlayer_; }
    Player& getActivePlayer() { return activePlayer_; }

    void switchPlayer()
    {
        activePlayer_ = activePlayer_ == Player::NORTH ? Player::SOUTH : Player::NORTH;
        qDebug() << "SWITCHED PLAYER TO PLAYER" << static_cast<int>(activePlayer_);
    }

private:
    Player activePlayer_;
    inline static Player startingPlayer_ = Player::SOUTH;
};
