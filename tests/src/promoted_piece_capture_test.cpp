#include "common_test_fixture.h"
#include "piece_capture_manager.h"

class PromotedPieceCaptureTest : public CommonTestFixture
{};

TEST_F(PromotedPieceCaptureTest, CheckIfPieceCanCapturePositive_PlayerUpCaptureAllDirections)
{
    setup({
        {{4, 3}, NORTH_PLAYER, true},
        {{3, 2}, SOUTH_PLAYER, true},
        {{3, 4}, SOUTH_PLAYER, true},
        {{5, 2}, SOUTH_PLAYER, true},
        {{5, 4}, SOUTH_PLAYER, true}
    });

    EXPECT_TRUE(PieceCaptureManager::checkIfPieceCanCapture(*piecesOnCheckerboard_.at(0), piecesManager_));

    for (size_t i = 1; i < piecesOnCheckerboard_.size(); ++i)
    {
        EXPECT_FALSE(PieceCaptureManager::checkIfPieceCanCapture(*piecesOnCheckerboard_.at(i), piecesManager_));
    }
}

TEST_F(PromotedPieceCaptureTest, CheckIfPieceCanCapturePositive_PlayerDownCaptureAllDirections)
{
    setup({
        {{5, 6}, NORTH_PLAYER, true},
        {{4, 5}, SOUTH_PLAYER, true},
        {{4, 7}, SOUTH_PLAYER, true},
        {{6, 5}, SOUTH_PLAYER, true},
        {{6, 7}, SOUTH_PLAYER, true}
    });

    EXPECT_TRUE(PieceCaptureManager::checkIfPieceCanCapture(*piecesOnCheckerboard_.at(0), piecesManager_));

    for (size_t i = 1; i < piecesOnCheckerboard_.size(); ++i)
    {
        EXPECT_FALSE(PieceCaptureManager::checkIfPieceCanCapture(*piecesOnCheckerboard_.at(i), piecesManager_));
    }
}

TEST_F(PromotedPieceCaptureTest, CheckIfPieceCanCapturePositive_CaptureOnOneSideOtherSideWall)
{
    setup({
        {{3, 2}, NORTH_PLAYER, true},
        {{3, 6}, NORTH_PLAYER, true},
        {{4, 3}, SOUTH_PLAYER, true},
        {{4, 7}, SOUTH_PLAYER, true}
    });

    for (auto& piece: piecesOnCheckerboard_)
    {
        EXPECT_TRUE(PieceCaptureManager::checkIfPieceCanCapture(*piece, piecesManager_));
    }
}

TEST_F(PromotedPieceCaptureTest, CheckIfPieceCanCapturePositive_CaptureOnBothSides)
{
    setup({
        {{4, 3}, NORTH_PLAYER, true},
        {{4, 5}, NORTH_PLAYER, true},
        {{5, 4}, SOUTH_PLAYER, true},
        {{5, 2}, SOUTH_PLAYER, true}
    });

    for (auto& piece: piecesOnCheckerboard_)
    {
        EXPECT_TRUE(PieceCaptureManager::checkIfPieceCanCapture(*piece, piecesManager_));
    }
}

TEST_F(PromotedPieceCaptureTest, CheckIfPieceCanCaptureNegative_SideWallBehindPiece)
{
    setup({
        {{2, 1}, NORTH_PLAYER, true},
        {{3, 2}, SOUTH_PLAYER, true},
        {{4, 3}, SOUTH_PLAYER, true}
    });

    for (auto& piece: piecesOnCheckerboard_)
    {
        EXPECT_FALSE(PieceCaptureManager::checkIfPieceCanCapture(*piece, piecesManager_));
    }
}

TEST_F(PromotedPieceCaptureTest, CheckIfPieceCanCaptureNegative_TopBottomAndSideWallBehindPiece)
{
    setup({
        {{1, 2}, NORTH_PLAYER, true},
        {{7, 8}, NORTH_PLAYER, true},
        {{2, 1}, SOUTH_PLAYER, true},
        {{8, 7}, SOUTH_PLAYER, true}
    });

    for (auto& piece: piecesOnCheckerboard_)
    {
        EXPECT_FALSE(PieceCaptureManager::checkIfPieceCanCapture(*piece, piecesManager_));
    }
}

