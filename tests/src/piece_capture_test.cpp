#include "common_test_fixture.h"
#include "piece_capture_manager.h"

class PieceCaptureTest : public CommonTestFixture
{};

TEST_F(PieceCaptureTest, CheckIfPieceCanCapturePositive_CaptureOnOneSide)
{
    piecesParameters_ = {{{4, 5}, Player::NORTH},
                         {{5, 4}, Player::SOUTH}};

    placePiecesOnCheckerboard();

    for(auto& piece : piecesOnCheckerboard_)
    {
        EXPECT_TRUE(PieceCaptureManager::checkIfPieceCanCapture(*piece, piecesManager_));
    }
}

TEST_F(PieceCaptureTest, CheckIfPieceCanCapturePositive_CaptureOnOneSideOtherSideWall)
{
    piecesParameters_ = {{{3, 2}, Player::NORTH},
                         {{3, 6}, Player::NORTH},
                         {{4, 3}, Player::SOUTH},
                         {{4, 7}, Player::SOUTH}};

    placePiecesOnCheckerboard();

    for(auto& piece : piecesOnCheckerboard_)
    {
        EXPECT_TRUE(PieceCaptureManager::checkIfPieceCanCapture(*piece, piecesManager_));
    }
}

TEST_F(PieceCaptureTest, CheckIfPieceCanCapturePositive_CaptureOnBothSides)
{
    piecesParameters_ = {{{4, 3}, Player::NORTH},
                         {{4, 5}, Player::NORTH},
                         {{5, 4}, Player::SOUTH},
                         {{5, 2}, Player::SOUTH}};

    placePiecesOnCheckerboard();

    for(auto& piece : piecesOnCheckerboard_)
    {
        EXPECT_TRUE(PieceCaptureManager::checkIfPieceCanCapture(*piece, piecesManager_));
    }
}

TEST_F(PieceCaptureTest, CheckIfPieceCanCaptureNegative_SideWallBehindPiece)
{
    piecesParameters_ = {{{2, 1}, Player::NORTH},
                         {{3, 2}, Player::SOUTH},
                         {{4, 3}, Player::SOUTH}}; /*This piece artificially blocks Player::NORTH piece from capturing*/

    placePiecesOnCheckerboard();

    for(auto& piece : piecesOnCheckerboard_)
    {
        EXPECT_FALSE(PieceCaptureManager::checkIfPieceCanCapture(*piece, piecesManager_));
    }
}

TEST_F(PieceCaptureTest, CheckIfPieceCanCaptureNegative_TopBottomAndSideWallBehindPiece)
{
    piecesParameters_ = {{{1, 2}, Player::NORTH},
                         {{2, 1}, Player::SOUTH},
                         {{7, 8}, Player::NORTH},
                         {{8, 7}, Player::SOUTH}};

    placePiecesOnCheckerboard();

    for(auto& piece : piecesOnCheckerboard_)
    {
        EXPECT_FALSE(PieceCaptureManager::checkIfPieceCanCapture(*piece, piecesManager_));
    }
}

TEST_F(PieceCaptureTest, CheckIfPieceCanCaptureNegative_FriendlyPieceBehindPiece)
{
    piecesParameters_ = {{{3, 6}, Player::NORTH},
                         {{4, 5}, Player::NORTH},
                         {{5, 4}, Player::SOUTH},
                         {{6, 3}, Player::SOUTH}};

    placePiecesOnCheckerboard();

    for(auto& piece : piecesOnCheckerboard_)
    {
        EXPECT_FALSE(PieceCaptureManager::checkIfPieceCanCapture(*piece, piecesManager_));
    }
}

TEST_F(PieceCaptureTest, CheckIfPieceCanCaptureNegative_EnemyPieceBehindPiece)
{
    piecesParameters_ = {{{4, 5}, Player::NORTH},
                         {{6, 3}, Player::NORTH},
                         {{3, 6}, Player::SOUTH},
                         {{5, 4}, Player::SOUTH}};

    placePiecesOnCheckerboard();

    for(auto& piece : piecesOnCheckerboard_)
    {
        EXPECT_FALSE(PieceCaptureManager::checkIfPieceCanCapture(*piece, piecesManager_));
    }
}

TEST_F(PieceCaptureTest, CheckCapturePossibility)
{
    piecesParameters_ = {{{3, 2}, Player::NORTH},
                         {{4, 3}, Player::SOUTH}};

    placePiecesOnCheckerboard();

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
    piecesParameters_ = {{{3, 4}, Player::NORTH},
                         {{3, 6}, Player::NORTH},
                         {{7, 2}, Player::NORTH},
                         {{8, 3}, Player::NORTH},
                         {{4, 3}, Player::SOUTH},
                         {{4, 5}, Player::SOUTH},
                         {{4, 7}, Player::SOUTH}};

    placePiecesOnCheckerboard();

    std::vector<Piece*> piecesWhichCanCapturePlayerUp = PieceCaptureManager::whichPiecesCanCapture(Player::NORTH, piecesManager_);
    std::vector<Piece*> piecesWhichCanCapturePlayerDown = PieceCaptureManager::whichPiecesCanCapture(Player::SOUTH, piecesManager_);

    EXPECT_EQ(piecesWhichCanCapturePlayerUp.size(), 2);
    EXPECT_EQ(piecesWhichCanCapturePlayerDown.size(), 3);
}
