#pragma once

enum class Player
{
    UPPER = 1,
    LOWER = 2
};

class PlayerManager
{
public:
    PlayerManager() {activePlayer_ = startingPlayer_;}
    Player& getActivePlayer() {return activePlayer_;}
    void switchPlayer() { activePlayer_ = (activePlayer_ == Player::UPPER) ? Player::LOWER : Player::UPPER;}

private:
    Player activePlayer_;
    inline static Player startingPlayer_ = Player::LOWER;
};
