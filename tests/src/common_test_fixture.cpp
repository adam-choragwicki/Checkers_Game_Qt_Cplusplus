#include "common_test_fixture.h"

void CommonTestFixture::SetUp()
{
    Drawer::setScene(&scene_);
}

void CommonTestFixture::TearDown()
{

}

void CommonTestFixture::placePiecesOnCheckerboard()
{
    for(const auto& piece: piecesParameters_)
    {
        piecesPlacement_.createPiece(piece.coordinates, piece.player);

        if(piece.isPromoted)
        {
            piecesPlacement_.getPieceAtCoordinates(piece.coordinates)->promote();
        }

        piecesOnCheckerboard_.push_back(piecesPlacement_.getPieceAtCoordinates(piece.coordinates));
    }
}
