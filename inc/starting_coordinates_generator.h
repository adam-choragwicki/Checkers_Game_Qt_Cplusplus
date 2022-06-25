#pragma once

#include "common.h"
#include "coordinates.h"

#include <QVector>

namespace StartingCoordinatesGenerator
{
    QVector<Coordinates> generatePlayableTilesCoordinates();
    QVector<Coordinates> generateStartingPiecesCoordinates(Player player);
}
