#include "common_test_fixture.h"
#include "piece_capture_manager.h"

class CaptureTest : public CommonTestFixture
{};

TEST_F(CaptureTest, CheckIfPieceCanCapturePositive_CaptureOnOneSide)
{
    piecesParameters_ = {{{4, 5}, Player::up},
                         {{5, 4}, Player::down}};

    placePiecesOnCheckerboard();

    for(auto& piece : piecesOnCheckerboard_)
    {
        EXPECT_TRUE(PieceCaptureManager::checkIfPieceCanCapture(piece, piecesPlacement_));
    }
}

TEST_F(CaptureTest, CheckIfPieceCanCapturePositive_CaptureOnOneSideOtherSideWall)
{
    piecesParameters_ = {{{3, 2}, Player::up},
                         {{3, 6}, Player::up},
                         {{4, 3}, Player::down},
                         {{4, 7}, Player::down}};

    placePiecesOnCheckerboard();

    for(auto& piece : piecesOnCheckerboard_)
    {
        EXPECT_TRUE(PieceCaptureManager::checkIfPieceCanCapture(piece, piecesPlacement_));
    }
}

TEST_F(CaptureTest, CheckIfPieceCanCapturePositive_CaptureOnBothSides)
{
    piecesParameters_ = {{{4, 3}, Player::up},
                         {{4, 5}, Player::up},
                         {{5, 4}, Player::down},
                         {{5, 2}, Player::down}};

    placePiecesOnCheckerboard();

    for(auto& piece : piecesOnCheckerboard_)
    {
        EXPECT_TRUE(PieceCaptureManager::checkIfPieceCanCapture(piece, piecesPlacement_));
    }
}

TEST_F(CaptureTest, CheckIfPieceCanCaptureNegative_SideWallBehindPiece)
{
    piecesParameters_ = {{{2, 1}, Player::up},
                         {{3, 2}, Player::down},
                         {{4, 3}, Player::down}}; /*This piece artificially blocks Player::up piece from capturing*/

    placePiecesOnCheckerboard();

    for(auto& piece : piecesOnCheckerboard_)
    {
        EXPECT_FALSE(PieceCaptureManager::checkIfPieceCanCapture(piece, piecesPlacement_));
    }
}

TEST_F(CaptureTest, CheckIfPieceCanCaptureNegative_TopBottomAndSideWallBehindPiece)
{
    piecesParameters_ = {{{1, 2}, Player::up},
                         {{2, 1}, Player::down},
                         {{7, 8}, Player::up},
                         {{8, 7}, Player::down}};

    placePiecesOnCheckerboard();

    for(auto& piece : piecesOnCheckerboard_)
    {
        EXPECT_FALSE(PieceCaptureManager::checkIfPieceCanCapture(piece, piecesPlacement_));
    }
}

TEST_F(CaptureTest, CheckIfPieceCanCaptureNegative_FriendlyPieceBehindPiece)
{
    piecesParameters_ = {{{3, 6}, Player::up},
                         {{4, 5}, Player::up},
                         {{5, 4}, Player::down},
                         {{6, 3}, Player::down}};

    placePiecesOnCheckerboard();

    for(auto& piece : piecesOnCheckerboard_)
    {
        EXPECT_FALSE(PieceCaptureManager::checkIfPieceCanCapture(piece, piecesPlacement_));
    }
}

TEST_F(CaptureTest, CheckIfPieceCanCaptureNegative_EnemyPieceBehindPiece)
{
    piecesParameters_ = {{{4, 5}, Player::up},
                         {{6, 3}, Player::up},
                         {{3, 6}, Player::down},
                         {{5, 4}, Player::down}};

    placePiecesOnCheckerboard();

    for(auto& piece : piecesOnCheckerboard_)
    {
        EXPECT_FALSE(PieceCaptureManager::checkIfPieceCanCapture(piece, piecesPlacement_));
    }
}

TEST_F(CaptureTest, CheckCapturePossibility)
{
    piecesParameters_ = {{{3, 2}, Player::up},
                         {{4, 3}, Player::down}};

    placePiecesOnCheckerboard();

    EXPECT_TRUE(PieceCaptureManager::checkCapturePossibility(piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(5, 4)));
    EXPECT_FALSE(PieceCaptureManager::checkCapturePossibility(piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(4, 1)));
    EXPECT_FALSE(PieceCaptureManager::checkCapturePossibility(piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(2, 1)));
    EXPECT_FALSE(PieceCaptureManager::checkCapturePossibility(piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(2, 3)));

    EXPECT_TRUE(PieceCaptureManager::checkCapturePossibility(piecesOnCheckerboard_.at(1), piecesPlacement_, Coordinates(2, 1)));
    EXPECT_FALSE(PieceCaptureManager::checkCapturePossibility(piecesOnCheckerboard_.at(1), piecesPlacement_, Coordinates(2, 3)));
    EXPECT_FALSE(PieceCaptureManager::checkCapturePossibility(piecesOnCheckerboard_.at(1), piecesPlacement_, Coordinates(3, 4)));
    EXPECT_FALSE(PieceCaptureManager::checkCapturePossibility(piecesOnCheckerboard_.at(1), piecesPlacement_, Coordinates(5, 2)));
    EXPECT_FALSE(PieceCaptureManager::checkCapturePossibility(piecesOnCheckerboard_.at(1), piecesPlacement_, Coordinates(5, 4)));
}

TEST_F(CaptureTest, WhichPiecesCanCapture)
{
    piecesParameters_ = {{{3, 4}, Player::up},
                         {{3, 6}, Player::up},
                         {{7, 2}, Player::up},
                         {{8, 3}, Player::up},
                         {{4, 3}, Player::down},
                         {{4, 5}, Player::down},
                         {{4, 7}, Player::down}};

    placePiecesOnCheckerboard();

    QVector<Piece*> piecesWhichCanCapturePlayerUp = PieceCaptureManager::whichPiecesCanCapture(Player::up, piecesPlacement_);
    QVector<Piece*> piecesWhichCanCapturePlayerDown = PieceCaptureManager::whichPiecesCanCapture(Player::down, piecesPlacement_);

    EXPECT_EQ(piecesWhichCanCapturePlayerUp.size(), 2);
    EXPECT_EQ(piecesWhichCanCapturePlayerDown.size(), 3);
}
