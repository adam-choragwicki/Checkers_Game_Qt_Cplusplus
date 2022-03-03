#pragma once

enum class Player
{
    up = 1,
    down = 2
};

class PlayerManager
{
public:
    static Player& getActivePlayer() {return activePlayer_;}
    static void setActivePlayer(Player activePlayer) {activePlayer_ = activePlayer;}
    static void resetActivePlayer() {activePlayer_ = Player::down;}

private:
    /*Player::down starts*/
    inline static Player activePlayer_ = Player::down;
};
