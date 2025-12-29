#include "common_test_fixture.h"
#include "piece_capture_manager.h"

class PromotedPieceCaptureTest : public CommonTestFixture
{};

TEST_F(PromotedPieceCaptureTest, CheckIfPieceCanCapturePositive_PlayerUpCaptureAllDirections)
{
    setup({
        {{4, 3}, Player::NORTH, true},
        {{3, 2}, Player::SOUTH, true},
        {{3, 4}, Player::SOUTH, true},
        {{5, 2}, Player::SOUTH, true},
        {{5, 4}, Player::SOUTH, true}
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
        {{5, 6}, Player::NORTH, true},
        {{4, 5}, Player::SOUTH, true},
        {{4, 7}, Player::SOUTH, true},
        {{6, 5}, Player::SOUTH, true},
        {{6, 7}, Player::SOUTH, true}
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
        {{3, 2}, Player::NORTH, true},
        {{3, 6}, Player::NORTH, true},
        {{4, 3}, Player::SOUTH, true},
        {{4, 7}, Player::SOUTH, true}
    });

    for (auto& piece: piecesOnCheckerboard_)
    {
        EXPECT_TRUE(PieceCaptureManager::checkIfPieceCanCapture(*piece, piecesManager_));
    }
}

TEST_F(PromotedPieceCaptureTest, CheckIfPieceCanCapturePositive_CaptureOnBothSides)
{
    setup({
        {{4, 3}, Player::NORTH, true},
        {{4, 5}, Player::NORTH, true},
        {{5, 4}, Player::SOUTH, true},
        {{5, 2}, Player::SOUTH, true}
    });

    for (auto& piece: piecesOnCheckerboard_)
    {
        EXPECT_TRUE(PieceCaptureManager::checkIfPieceCanCapture(*piece, piecesManager_));
    }
}

TEST_F(PromotedPieceCaptureTest, CheckIfPieceCanCaptureNegative_SideWallBehindPiece)
{
    setup({
        {{2, 1}, Player::NORTH, true},
        {{3, 2}, Player::SOUTH, true},
        {{4, 3}, Player::SOUTH, true}
    });

    for (auto& piece: piecesOnCheckerboard_)
    {
        EXPECT_FALSE(PieceCaptureManager::checkIfPieceCanCapture(*piece, piecesManager_));
    }
}

TEST_F(PromotedPieceCaptureTest, CheckIfPieceCanCaptureNegative_TopBottomAndSideWallBehindPiece)
{
    setup({
        {{1, 2}, Player::NORTH, true},
        {{7, 8}, Player::NORTH, true},
        {{2, 1}, Player::SOUTH, true},
        {{8, 7}, Player::SOUTH, true}
    });

    for (auto& piece: piecesOnCheckerboard_)
    {
        EXPECT_FALSE(PieceCaptureManager::checkIfPieceCanCapture(*piece, piecesManager_));
    }
}

TEST_F(PromotedPieceCaptureTest, CheckIfPieceCanCaptureNegative_FriendlyPieceBehindPiece)
{
    setup({
        {{3, 6}, Player::NORTH, true},
        {{4, 5}, Player::NORTH, true},
        {{5, 4}, Player::SOUTH, true},
        {{6, 3}, Player::SOUTH, true}
    });

    for (auto& piece: piecesOnCheckerboard_)
    {
        EXPECT_FALSE(PieceCaptureManager::checkIfPieceCanCapture(*piece, piecesManager_));
    }
}

TEST_F(PromotedPieceCaptureTest, CheckCapturePossibilityPlayerUp)
{
    setup({
        {{5, 4}, Player::NORTH, true},
        {{4, 3}, Player::SOUTH, true},
        {{4, 5}, Player::SOUTH, true},
        {{6, 3}, Player::SOUTH, true},
        {{6, 5}, Player::SOUTH, true}
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
        {{5, 4}, Player::SOUTH, true},
        {{4, 3}, Player::NORTH, true},
        {{4, 5}, Player::NORTH, true},
        {{6, 3}, Player::NORTH, true},
        {{6, 5}, Player::NORTH, true}
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
        {{3, 4}, Player::NORTH, true},
        {{3, 6}, Player::NORTH, true},
        {{8, 3}, Player::NORTH, true},
        {{4, 3}, Player::SOUTH, true},
        {{4, 5}, Player::SOUTH, true},
        {{4, 7}, Player::SOUTH, true},
        {{7, 2}, Player::SOUTH, true}
    });

    std::vector<Piece*> piecesWhichCanCapturePlayerUp = PieceCaptureManager::whichPiecesCanCapture(Player::NORTH, piecesManager_);
    std::vector<Piece*> piecesWhichCanCapturePlayerDown = PieceCaptureManager::whichPiecesCanCapture(Player::SOUTH, piecesManager_);

    EXPECT_EQ(piecesWhichCanCapturePlayerUp.size(), 3);
    EXPECT_EQ(piecesWhichCanCapturePlayerDown.size(), 3);
}
