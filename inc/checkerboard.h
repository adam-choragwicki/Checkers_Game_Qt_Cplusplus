#pragma once

#include "piece.h"
#include "common.h"
#include "tile.h"

class Checkerboard : public QObject, public QGraphicsRectItem
{
Q_OBJECT

signals:
    void tileClickedSignal(const Coordinates& coordinates, bool playable);

public:
    Checkerboard();
    ~Checkerboard() override;
    [[nodiscard]] const QVector<Tile*>& getPlayableTiles() const {return playableTiles_;}

private:
    void createTiles();

    const int boardPositionX_ = 0;
    const int boardPositionY_ = 0;
    const int boardSize_ = 640;
    const int boardOutlineWidth_ = 10;
    const QColor boardOutlineColor_{150, 100, 40};

    QVector<Tile*> playableTiles_;
};
