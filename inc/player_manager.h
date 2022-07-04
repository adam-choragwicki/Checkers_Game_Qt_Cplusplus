#pragma once

enum class Player
{
    up = 1,
    down = 2
};

class PlayerManager
{
public:
    PlayerManager() = delete;

    static Player& getActivePlayer() {return activePlayer_;}
    static void setActivePlayer(Player activePlayer) {activePlayer_ = activePlayer;}
    static void resetActivePlayer() {activePlayer_ = startingPlayer_;}

private:
    inline static Player activePlayer_;
    inline static Player startingPlayer_ = Player::down;
};
