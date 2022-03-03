#include "tile.h"
#include "common.h"

#include <QPen>
#include <QGraphicsSceneMouseEvent>

Tile::Tile(Coordinates coordinates, bool playable, QGraphicsItem* parent) : QGraphicsRectItem(parent), coordinates_(coordinates.getRow(), coordinates.getColumn()), playable_(playable)
{
    QGraphicsRectItem::setRect((coordinates.getColumn() - 1) * Common::tileSize,
                               (coordinates.getRow() - 1) * Common::tileSize,
                               Common::tileSize,
                               Common::tileSize);

    if(playable_)
    {
        setBrush(QBrush(playableTileColor_));
    }
    else
    {
        setBrush(QBrush(nonPlayableTileColor_));
    }

    setPen(QPen(brush().color()));
    setAcceptHoverEvents(true);
}

void Tile::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if(event->button() == Qt::MouseButton::LeftButton)
    {
        emit clickedSignal(coordinates_, playable_);
    }
}

void Tile::hoverMoveEvent(QGraphicsSceneHoverEvent* event)
{
    setToolTip(QString::number(coordinates_.getRow()) + "," + QString::number(coordinates_.getColumn()));
}
