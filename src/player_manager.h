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
        else
        {
            qFatal("Invalid player");
        }

        qDebug() << "Switched player to" << activePlayer_.toString();
    }

    static const Player& getOtherPlayer(const Player& player) noexcept
    {
        if (player == SOUTH_PLAYER)
        {
            return NORTH_PLAYER;
        }

        if (player == NORTH_PLAYER)
        {
            return SOUTH_PLAYER;
        }

        qFatal("Invalid player");
    }

private:
    Player activePlayer_;
};
