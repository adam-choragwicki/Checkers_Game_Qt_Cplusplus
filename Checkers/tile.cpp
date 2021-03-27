#include "tile.h"
#include <QPen>
#include <QGraphicsSceneMouseEvent>
#include "checkerboard.h"

Tile::Tile(int row, int column, bool playable, QGraphicsItem* parent) : QGraphicsRectItem(parent), m_Coordinates(row, column), m_Playable(playable)
{
    QGraphicsRectItem::setRect((column - 1) * Common::TILE_SIZE,
                               (row - 1) * Common::TILE_SIZE,
                               Common::TILE_SIZE,
                               Common::TILE_SIZE);

    if(m_Playable)
    {
        setBrush(QBrush(BROWN_TILE_COLOR));
    }
    else
    {
        setBrush(QBrush(WHITE_TILE_COLOR));
    }

    setPen(QPen(brush().color()));
}

void Tile::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if(event->button() == Qt::MouseButton::LeftButton)
    {
        Checkerboard::ProcessTileClicked(m_Coordinates.Row(), m_Coordinates.Column(), m_Playable);
    }
}
