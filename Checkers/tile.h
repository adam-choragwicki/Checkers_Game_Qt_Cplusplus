#pragma once

#include <QGraphicsRectItem>
#include "common.h"

class Tile : public QGraphicsRectItem
{
public:
    Tile(int row, int column);

private:
    const QColor BROWN_TILE_COLOR{140, 90, 40};
    const QColor WHITE_TILE_COLOR{230, 200, 160};
};
