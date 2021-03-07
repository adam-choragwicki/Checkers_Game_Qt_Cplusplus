#include "piece.h"
#include <QPen>

Piece::Piece(std::pair<int, int> coordinates, Player player)
{
    QGraphicsEllipseItem::setRect((coordinates.second - 1) * Common::TILE_SIZE + PIECE_OFFSET_X,
                                  (coordinates.first - 1) * Common::TILE_SIZE + PIECE_OFFSET_Y,
                                  PIECE_SIZE,
                                  PIECE_SIZE);

    row = coordinates.first;
    column = coordinates.second;

    if(player == Player::Down)
    {
        setBrush(BLACK_PIECE_COLOR);
        setPen(QPen(QBrush(BLACK_PIECE_OUTLINE_COLOR), PIECE_OUTLINE_WIDTH));
    }
    else if(player == Player::Up)
    {
        setBrush(RED_PIECE_COLOR);
        setPen(QPen(QBrush(RED_PIECE_OUTLINE_COLOR), PIECE_OUTLINE_WIDTH));
    }
}
