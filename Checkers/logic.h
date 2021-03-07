#pragma once
#include <vector>
#include "common.h"

class Logic
{
public:
    Logic() = delete;
    Logic(const Logic&) = delete;
    static std::vector<std::pair<int, int> > GenerateAllValidGameTilesCoordinates();
    static std::vector<std::pair<int, int> > GenerateStartingPiecesCoordinates(Player player);
};
