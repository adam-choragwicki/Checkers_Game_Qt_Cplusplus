#pragma once

#include <QGraphicsRectItem>
#include "common.h"
#include "coordinates.h"

class Tile : public QObject, public QGraphicsRectItem
{
    Q_OBJECT

public:
    Tile(Coordinates coordinates, bool playable, QGraphicsItem* parent);
    bool IsPlayable() const {return m_Playable;}

signals:
    void ClickedSignal(const Coordinates& coordinates, bool playable);

private:
    static constexpr QColor BROWN_TILE_COLOR{140, 90, 40};
    static constexpr QColor WHITE_TILE_COLOR{230, 200, 160};
    const Coordinates m_Coordinates;
    const bool m_Playable;

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void hoverMoveEvent(QGraphicsSceneHoverEvent* event) override;
};
