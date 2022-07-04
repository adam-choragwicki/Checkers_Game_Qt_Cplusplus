#pragma once

#include "coordinates.h"

#include <QGraphicsRectItem>

class Tile : public QObject, public QGraphicsRectItem
{
Q_OBJECT

signals:
    void clickedSignal(const Coordinates& coordinates, bool playable);

public:
    Tile(Coordinates coordinates, bool playable);
    ~Tile() override;

    [[nodiscard]] bool isPlayable() const {return isPlayable_;}

private:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void hoverMoveEvent(QGraphicsSceneHoverEvent* event) override;

    static constexpr QColor playableTileColor_{140, 90, 40};
    static constexpr QColor nonPlayableTileColor_{230, 200, 160};
    const Coordinates coordinates_;
    const bool isPlayable_;
};
