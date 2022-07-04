#pragma once

#include "piece.h"
#include "common.h"
#include "tile.h"

class Checkerboard : public QObject
{
Q_OBJECT

signals:
    void tileClickedSignal(const Coordinates& coordinates, bool playable);

public:
    Checkerboard();
    ~Checkerboard() override;
    [[nodiscard]] QVector<Tile*> getPlayableTiles() const;

private:
    void createTiles();

    QVector<Tile*> tiles_;
};
