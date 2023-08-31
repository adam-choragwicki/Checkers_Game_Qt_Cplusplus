#include "common_test_fixture.h"
#include "piece_movement_manager.h"

class PromotedPieceMovementTest : public CommonTestFixture
{};

TEST_F(PromotedPieceMovementTest, CheckIfPieceCanMovePositive_PiecesInTheirFirstRows)
{
    piecesParameters_ = {{{1, 4}, Player::UPPER, true},
                         {{1, 6}, Player::UPPER, true},
                         {{8, 3}, Player::LOWER, true},
                         {{8, 5}, Player::LOWER, true}};

    placePiecesOnCheckerboard();

    for(auto& piece : piecesOnCheckerboard_)
    {
        EXPECT_TRUE(PieceMovementManager::checkIfPieceCanMove(*piece, piecesPlacement_));
    }
}

TEST_F(PromotedPieceMovementTest, CheckIfPieceCanMovePositive_PiecesInMiddleRows)
{
    piecesParameters_ = {{{3, 4}, Player::UPPER, true},
                         {{3, 6}, Player::UPPER, true},
                         {{6, 3}, Player::LOWER, true},
                         {{6, 5}, Player::LOWER, true}};

    placePiecesOnCheckerboard();

    for(auto& piece : piecesOnCheckerboard_)
    {
        EXPECT_TRUE(PieceMovementManager::checkIfPieceCanMove(*piece, piecesPlacement_));
    }
}

TEST_F(PromotedPieceMovementTest, CheckIfPieceCanMovePositive_PiecesInSideColumns)
{
    piecesParameters_ = {{{3, 8}, Player::UPPER, true},
                         {{4, 1}, Player::UPPER, true},
                         {{5, 8}, Player::LOWER, true},
                         {{6, 1}, Player::LOWER, true}};

    placePiecesOnCheckerboard();

    for(auto& piece : piecesOnCheckerboard_)
    {
        EXPECT_TRUE(PieceMovementManager::checkIfPieceCanMove(*piece, piecesPlacement_));
    }
}

TEST_F(PromotedPieceMovementTest, CheckIfPieceCanMovePositive_PiecesHalfBlockedByOtherFriendlyPieces)
{
    piecesParameters_ = {{{3, 2}, Player::UPPER, true},
                         {{4, 3}, Player::UPPER, true},
                         {{3, 6}, Player::UPPER, true},
                         {{4, 5}, Player::UPPER, true},
                         {{7, 2}, Player::LOWER, true},
                         {{6, 3}, Player::LOWER, true},
                         {{7, 6}, Player::LOWER, true},
                         {{6, 5}, Player::LOWER, true}};

    placePiecesOnCheckerboard();

    for(auto& piece : piecesOnCheckerboard_)
    {
        EXPECT_TRUE(PieceMovementManager::checkIfPieceCanMove(*piece, piecesPlacement_));
    }
}

TEST_F(PromotedPieceMovementTest, CheckIfPieceCanMovePositive_PiecesHalfBlockedByOtherEnemyPieces)
{
    piecesParameters_ = {{{3, 2}, Player::UPPER, true},
                         {{4, 3}, Player::LOWER, true},
                         {{3, 6}, Player::UPPER, true},
                         {{4, 5}, Player::LOWER, true},
                         {{7, 2}, Player::LOWER, true},
                         {{6, 3}, Player::UPPER, true},
                         {{7, 6}, Player::LOWER, true},
                         {{6, 5}, Player::UPPER, true}};

    placePiecesOnCheckerboard();

    for(auto& piece : piecesOnCheckerboard_)
    {
        EXPECT_TRUE(PieceMovementManager::checkIfPieceCanMove(*piece, piecesPlacement_));
    }
}

TEST_F(PromotedPieceMovementTest, CheckIfPiecesCanMovePositive_PiecesInTheirLastRows)
{
    piecesParameters_ = {{{8, 3}, Player::UPPER, true},
                         {{8, 5}, Player::UPPER, true},
                         {{1, 4}, Player::LOWER, true},
                         {{1, 6}, Player::LOWER, true}};

    placePiecesOnCheckerboard();

    for(auto& piece : piecesOnCheckerboard_)
    {
        EXPECT_TRUE(PieceMovementManager::checkIfPieceCanMove(*piece, piecesPlacement_));
    }
}

