#pragma once

#include "coordinates.h"

#include <QGraphicsRectItem>

class Tile : public QObject, public QGraphicsRectItem
{
    Q_OBJECT

public:
    Tile(Coordinates coordinates, bool playable, QGraphicsItem* parent);
    bool isPlayable() const {return playable_;}

signals:
    void clickedSignal(const Coordinates& coordinates, bool playable);

private:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void hoverMoveEvent(QGraphicsSceneHoverEvent* event) override;

    static constexpr QColor playableTileColor_{140, 90, 40};
    static constexpr QColor nonPlayableTileColor_{230, 200, 160};
    const Coordinates coordinates_;
    const bool playable_;
};
