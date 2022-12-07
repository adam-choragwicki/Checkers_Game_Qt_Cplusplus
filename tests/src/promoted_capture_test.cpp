#include "common_test_fixture.h"
#include "piece_capture_manager.h"

class PromotedCaptureTest : public CommonTestFixture
{};

TEST_F(PromotedCaptureTest, CheckIfPieceCanCapturePositive_PlayerUpCaptureAllDirections)
{
    piecesParameters_ = {{{4, 3}, Player::up,   true},
                         {{3, 2}, Player::down, true},
                         {{3, 4}, Player::down, true},
                         {{5, 2}, Player::down, true},
                         {{5, 4}, Player::down, true}};

    placePiecesOnCheckerboard();

    EXPECT_TRUE(PieceCaptureManager::checkIfPieceCanCapture(piecesOnCheckerboard_.at(0), piecesPlacement_));
    EXPECT_FALSE(PieceCaptureManager::checkIfPieceCanCapture(piecesOnCheckerboard_.at(1), piecesPlacement_));
    EXPECT_FALSE(PieceCaptureManager::checkIfPieceCanCapture(piecesOnCheckerboard_.at(2), piecesPlacement_));
    EXPECT_FALSE(PieceCaptureManager::checkIfPieceCanCapture(piecesOnCheckerboard_.at(3), piecesPlacement_));
    EXPECT_FALSE(PieceCaptureManager::checkIfPieceCanCapture(piecesOnCheckerboard_.at(4), piecesPlacement_));
}

TEST_F(PromotedCaptureTest, CheckIfPieceCanCapturePositive_PlayerDownCaptureAllDirections)
{
    piecesParameters_ = {{{5, 6}, Player::up,   true},
                         {{4, 5}, Player::down, true},
                         {{4, 7}, Player::down, true},
                         {{6, 5}, Player::down, true},
                         {{6, 7}, Player::down, true}};

    placePiecesOnCheckerboard();

    EXPECT_TRUE(PieceCaptureManager::checkIfPieceCanCapture(piecesOnCheckerboard_.at(0), piecesPlacement_));
    EXPECT_FALSE(PieceCaptureManager::checkIfPieceCanCapture(piecesOnCheckerboard_.at(1), piecesPlacement_));
    EXPECT_FALSE(PieceCaptureManager::checkIfPieceCanCapture(piecesOnCheckerboard_.at(2), piecesPlacement_));
    EXPECT_FALSE(PieceCaptureManager::checkIfPieceCanCapture(piecesOnCheckerboard_.at(3), piecesPlacement_));
    EXPECT_FALSE(PieceCaptureManager::checkIfPieceCanCapture(piecesOnCheckerboard_.at(4), piecesPlacement_));
}

TEST_F(PromotedCaptureTest, CheckIfPieceCanCapturePositive_CaptureOnOneSideOtherSideWall)
{
    piecesParameters_ = {{{3, 2}, Player::up,   true},
                         {{3, 6}, Player::up,   true},
                         {{4, 3}, Player::down, true},
                         {{4, 7}, Player::down, true}};

    placePiecesOnCheckerboard();

    for(const auto& piece : piecesOnCheckerboard_)
    {
        EXPECT_TRUE(PieceCaptureManager::checkIfPieceCanCapture(piece, piecesPlacement_));
    }
}

TEST_F(PromotedCaptureTest, CheckIfPieceCanCapturePositive_CaptureOnBothSides)
{
    piecesParameters_ = {{{4, 3}, Player::up,   true},
                         {{4, 5}, Player::up,   true},
                         {{5, 4}, Player::down, true},
                         {{5, 2}, Player::down, true}};

    placePiecesOnCheckerboard();

    for(const auto& piece : piecesOnCheckerboard_)
    {
        EXPECT_TRUE(PieceCaptureManager::checkIfPieceCanCapture(piece, piecesPlacement_));
    }
}

TEST_F(PromotedCaptureTest, CheckIfPieceCanCaptureNegative_SideWallBehindPiece)
{
    piecesParameters_ = {{{2, 1}, Player::up,   true},
                         {{3, 2}, Player::down, true},
                         {{4, 3}, Player::down, true}};

    placePiecesOnCheckerboard();

    for(const auto& piece : piecesOnCheckerboard_)
    {
        EXPECT_FALSE(PieceCaptureManager::checkIfPieceCanCapture(piece, piecesPlacement_));
    }
}

TEST_F(PromotedCaptureTest, CheckIfPieceCanCaptureNegative_TopBottomAndSideWallBehindPiece)
{
    piecesParameters_ = {{{1, 2}, Player::up,   true},
                         {{7, 8}, Player::up,   true},
                         {{2, 1}, Player::down, true},
                         {{8, 7}, Player::down, true}};

    placePiecesOnCheckerboard();

    for(const auto& piece : piecesOnCheckerboard_)
    {
        EXPECT_FALSE(PieceCaptureManager::checkIfPieceCanCapture(piece, piecesPlacement_));
    }
}

TEST_F(PromotedCaptureTest, CheckIfPieceCanCaptureNegative_FriendlyPieceBehindPiece)
{
    piecesParameters_ = {{{3, 6}, Player::up,   true},
                         {{4, 5}, Player::up,   true},
                         {{5, 4}, Player::down, true},
                         {{6, 3}, Player::down, true}};

    placePiecesOnCheckerboard();

    for(const auto& piece : piecesOnCheckerboard_)
    {
        EXPECT_FALSE(PieceCaptureManager::checkIfPieceCanCapture(piece, piecesPlacement_));
    }
}

