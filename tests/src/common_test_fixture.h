#pragma once

#include "gtest/gtest.h"
#include "pieces_placement.h"

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
            piecesPlacement_.createPiece(piece.coordinates, piece.player);

            if(piece.isPromoted)
            {
                piecesPlacement_.getPieceAtCoordinates(piece.coordinates).promote();
            }

            piecesOnCheckerboard_.push_back(&piecesPlacement_.getPieceAtCoordinates(piece.coordinates));
        }
    }

    struct PieceParameters
    {
        Coordinates coordinates;
        Player player;
        bool isPromoted = false;
    };

    PiecesPlacement piecesPlacement_;
    std::vector<PieceParameters> piecesParameters_;
    std::vector<Piece*> piecesOnCheckerboard_;
};
