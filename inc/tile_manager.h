#pragma once

#include "coordinates.h"
#include "common.h"
#include "pieces_placement.h"

namespace TileManager
{
    bool isTileEmpty(const Coordinates &coordinates, const PiecesPlacement &piecesPlacement);
}
