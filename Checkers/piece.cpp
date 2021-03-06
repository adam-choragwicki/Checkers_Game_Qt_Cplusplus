#include "piece.h"
#include <QPen>
#include <QBrush>

Piece::Piece(std::pair<int, int> coordinates, PLAYER player) :
    QGraphicsEllipseItem((coordinates.second - 1) * TILE_SIZE + PIECE_OFFSET_X,
                         (coordinates.first - 1) * TILE_SIZE + PIECE_OFFSET_Y,
                         PIECE_SIZE,
                         PIECE_SIZE)
{
    row = coordinates.first;
    column = coordinates.second;

    if(player == PLAYER_LOWER)
    {
        setBrush(BLACK_PIECE_COLOR);
        setPen(QPen(QBrush(BLACK_PIECE_OUTLINE_COLOR), PIECE_OUTLINE_WIDTH));
    }
    else if(player == PLAYER_UPPER)
    {
        setBrush(RED_PIECE_COLOR);
        setPen(QPen(QBrush(RED_PIECE_OUTLINE_COLOR), PIECE_OUTLINE_WIDTH));
    }
}
