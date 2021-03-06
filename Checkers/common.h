#pragma once

#include <QColor>

enum PLAYER
{
    PLAYER_UPPER = 1,
    PLAYER_LOWER = 2
};

const int TILE_SIZE = 80;
const int PIECE_OFFSET_X = 15;
const int PIECE_OFFSET_Y = 15;
const int PIECE_SIZE = 50;
const int PIECE_OUTLINE_WIDTH = 6;

const QColor BLACK_PIECE_COLOR(50, 50, 50);
const QColor BLACK_PIECE_OUTLINE_COLOR(0, 0, 0);
const QColor RED_PIECE_COLOR(220, 0, 0);
const QColor RED_PIECE_OUTLINE_COLOR(170, 0, 0);
