#include "tile.h"
#include "common.h"
#include "drawer.h"

#include <QPen>
#include <QGraphicsSceneMouseEvent>

Tile::Tile(Coordinates coordinates, bool playable) : coordinates_(coordinates.getRow(), coordinates.getColumn()), isPlayable_(playable)
{
    QGraphicsRectItem::setRect(coordinates.getColumn() * GameParameters::tileSize,
                               coordinates.getRow() * GameParameters::tileSize,
                               GameParameters::tileSize,
                               GameParameters::tileSize);

    if(isPlayable_)
    {
        setBrush(QBrush(playableTileColor_));
    }
    else
    {
        setBrush(QBrush(nonPlayableTileColor_));
    }

    setPen(QPen(brush().color()));
    setAcceptHoverEvents(true);

    Drawer::drawItem(this);
}

Tile::~Tile()
{
    Drawer::eraseItem(this);
}

void Tile::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if(event->button() == Qt::MouseButton::LeftButton)
    {
        emit clickedSignal(coordinates_, isPlayable_);
    }
}

void Tile::hoverMoveEvent(QGraphicsSceneHoverEvent* event)
{
    setToolTip(QString::number(coordinates_.getRow()) + "," + QString::number(coordinates_.getColumn()));
}
