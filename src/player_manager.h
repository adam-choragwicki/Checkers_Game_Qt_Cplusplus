#pragma once

#include "player.h"
#include <QDebug>

class PlayerManager
{
public:
    PlayerManager() : activePlayer_(SOUTH_PLAYER)
    {}

    void reset() noexcept
    {
        activePlayer_ = SOUTH_PLAYER;
    }

    const Player& getActivePlayer() const noexcept { return activePlayer_; }

    void switchPlayer() noexcept
    {
        if (activePlayer_ == SOUTH_PLAYER)
        {
            activePlayer_ = NORTH_PLAYER;
        }
        else if (activePlayer_ == NORTH_PLAYER)
        {
            activePlayer_ = SOUTH_PLAYER;
        }

        qDebug() << "Switched player to" << activePlayer_.toString();
    }

private:
    Player activePlayer_;
};
