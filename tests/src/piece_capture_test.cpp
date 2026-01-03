#include "common_test_fixture.h"
#include "piece_capture_manager.h"

class PieceCaptureTest : public CommonTestFixture
{};

TEST_F(PieceCaptureTest, CheckIfPieceCanCapturePositive_CaptureOnOneSide)
{
    setup({
        {{4, 5}, NORTH_PLAYER},
        {{5, 4}, SOUTH_PLAYER}
    });

    for (auto& piece: piecesOnCheckerboard_)
    {
        EXPECT_TRUE(PieceCaptureManager::checkIfPieceCanCapture(*piece, piecesManager_));
    }
}

TEST_F(PieceCaptureTest, CheckIfPieceCanCapturePositive_CaptureOnOneSideOtherSideWall)
{
    setup({
        {{3, 2}, NORTH_PLAYER},
        {{3, 6}, NORTH_PLAYER},
        {{4, 3}, SOUTH_PLAYER},
        {{4, 7}, SOUTH_PLAYER}
    });

    for (auto& piece: piecesOnCheckerboard_)
    {
        EXPECT_TRUE(PieceCaptureManager::checkIfPieceCanCapture(*piece, piecesManager_));
    }
}

TEST_F(PieceCaptureTest, CheckIfPieceCanCapturePositive_CaptureOnBothSides)
{
    setup({
        {{4, 3}, NORTH_PLAYER},
        {{4, 5}, NORTH_PLAYER},
        {{5, 4}, SOUTH_PLAYER},
        {{5, 2}, SOUTH_PLAYER}
    });

    for (auto& piece: piecesOnCheckerboard_)
    {
        EXPECT_TRUE(PieceCaptureManager::checkIfPieceCanCapture(*piece, piecesManager_));
    }
}

TEST_F(PieceCaptureTest, CheckIfPieceCanCaptureNegative_SideWallBehindPiece)
{
    setup({
        {{2, 1}, NORTH_PLAYER},
        {{3, 2}, SOUTH_PLAYER},
        {{4, 3}, SOUTH_PLAYER} /*This piece artificially blocks NORTH_PLAYER piece from capturing*/
    });

    for (auto& piece: piecesOnCheckerboard_)
    {
        EXPECT_FALSE(PieceCaptureManager::checkIfPieceCanCapture(*piece, piecesManager_));
    }
}

TEST_F(PieceCaptureTest, CheckIfPieceCanCaptureNegative_TopBottomAndSideWallBehindPiece)
{
    setup({
        {{1, 2}, NORTH_PLAYER},
        {{2, 1}, SOUTH_PLAYER},
        {{7, 8}, NORTH_PLAYER},
        {{8, 7}, SOUTH_PLAYER}
    });

    for (auto& piece: piecesOnCheckerboard_)
    {
        EXPECT_FALSE(PieceCaptureManager::checkIfPieceCanCapture(*piece, piecesManager_));
    }
}

TEST_F(PieceCaptureTest, CheckIfPieceCanCaptureNegative_FriendlyPieceBehindPiece)
{
    setup({
        {{3, 6}, NORTH_PLAYER},
        {{4, 5}, NORTH_PLAYER},
        {{5, 4}, SOUTH_PLAYER},
        {{6, 3}, SOUTH_PLAYER}
    });

    for (auto& piece: piecesOnCheckerboard_)
    {
        EXPECT_FALSE(PieceCaptureManager::checkIfPieceCanCapture(*piece, piecesManager_));
    }
}

TEST_F(PieceCaptureTest, CheckIfPieceCanCaptureNegative_EnemyPieceBehindPiece)
{
    setup({
        {{4, 5}, NORTH_PLAYER},
        {{6, 3}, NORTH_PLAYER},
        {{3, 6}, SOUTH_PLAYER},
        {{5, 4}, SOUTH_PLAYER}
    });

    for (auto& piece: piecesOnCheckerboard_)
    {
        EXPECT_FALSE(PieceCaptureManager::checkIfPieceCanCapture(*piece, piecesManager_));
    }
}

TEST_F(PieceCaptureTest, CheckCapturePossibility)
{
    setup({
        {{3, 2}, NORTH_PLAYER},
        {{4, 3}, SOUTH_PLAYER}
    });

    EXPECT_TRUE(PieceCaptureManager::checkCapturePossibility(*piecesOnCheckerboard_.at(0), piecesManager_, Coordinates(5, 4)));
    EXPECT_FALSE(PieceCaptureManager::checkCapturePossibility(*piecesOnCheckerboard_.at(0), piecesManager_, Coordinates(4, 1)));
    EXPECT_FALSE(PieceCaptureManager::checkCapturePossibility(*piecesOnCheckerboard_.at(0), piecesManager_, Coordinates(2, 1)));
    EXPECT_FALSE(PieceCaptureManager::checkCapturePossibility(*piecesOnCheckerboard_.at(0), piecesManager_, Coordinates(2, 3)));

    EXPECT_TRUE(PieceCaptureManager::checkCapturePossibility(*piecesOnCheckerboard_.at(1), piecesManager_, Coordinates(2, 1)));
    EXPECT_FALSE(PieceCaptureManager::checkCapturePossibility(*piecesOnCheckerboard_.at(1), piecesManager_, Coordinates(2, 3)));
    EXPECT_FALSE(PieceCaptureManager::checkCapturePossibility(*piecesOnCheckerboard_.at(1), piecesManager_, Coordinates(3, 4)));
    EXPECT_FALSE(PieceCaptureManager::checkCapturePossibility(*piecesOnCheckerboard_.at(1), piecesManager_, Coordinates(5, 2)));
    EXPECT_FALSE(PieceCaptureManager::checkCapturePossibility(*piecesOnCheckerboard_.at(1), piecesManager_, Coordinates(5, 4)));
}

TEST_F(PieceCaptureTest, WhichPiecesCanCapture)
{
    setup({
        {{3, 4}, NORTH_PLAYER},
        {{3, 6}, NORTH_PLAYER},
        {{7, 2}, NORTH_PLAYER},
        {{8, 3}, NORTH_PLAYER},
        {{4, 3}, SOUTH_PLAYER},
        {{4, 5}, SOUTH_PLAYER},
        {{4, 7}, SOUTH_PLAYER}
    });

    std::vector<Piece*> piecesWhichCanCapturePlayerUp = PieceCaptureManager::whichPiecesCanCapture(NORTH_PLAYER, piecesManager_);
    std::vector<Piece*> piecesWhichCanCapturePlayerDown = PieceCaptureManager::whichPiecesCanCapture(SOUTH_PLAYER, piecesManager_);

    EXPECT_EQ(piecesWhichCanCapturePlayerUp.size(), 2);
    EXPECT_EQ(piecesWhichCanCapturePlayerDown.size(), 3);
}
