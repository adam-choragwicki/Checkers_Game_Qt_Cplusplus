#include "tile.h"
#include <QPen>

Tile::Tile(int row, int column)
{
    QGraphicsRectItem::setRect(row * Common::TILE_SIZE,
                               column * Common::TILE_SIZE,
                               Common::TILE_SIZE,
                               Common::TILE_SIZE);

    if(row % 2 == 0)
    {
        column % 2 == 0 ? setBrush(QBrush(WHITE_TILE_COLOR)) : setBrush(QBrush(BROWN_TILE_COLOR));
    }
    else
    {
        column % 2 == 0 ? setBrush(QBrush(BROWN_TILE_COLOR)) : setBrush(QBrush(WHITE_TILE_COLOR));
    }

    setPen(QPen(brush().color()));
}
