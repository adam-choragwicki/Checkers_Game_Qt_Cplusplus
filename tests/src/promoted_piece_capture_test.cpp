#include "common_test_fixture.h"
#include "piece_capture_manager.h"

class PromotedPieceCaptureTest : public CommonTestFixture
{};

TEST_F(PromotedPieceCaptureTest, CheckIfPieceCanCapturePositive_PlayerUpCaptureAllDirections)
{
    piecesParameters_ = {{{4, 3}, Player::UPPER, true},
                         {{3, 2}, Player::LOWER, true},
                         {{3, 4}, Player::LOWER, true},
                         {{5, 2}, Player::LOWER, true},
                         {{5, 4}, Player::LOWER, true}};

    placePiecesOnCheckerboard();

    EXPECT_TRUE(PieceCaptureManager::checkIfPieceCanCapture(*piecesOnCheckerboard_.at(0), piecesPlacement_));
    EXPECT_FALSE(PieceCaptureManager::checkIfPieceCanCapture(*piecesOnCheckerboard_.at(1), piecesPlacement_));
    EXPECT_FALSE(PieceCaptureManager::checkIfPieceCanCapture(*piecesOnCheckerboard_.at(2), piecesPlacement_));
    EXPECT_FALSE(PieceCaptureManager::checkIfPieceCanCapture(*piecesOnCheckerboard_.at(3), piecesPlacement_));
    EXPECT_FALSE(PieceCaptureManager::checkIfPieceCanCapture(*piecesOnCheckerboard_.at(4), piecesPlacement_));
}

TEST_F(PromotedPieceCaptureTest, CheckIfPieceCanCapturePositive_PlayerDownCaptureAllDirections)
{
    piecesParameters_ = {{{5, 6}, Player::UPPER, true},
                         {{4, 5}, Player::LOWER, true},
                         {{4, 7}, Player::LOWER, true},
                         {{6, 5}, Player::LOWER, true},
                         {{6, 7}, Player::LOWER, true}};

    placePiecesOnCheckerboard();

    EXPECT_TRUE(PieceCaptureManager::checkIfPieceCanCapture(*piecesOnCheckerboard_.at(0), piecesPlacement_));
    EXPECT_FALSE(PieceCaptureManager::checkIfPieceCanCapture(*piecesOnCheckerboard_.at(1), piecesPlacement_));
    EXPECT_FALSE(PieceCaptureManager::checkIfPieceCanCapture(*piecesOnCheckerboard_.at(2), piecesPlacement_));
    EXPECT_FALSE(PieceCaptureManager::checkIfPieceCanCapture(*piecesOnCheckerboard_.at(3), piecesPlacement_));
    EXPECT_FALSE(PieceCaptureManager::checkIfPieceCanCapture(*piecesOnCheckerboard_.at(4), piecesPlacement_));
}

TEST_F(PromotedPieceCaptureTest, CheckIfPieceCanCapturePositive_CaptureOnOneSideOtherSideWall)
{
    piecesParameters_ = {{{3, 2}, Player::UPPER, true},
                         {{3, 6}, Player::UPPER, true},
                         {{4, 3}, Player::LOWER, true},
                         {{4, 7}, Player::LOWER, true}};

    placePiecesOnCheckerboard();

    for(const auto& piece : piecesOnCheckerboard_)
    {
        EXPECT_TRUE(PieceCaptureManager::checkIfPieceCanCapture(*piece, piecesPlacement_));
    }
}

TEST_F(PromotedPieceCaptureTest, CheckIfPieceCanCapturePositive_CaptureOnBothSides)
{
    piecesParameters_ = {{{4, 3}, Player::UPPER, true},
                         {{4, 5}, Player::UPPER, true},
                         {{5, 4}, Player::LOWER, true},
                         {{5, 2}, Player::LOWER, true}};

    placePiecesOnCheckerboard();

    for(const auto& piece : piecesOnCheckerboard_)
    {
        EXPECT_TRUE(PieceCaptureManager::checkIfPieceCanCapture(*piece, piecesPlacement_));
    }
}

TEST_F(PromotedPieceCaptureTest, CheckIfPieceCanCaptureNegative_SideWallBehindPiece)
{
    piecesParameters_ = {{{2, 1}, Player::UPPER, true},
                         {{3, 2}, Player::LOWER, true},
                         {{4, 3}, Player::LOWER, true}};

    placePiecesOnCheckerboard();

    for(const auto& piece : piecesOnCheckerboard_)
    {
        EXPECT_FALSE(PieceCaptureManager::checkIfPieceCanCapture(*piece, piecesPlacement_));
    }
}

TEST_F(PromotedPieceCaptureTest, CheckIfPieceCanCaptureNegative_TopBottomAndSideWallBehindPiece)
{
    piecesParameters_ = {{{1, 2}, Player::UPPER, true},
                         {{7, 8}, Player::UPPER, true},
                         {{2, 1}, Player::LOWER, true},
                         {{8, 7}, Player::LOWER, true}};

    placePiecesOnCheckerboard();

    for(const auto& piece : piecesOnCheckerboard_)
    {
        EXPECT_FALSE(PieceCaptureManager::checkIfPieceCanCapture(*piece, piecesPlacement_));
    }
}

TEST_F(PromotedPieceCaptureTest, CheckIfPieceCanCaptureNegative_FriendlyPieceBehindPiece)
{
    piecesParameters_ = {{{3, 6}, Player::UPPER, true},
                         {{4, 5}, Player::UPPER, true},
                         {{5, 4}, Player::LOWER, true},
                         {{6, 3}, Player::LOWER, true}};

    placePiecesOnCheckerboard();

    for(const auto& piece : piecesOnCheckerboard_)
    {
        EXPECT_FALSE(PieceCaptureManager::checkIfPieceCanCapture(*piece, piecesPlacement_));
    }
}

