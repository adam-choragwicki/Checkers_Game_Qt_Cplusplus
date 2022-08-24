#pragma once

enum class Player
{
    up = 1,
    down = 2
};

class PlayerManager
{
public:
    PlayerManager() {activePlayer_ = startingPlayer_;}
    Player& getActivePlayer() {return activePlayer_;}
    void switchPlayer() { activePlayer_ = (activePlayer_ == Player::up) ? Player::down : Player::up;}

private:
    Player activePlayer_;
    inline static Player startingPlayer_ = Player::down;
};
