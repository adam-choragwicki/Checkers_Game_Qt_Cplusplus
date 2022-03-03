#pragma once

#include "piece.h"

namespace common {
const int tileSize_ = 80;
}

using CoordinatesToPiecesMapping = std::map<Coordinates, Piece*>;
