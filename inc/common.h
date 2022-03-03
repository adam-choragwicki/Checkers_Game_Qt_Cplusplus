#pragma once

#include "piece.h"

namespace Common {
const int tileSize = 80;
}

using CoordinatesToPiecesMapping = std::map<Coordinates, Piece*>;
