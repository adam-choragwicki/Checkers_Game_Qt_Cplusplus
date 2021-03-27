#pragma once

#include <QGraphicsRectItem>
#include "common.h"
#include "coordinates.h"

class Tile : public QGraphicsRectItem
{
public:
    Tile(int row, int column, bool playable, QGraphicsItem* parent);
    bool IsPlayable() const {return m_Playable;}

private:
    static constexpr QColor BROWN_TILE_COLOR{140, 90, 40};
    static constexpr QColor WHITE_TILE_COLOR{230, 200, 160};
    const Coordinates m_Coordinates;
    const bool m_Playable;

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
};
