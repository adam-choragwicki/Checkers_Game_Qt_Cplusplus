#pragma once

#include <QGraphicsEllipseItem>
#include "common.h"

class Piece : public QGraphicsEllipseItem
{
public:
    Piece(std::pair<int, int> coordinates, PLAYER player);
private:
    int row;
    int column;
};
