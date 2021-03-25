#include "tile.h"
#include <QPen>
#include <QGraphicsSceneMouseEvent>
#include "checkerboard.h"

Tile::Tile(int row, int column, QGraphicsItem* parent) : QGraphicsRectItem(parent), m_Coordinates(row, column)
{
    QGraphicsRectItem::setRect((column - 1) * Common::TILE_SIZE,
                               (row - 1) * Common::TILE_SIZE,
                               Common::TILE_SIZE,
                               Common::TILE_SIZE);

    if(row % 2 == 0)
    {
        m_Playable = false;
        column % 2 == 0 ? setBrush(QBrush(WHITE_TILE_COLOR)) : setBrush(QBrush(BROWN_TILE_COLOR));
    }
    else
    {
        m_Playable = true;
        column % 2 == 0 ? setBrush(QBrush(BROWN_TILE_COLOR)) : setBrush(QBrush(WHITE_TILE_COLOR));
    }

    //TODO
    if(brush() == QBrush(BROWN_TILE_COLOR))
    {
        m_Playable = true;
    }
    else
    {
        m_Playable = false;
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