TEST_F(PromotedPieceMovementTest, CheckIfPieceCanMovePositive_PiecesBlockedInFrontByEnemyPiecesAndWall)
{
    piecesParameters_ = {{{4, 1}, Player::UPPER, true},
                         {{4, 3}, Player::UPPER, true},
                         {{4, 5}, Player::UPPER, true},
                         {{4, 7}, Player::UPPER, true},
                         {{5, 2}, Player::LOWER, true},
                         {{5, 4}, Player::LOWER, true},
                         {{5, 6}, Player::LOWER, true},
                         {{5, 8}, Player::LOWER, true}};

    placePiecesOnCheckerboard();

    for(auto& piece : piecesOnCheckerboard_)
    {
        EXPECT_TRUE(PieceMovementManager::checkIfPieceCanMove(*piece, piecesPlacement_));
    }
}

TEST_F(PromotedPieceMovementTest, CheckMovePossibility1)
{
    piecesParameters_ = {{{3, 4}, Player::UPPER, true},
                         {{6, 5}, Player::LOWER, true}};

    placePiecesOnCheckerboard();

    EXPECT_TRUE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(4, 3)));
    EXPECT_TRUE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(4, 5)));
    EXPECT_TRUE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(2, 3)));
    EXPECT_TRUE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(2, 5)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(1, 2)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(1, 6)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(5, 2)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(5, 6)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(3, 2)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(3, 6)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(1, 4)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(5, 4)));

    EXPECT_TRUE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(1), piecesPlacement_, Coordinates(5, 4)));
    EXPECT_TRUE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(1), piecesPlacement_, Coordinates(5, 6)));
    EXPECT_TRUE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(1), piecesPlacement_, Coordinates(7, 4)));
    EXPECT_TRUE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(1), piecesPlacement_, Coordinates(7, 6)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(1), piecesPlacement_, Coordinates(4, 3)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(1), piecesPlacement_, Coordinates(4, 7)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(1), piecesPlacement_, Coordinates(8, 3)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(1), piecesPlacement_, Coordinates(8, 7)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(1), piecesPlacement_, Coordinates(4, 5)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(1), piecesPlacement_, Coordinates(8, 5)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(1), piecesPlacement_, Coordinates(6, 3)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(1), piecesPlacement_, Coordinates(6, 7)));
}

TEST_F(PromotedPieceMovementTest, CheckMovePossibility2)
{
    piecesParameters_ = {{{4, 5}, Player::UPPER, true},
                         {{5, 4}, Player::LOWER, true}};

    placePiecesOnCheckerboard();

    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(5, 4)));
    EXPECT_TRUE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(5, 6)));
    EXPECT_TRUE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(3, 4)));
    EXPECT_TRUE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(3, 6)));

    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(1), piecesPlacement_, Coordinates(4, 5)));
    EXPECT_TRUE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(1), piecesPlacement_, Coordinates(4, 3)));
    EXPECT_TRUE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(1), piecesPlacement_, Coordinates(6, 3)));
    EXPECT_TRUE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(1), piecesPlacement_, Coordinates(6, 5)));
}

TEST_F(PromotedPieceMovementTest, WhichPiecesCanMove)
{
    piecesParameters_ = {{{7, 2}, Player::UPPER, true},
                         {{8, 3}, Player::UPPER, true},
                         {{1, 2}, Player::LOWER, true},
                         {{4, 5}, Player::LOWER, true},
                         {{3, 4}, Player::LOWER, true},
                         {{3, 6}, Player::LOWER, true}};

    placePiecesOnCheckerboard();

    std::vector<Piece*> piecesWhichCanMovePlayerUp = PieceMovementManager::whichPiecesCanMove(Player::UPPER, piecesPlacement_);
    std::vector<Piece*> piecesWhichCanMovePlayerDown = PieceMovementManager::whichPiecesCanMove(Player::LOWER, piecesPlacement_);

    EXPECT_EQ(piecesWhichCanMovePlayerUp.size(), 2);
    EXPECT_EQ(piecesWhichCanMovePlayerDown.size(), 4);
}
