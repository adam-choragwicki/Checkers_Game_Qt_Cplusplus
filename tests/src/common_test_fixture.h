#pragma once

#include "gtest/gtest.h"
#include "pieces_placement.h"
#include "coordinates.h"
#include "pieces_manager.h"
#include "player_manager.h"

class CommonTestFixture : public ::testing ::Test
{
protected:
    void SetUp() override
    {}

    void TearDown() override
    {}

    void placePiecesOnCheckerboard()
    {
        for(const auto& piece: piecesParameters_)
        {
            piecesManager_.createPiece(piece.coordinates, piece.player);

            if(piece.isPromoted)
            {
                piecesManager_.getPieceAtCoordinates(piece.coordinates).promote();
            }

            piecesOnCheckerboard_.push_back(&piecesManager_.getPieceAtCoordinates(piece.coordinates));
        }
    }

    struct PieceParameters
    {
        Coordinates coordinates;
        Player player;
        bool isPromoted = false;
    };

    PiecesManager piecesManager_;
    std::vector<PieceParameters> piecesParameters_;
    std::vector<Piece*> piecesOnCheckerboard_;
};
