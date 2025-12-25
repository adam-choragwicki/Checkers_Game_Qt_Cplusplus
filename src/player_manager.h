#pragma once

#include <QDebug>

enum class Player
{
    UPPER = 1,
    LOWER = 2
};

class PlayerManager
{
public:
    PlayerManager() { activePlayer_ = startingPlayer_; }
    Player& getActivePlayer() { return activePlayer_; }

    void switchPlayer()
    {
        activePlayer_ = activePlayer_ == Player::UPPER ? Player::LOWER : Player::UPPER;
        qDebug() << "SWITCHED PLAYER TO PLAYER" << static_cast<int>(activePlayer_);
    }

private:
    Player activePlayer_;
    inline static Player startingPlayer_ = Player::LOWER;
};
