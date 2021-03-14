#pragma once
#include <vector>
#include "common.h"
#include "coordinates.h"

class Logic
{
public:
    Logic() = delete;
    Logic(const Logic&) = delete;
    static std::vector<Coordinates> GenerateAllValidGameTilesCoordinates();
    static std::vector<Coordinates> GenerateStartingPiecesCoordinates(Player player);
};
