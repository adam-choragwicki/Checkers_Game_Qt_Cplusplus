#pragma once

#include "coordinates.h"
#include "common.h"

namespace TileManager
{
    bool isTileEmpty(const Coordinates &coordinates, const CoordinatesToPiecesMapping &coordinatesToPiecesMapping);
}
