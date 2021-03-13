#pragma once

#include <QGraphicsRectItem>
#include "common.h"

class Tile : public QGraphicsRectItem
{
public:
    Tile(int row, int column);
    bool IsPlayable() {return m_Playable;}

private:
    const QColor BROWN_TILE_COLOR{140, 90, 40};
    const QColor WHITE_TILE_COLOR{230, 200, 160};

    const int m_Row;
    const int m_Column;

    bool m_Playable = false;

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
};
