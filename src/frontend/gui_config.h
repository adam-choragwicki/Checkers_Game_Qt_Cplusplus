#pragma once

#include <QColor>
#include <QPoint>

namespace GuiConfig
{
    namespace Timing
    {
        const int ANIMATION_DURATION_MS = 200;
    }

    namespace Tile
    {
        const int SIZE = 80;
    }

    namespace Piece
    {
        const int OFFSET_X = 15;
        const int OFFSET_Y = 15;
        const int SIZE = 50;
        const int OUTLINE_WIDTH = 5;
    }

    namespace Colors
    {
        constexpr QColor BLACK_PIECE{50, 50, 50};
        constexpr QColor DISABLED_BLACK_PIECE_OUTLINE{0, 0, 0};

        constexpr QColor RED_PIECE{220, 0, 0};
        constexpr QColor DISABLED_RED_PIECE_OUTLINE{170, 0, 0};

        constexpr QColor SELECTED_PIECE_OUTLINE{255, 255, 255};
        constexpr QColor ACTIVE_PIECE_OUTLINE{255, 255, 0};

        constexpr QColor CROWN(150, 150, 150);

        constexpr QColor PLAYABLE_TILE_COLOR{140, 90, 40};
        constexpr QColor NON_PLAYABLE_TILE_COLOR{230, 200, 160};
    }

    namespace Crown
    {
        const std::vector<QPoint> POLYGON_SHAPE_VERTICES_COORDINATES = {{0,  0},
                                                                        {6,  8},
                                                                        {12, 0},
                                                                        {18, 8},
                                                                        {23, 0},
                                                                        {29, 8},
                                                                        {34, 0},
                                                                        {33, 20},
                                                                        {2,  20}};

        const int CROWN_OFFSET_X = 10;
        const int CROWN_OFFSET_Y = 18;
    }
}
