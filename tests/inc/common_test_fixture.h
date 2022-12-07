#pragma once

#include "gtest/gtest.h"
#include "common.h"
#include "pieces_placement.h"
#include "drawer.h"

class CommonTestFixture : public ::testing ::Test
{
protected:
    void SetUp() override;
    void TearDown() override;
    void placePiecesOnCheckerboard();

    struct PieceParameters
    {
        Coordinates coordinates;
        Player player;
        bool isPromoted = false;
    };

    QGraphicsScene scene_;
    PiecesPlacement piecesPlacement_;
    QVector<PieceParameters> piecesParameters_;
    QVector<Piece*> piecesOnCheckerboard_;
};
