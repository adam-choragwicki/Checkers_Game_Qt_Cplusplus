#pragma once

#include "common.h"
#include "coordinates.h"

#include <vector>

namespace StartingCoordinatesGenerator
{
    std::vector<Coordinates> generatePlayableTilesCoordinates();
    std::vector<Coordinates> generateStartingPiecesCoordinates(Player player);
}
