#pragma once

#include "piece.h"

namespace GameParameters
{
    const int tileSize = 80;

    constexpr QColor blackPieceColor_{50, 50, 50};
    constexpr QColor blackPieceOutlineColor_{0, 0, 0};

    constexpr QColor redPieceColor_{220, 0, 0};
    constexpr QColor redPieceOutlineColor_{170, 0, 0};

    constexpr QColor activePieceOutlineColor_{255, 255, 255};
    constexpr QColor movePossiblePieceOutlineColor_{255, 255, 0};

    constexpr QColor crownColor(150, 150, 150);
}

enum class Status
{
    exit = 0,
    restart = 1
};
