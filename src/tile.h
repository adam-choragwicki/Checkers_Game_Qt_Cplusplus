#pragma once

#include "coordinates.h"
#include <QGraphicsRectItem>

class Tile : public QGraphicsRectItem
{
public:
    explicit Tile(const Coordinates& coordinates);
    ~Tile() override = 0;

    void hoverMoveEvent(QGraphicsSceneHoverEvent* event) override;

protected:
    const Coordinates coordinates_;
};

class NonPlayableTile : public Tile
{
public:
    explicit NonPlayableTile(const Coordinates& coordinates);
    ~NonPlayableTile() override = default;
};

class PlayableTile : public QObject, public Tile
{
Q_OBJECT

signals:
    void clickedSignal(const Coordinates& coordinates);

public:
    explicit PlayableTile(const Coordinates& coordinates);
    ~PlayableTile() override = default;

private:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
};
