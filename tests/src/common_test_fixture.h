#pragma once

#include "gtest/gtest.h"
#include "coordinates.h"
#include "pieces_manager.h"
#include "player_manager.h"

class CommonTestFixture : public ::testing::Test
{
protected:
    struct PieceParameters
    {
        Coordinates coordinates;
        Player player;
        bool isPromoted = false;
    };

    void setup(const std::initializer_list<PieceParameters> pieces)
    {
        for (const auto& [coordinates, player, isPromoted]: pieces)
        {
            piecesManager_.createPiece(coordinates, player);

            Piece& piece = piecesManager_.getPieceAtCoordinates(coordinates);

            if (isPromoted)
            {
                piece.promote();
            }

            piecesOnCheckerboard_.push_back(&piece);
        }
    }

    PiecesManager piecesManager_;
    std::vector<Piece*> piecesOnCheckerboard_;
};
