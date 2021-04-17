#include "tile.h"
#include <QPen>
#include <QGraphicsSceneMouseEvent>

Tile::Tile(Coordinates coordinates, bool playable, QGraphicsItem* parent) : QGraphicsRectItem(parent), m_Coordinates(coordinates.Row(), coordinates.Column()), m_Playable(playable)
{
    QGraphicsRectItem::setRect((coordinates.Column() - 1) * Common::TILE_SIZE,
                               (coordinates.Row() - 1) * Common::TILE_SIZE,
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
    setAcceptHoverEvents(true);
}

void Tile::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if(event->button() == Qt::MouseButton::LeftButton)
    {
        emit ClickedSignal(m_Coordinates, m_Playable);
    }
}

void Tile::hoverMoveEvent(QGraphicsSceneHoverEvent* event)
{
    setToolTip(QString::number(m_Coordinates.Row()) + "," + QString::number(m_Coordinates.Column()));
}