TEST_F(PromotedPieceCaptureTest, CheckIfPieceCanCaptureNegative_FriendlyPieceBehindPiece)
{
    setup({
        {{3, 6}, NORTH_PLAYER, true},
        {{4, 5}, NORTH_PLAYER, true},
        {{5, 4}, SOUTH_PLAYER, true},
        {{6, 3}, SOUTH_PLAYER, true}
    });

    for (auto& piece: piecesOnCheckerboard_)
    {
        EXPECT_FALSE(PieceCaptureManager::checkIfPieceCanCapture(*piece, piecesManager_));
    }
}

TEST_F(PromotedPieceCaptureTest, CheckCapturePossibilityPlayerUp)
{
    setup({
        {{5, 4}, NORTH_PLAYER, true},
        {{4, 3}, SOUTH_PLAYER, true},
        {{4, 5}, SOUTH_PLAYER, true},
        {{6, 3}, SOUTH_PLAYER, true},
        {{6, 5}, SOUTH_PLAYER, true}
    });

    EXPECT_TRUE(PieceCaptureManager::checkCapturePossibility(*piecesOnCheckerboard_.at(0), piecesManager_, {3, 2}));
    EXPECT_TRUE(PieceCaptureManager::checkCapturePossibility(*piecesOnCheckerboard_.at(0), piecesManager_, {3, 6}));
    EXPECT_TRUE(PieceCaptureManager::checkCapturePossibility(*piecesOnCheckerboard_.at(0), piecesManager_, {7, 2}));
    EXPECT_TRUE(PieceCaptureManager::checkCapturePossibility(*piecesOnCheckerboard_.at(0), piecesManager_, {7, 6}));

    const std::vector<Coordinates> invalidCaptureTargetsCoordinates = {
        {2, 3}, {4, 1}, {2, 1}, {4, 3}, {4, 5}, {6, 3}, {6, 5}, {3, 4}, {5, 2}, {5, 6}, {7, 4}
    };

    for (auto& target: invalidCaptureTargetsCoordinates)
    {
        EXPECT_FALSE(PieceCaptureManager::checkCapturePossibility(*piecesOnCheckerboard_.at(0), piecesManager_, target));
    }
}

TEST_F(PromotedPieceCaptureTest, CheckCapturePossibilityPlayerDown)
{
    setup({
        {{5, 4}, SOUTH_PLAYER, true},
        {{4, 3}, NORTH_PLAYER, true},
        {{4, 5}, NORTH_PLAYER, true},
        {{6, 3}, NORTH_PLAYER, true},
        {{6, 5}, NORTH_PLAYER, true}
    });

    EXPECT_TRUE(PieceCaptureManager::checkCapturePossibility(*piecesOnCheckerboard_.at(0), piecesManager_, {3, 2}));
    EXPECT_TRUE(PieceCaptureManager::checkCapturePossibility(*piecesOnCheckerboard_.at(0), piecesManager_, {3, 6}));
    EXPECT_TRUE(PieceCaptureManager::checkCapturePossibility(*piecesOnCheckerboard_.at(0), piecesManager_, {7, 2}));
    EXPECT_TRUE(PieceCaptureManager::checkCapturePossibility(*piecesOnCheckerboard_.at(0), piecesManager_, {7, 6}));

    const std::vector<Coordinates> invalidCaptureTargetsCoordinates = {
        {2, 3}, {4, 1}, {2, 1}, {4, 3}, {4, 5}, {6, 3}, {6, 5}, {3, 4}, {5, 2}, {5, 6}, {7, 4}
    };

    for (auto& target: invalidCaptureTargetsCoordinates)
    {
        EXPECT_FALSE(PieceCaptureManager::checkCapturePossibility(*piecesOnCheckerboard_.at(0), piecesManager_, target));
    }
}

TEST_F(PromotedPieceCaptureTest, WhichPiecesCanCapture)
{
    setup({
        {{3, 4}, NORTH_PLAYER, true},
        {{3, 6}, NORTH_PLAYER, true},
        {{8, 3}, NORTH_PLAYER, true},
        {{4, 3}, SOUTH_PLAYER, true},
        {{4, 5}, SOUTH_PLAYER, true},
        {{4, 7}, SOUTH_PLAYER, true},
        {{7, 2}, SOUTH_PLAYER, true}
    });

    std::vector<Piece*> piecesWhichCanCapturePlayerUp = PieceCaptureManager::whichPiecesCanCapture(NORTH_PLAYER, piecesManager_);
    std::vector<Piece*> piecesWhichCanCapturePlayerDown = PieceCaptureManager::whichPiecesCanCapture(SOUTH_PLAYER, piecesManager_);

    EXPECT_EQ(piecesWhichCanCapturePlayerUp.size(), 3);
    EXPECT_EQ(piecesWhichCanCapturePlayerDown.size(), 3);
}