TEST_F(PromotedCaptureTest, CheckCapturePossibilityPlayerUp)
{
    piecesParameters_ = {{{5, 4}, Player::up,   true},
                         {{4, 3}, Player::down, true},
                         {{4, 5}, Player::down, true},
                         {{6, 3}, Player::down, true},
                         {{6, 5}, Player::down, true}};

    placePiecesOnCheckerboard();

    EXPECT_TRUE(PieceCaptureManager::checkCapturePossibility(piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(3, 2)));
    EXPECT_TRUE(PieceCaptureManager::checkCapturePossibility(piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(3, 6)));
    EXPECT_TRUE(PieceCaptureManager::checkCapturePossibility(piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(7, 2)));
    EXPECT_TRUE(PieceCaptureManager::checkCapturePossibility(piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(7, 6)));

    EXPECT_FALSE(PieceCaptureManager::checkCapturePossibility(piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(2, 3)));
    EXPECT_FALSE(PieceCaptureManager::checkCapturePossibility(piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(4, 1)));
    EXPECT_FALSE(PieceCaptureManager::checkCapturePossibility(piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(2, 1)));
    EXPECT_FALSE(PieceCaptureManager::checkCapturePossibility(piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(2, 3)));
    EXPECT_FALSE(PieceCaptureManager::checkCapturePossibility(piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(4, 3)));
    EXPECT_FALSE(PieceCaptureManager::checkCapturePossibility(piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(4, 5)));
    EXPECT_FALSE(PieceCaptureManager::checkCapturePossibility(piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(6, 3)));
    EXPECT_FALSE(PieceCaptureManager::checkCapturePossibility(piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(6, 5)));
    EXPECT_FALSE(PieceCaptureManager::checkCapturePossibility(piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(3, 4)));
    EXPECT_FALSE(PieceCaptureManager::checkCapturePossibility(piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(5, 2)));
    EXPECT_FALSE(PieceCaptureManager::checkCapturePossibility(piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(5, 6)));
    EXPECT_FALSE(PieceCaptureManager::checkCapturePossibility(piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(7, 4)));
}

TEST_F(PromotedCaptureTest, CheckCapturePossibilityPlayerDown)
{
    piecesParameters_ = {{{5, 4}, Player::down, true},
                         {{4, 3}, Player::up,   true},
                         {{4, 5}, Player::up,   true},
                         {{6, 3}, Player::up,   true},
                         {{6, 5}, Player::up,   true}};

    placePiecesOnCheckerboard();

    EXPECT_TRUE(PieceCaptureManager::checkCapturePossibility(piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(3, 2)));
    EXPECT_TRUE(PieceCaptureManager::checkCapturePossibility(piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(3, 6)));
    EXPECT_TRUE(PieceCaptureManager::checkCapturePossibility(piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(7, 2)));
    EXPECT_TRUE(PieceCaptureManager::checkCapturePossibility(piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(7, 6)));

    EXPECT_FALSE(PieceCaptureManager::checkCapturePossibility(piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(2, 3)));
    EXPECT_FALSE(PieceCaptureManager::checkCapturePossibility(piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(4, 1)));
    EXPECT_FALSE(PieceCaptureManager::checkCapturePossibility(piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(2, 1)));
    EXPECT_FALSE(PieceCaptureManager::checkCapturePossibility(piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(2, 3)));
    EXPECT_FALSE(PieceCaptureManager::checkCapturePossibility(piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(4, 3)));
    EXPECT_FALSE(PieceCaptureManager::checkCapturePossibility(piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(4, 5)));
    EXPECT_FALSE(PieceCaptureManager::checkCapturePossibility(piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(6, 3)));
    EXPECT_FALSE(PieceCaptureManager::checkCapturePossibility(piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(6, 5)));
    EXPECT_FALSE(PieceCaptureManager::checkCapturePossibility(piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(3, 4)));
    EXPECT_FALSE(PieceCaptureManager::checkCapturePossibility(piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(5, 2)));
    EXPECT_FALSE(PieceCaptureManager::checkCapturePossibility(piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(5, 6)));
    EXPECT_FALSE(PieceCaptureManager::checkCapturePossibility(piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(7, 4)));
}

TEST_F(PromotedCaptureTest, WhichPiecesCanCapture)
{
    piecesParameters_ = {{{3, 4}, Player::up,   true},
                         {{3, 6}, Player::up,   true},
                         {{8, 3}, Player::up,   true},
                         {{4, 3}, Player::down, true},
                         {{4, 5}, Player::down, true},
                         {{4, 7}, Player::down, true},
                         {{7, 2}, Player::down, true}};

    placePiecesOnCheckerboard();

    QVector<Piece*> piecesWhichCanCapturePlayerUp = PieceCaptureManager::whichPiecesCanCapture(Player::up, piecesPlacement_);
    QVector<Piece*> piecesWhichCanCapturePlayerDown = PieceCaptureManager::whichPiecesCanCapture(Player::down, piecesPlacement_);

    EXPECT_EQ(piecesWhichCanCapturePlayerUp.size(), 3);
    EXPECT_EQ(piecesWhichCanCapturePlayerDown.size(), 3);
}