TEST_F(PromotedPieceCaptureTest, CheckCapturePossibilityPlayerUp)
{
    piecesParameters_ = {{{5, 4}, Player::UPPER, true},
                         {{4, 3}, Player::LOWER, true},
                         {{4, 5}, Player::LOWER, true},
                         {{6, 3}, Player::LOWER, true},
                         {{6, 5}, Player::LOWER, true}};

    placePiecesOnCheckerboard();

    EXPECT_TRUE(PieceCaptureManager::checkCapturePossibility(*piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(3, 2)));
    EXPECT_TRUE(PieceCaptureManager::checkCapturePossibility(*piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(3, 6)));
    EXPECT_TRUE(PieceCaptureManager::checkCapturePossibility(*piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(7, 2)));
    EXPECT_TRUE(PieceCaptureManager::checkCapturePossibility(*piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(7, 6)));

    EXPECT_FALSE(PieceCaptureManager::checkCapturePossibility(*piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(2, 3)));
    EXPECT_FALSE(PieceCaptureManager::checkCapturePossibility(*piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(4, 1)));
    EXPECT_FALSE(PieceCaptureManager::checkCapturePossibility(*piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(2, 1)));
    EXPECT_FALSE(PieceCaptureManager::checkCapturePossibility(*piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(2, 3)));
    EXPECT_FALSE(PieceCaptureManager::checkCapturePossibility(*piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(4, 3)));
    EXPECT_FALSE(PieceCaptureManager::checkCapturePossibility(*piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(4, 5)));
    EXPECT_FALSE(PieceCaptureManager::checkCapturePossibility(*piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(6, 3)));
    EXPECT_FALSE(PieceCaptureManager::checkCapturePossibility(*piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(6, 5)));
    EXPECT_FALSE(PieceCaptureManager::checkCapturePossibility(*piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(3, 4)));
    EXPECT_FALSE(PieceCaptureManager::checkCapturePossibility(*piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(5, 2)));
    EXPECT_FALSE(PieceCaptureManager::checkCapturePossibility(*piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(5, 6)));
    EXPECT_FALSE(PieceCaptureManager::checkCapturePossibility(*piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(7, 4)));
}

TEST_F(PromotedPieceCaptureTest, CheckCapturePossibilityPlayerDown)
{
    piecesParameters_ = {{{5, 4}, Player::LOWER, true},
                         {{4, 3}, Player::UPPER, true},
                         {{4, 5}, Player::UPPER, true},
                         {{6, 3}, Player::UPPER, true},
                         {{6, 5}, Player::UPPER, true}};

    placePiecesOnCheckerboard();

    EXPECT_TRUE(PieceCaptureManager::checkCapturePossibility(*piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(3, 2)));
    EXPECT_TRUE(PieceCaptureManager::checkCapturePossibility(*piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(3, 6)));
    EXPECT_TRUE(PieceCaptureManager::checkCapturePossibility(*piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(7, 2)));
    EXPECT_TRUE(PieceCaptureManager::checkCapturePossibility(*piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(7, 6)));

    EXPECT_FALSE(PieceCaptureManager::checkCapturePossibility(*piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(2, 3)));
    EXPECT_FALSE(PieceCaptureManager::checkCapturePossibility(*piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(4, 1)));
    EXPECT_FALSE(PieceCaptureManager::checkCapturePossibility(*piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(2, 1)));
    EXPECT_FALSE(PieceCaptureManager::checkCapturePossibility(*piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(2, 3)));
    EXPECT_FALSE(PieceCaptureManager::checkCapturePossibility(*piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(4, 3)));
    EXPECT_FALSE(PieceCaptureManager::checkCapturePossibility(*piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(4, 5)));
    EXPECT_FALSE(PieceCaptureManager::checkCapturePossibility(*piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(6, 3)));
    EXPECT_FALSE(PieceCaptureManager::checkCapturePossibility(*piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(6, 5)));
    EXPECT_FALSE(PieceCaptureManager::checkCapturePossibility(*piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(3, 4)));
    EXPECT_FALSE(PieceCaptureManager::checkCapturePossibility(*piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(5, 2)));
    EXPECT_FALSE(PieceCaptureManager::checkCapturePossibility(*piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(5, 6)));
    EXPECT_FALSE(PieceCaptureManager::checkCapturePossibility(*piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(7, 4)));
}

TEST_F(PromotedPieceCaptureTest, WhichPiecesCanCapture)
{
    piecesParameters_ = {{{3, 4}, Player::UPPER, true},
                         {{3, 6}, Player::UPPER, true},
                         {{8, 3}, Player::UPPER, true},
                         {{4, 3}, Player::LOWER, true},
                         {{4, 5}, Player::LOWER, true},
                         {{4, 7}, Player::LOWER, true},
                         {{7, 2}, Player::LOWER, true}};

    placePiecesOnCheckerboard();

    std::vector<Piece*> piecesWhichCanCapturePlayerUp = PieceCaptureManager::whichPiecesCanCapture(Player::UPPER, piecesPlacement_);
    std::vector<Piece*> piecesWhichCanCapturePlayerDown = PieceCaptureManager::whichPiecesCanCapture(Player::LOWER, piecesPlacement_);

    EXPECT_EQ(piecesWhichCanCapturePlayerUp.size(), 3);
    EXPECT_EQ(piecesWhichCanCapturePlayerDown.size(), 3);
}
