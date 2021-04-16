#pragma once

enum class Player
{
    UP = 1,
    DOWN = 2
};

enum class TileColor
{
    BROWN = 1,
    WHITE = 2
};

class Common
{
public:
    static const int TILE_SIZE = 80;
    static Player& GetActivePlayer() {return m_ActivePlayer;}
    static void SetActivePlayer(Player newActivePlayer) {m_ActivePlayer = newActivePlayer;}

private:
    static Player m_ActivePlayer;
};
