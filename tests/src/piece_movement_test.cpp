#include "common_test_fixture.h"
#include "piece_movement_manager.h"

class PieceMovementTest : public CommonTestFixture
{};

TEST_F(PieceMovementTest, CheckIfPieceCanMovePositive_PiecesInTheirFirstRows)
{
    setup({
        {{1, 4}, Player::NORTH},
        {{1, 6}, Player::NORTH},
        {{8, 3}, Player::SOUTH},
        {{8, 5}, Player::SOUTH}
    });

    for (auto& piece: piecesOnCheckerboard_)
    {
        EXPECT_TRUE(PieceMovementManager::checkIfPieceCanMove(*piece, piecesManager_));
    }
}

TEST_F(PieceMovementTest, CheckIfPieceCanMovePositive_PiecesInMiddleRows)
{
    setup({
        {{3, 4}, Player::NORTH},
        {{3, 6}, Player::NORTH},
        {{6, 3}, Player::SOUTH},
        {{6, 5}, Player::SOUTH}
    });

    for (auto& piece: piecesOnCheckerboard_)
    {
        EXPECT_TRUE(PieceMovementManager::checkIfPieceCanMove(*piece, piecesManager_));
    }
}

TEST_F(PieceMovementTest, CheckIfPieceCanMovePositive_PiecesInSideColumns)
{
    setup({
        {{3, 8}, Player::NORTH},
        {{4, 1}, Player::NORTH},
        {{5, 8}, Player::SOUTH},
        {{6, 1}, Player::SOUTH}
    });

    for (auto& piece: piecesOnCheckerboard_)
    {
        EXPECT_TRUE(PieceMovementManager::checkIfPieceCanMove(*piece, piecesManager_));
    }
}

TEST_F(PieceMovementTest, CheckIfPieceCanMovePositive_PiecesHalfBlockedByOtherFriendlyPieces)
{
    setup({
        {{3, 2}, Player::NORTH},
        {{4, 3}, Player::NORTH},
        {{3, 6}, Player::NORTH},
        {{4, 5}, Player::NORTH},
        {{7, 2}, Player::SOUTH},
        {{6, 3}, Player::SOUTH},
        {{7, 6}, Player::SOUTH},
        {{6, 5}, Player::SOUTH}
    });

    for (auto& piece: piecesOnCheckerboard_)
    {
        EXPECT_TRUE(PieceMovementManager::checkIfPieceCanMove(*piece, piecesManager_));
    }
}

TEST_F(PieceMovementTest, CheckIfPieceCanMovePositive_PiecesHalfBlockedByOtherEnemyPieces)
{
    setup({
        {{3, 2}, Player::NORTH},
        {{4, 3}, Player::SOUTH},
        {{3, 6}, Player::NORTH},
        {{4, 5}, Player::SOUTH},
        {{7, 2}, Player::SOUTH},
        {{6, 3}, Player::NORTH},
        {{7, 6}, Player::SOUTH},
        {{6, 5}, Player::NORTH}
    });

    for (auto& piece: piecesOnCheckerboard_)
    {
        EXPECT_TRUE(PieceMovementManager::checkIfPieceCanMove(*piece, piecesManager_));
    }
}

TEST_F(PieceMovementTest, CheckIfPiecesCanMoveNegative_PiecesInTheirLastRows)
{
    setup({
        {{8, 3}, Player::NORTH},
        {{8, 5}, Player::NORTH},
        {{1, 4}, Player::SOUTH},
        {{1, 6}, Player::SOUTH}
    });

    for (auto& piece: piecesOnCheckerboard_)
    {
        EXPECT_FALSE(PieceMovementManager::checkIfPieceCanMove(*piece, piecesManager_));
    }
}

TEST_F(PieceMovementTest, CheckIfPieceCanMoveNegative_PiecesBlockedInFrontByEnemyPiecesAndWall)
{
    setup({
        {{4, 1}, Player::NORTH},
        {{4, 3}, Player::NORTH},
        {{4, 5}, Player::NORTH},
        {{4, 7}, Player::NORTH},
        {{5, 2}, Player::SOUTH},
        {{5, 4}, Player::SOUTH},
        {{5, 6}, Player::SOUTH},
        {{5, 8}, Player::SOUTH}
    });

    for (auto& piece: piecesOnCheckerboard_)
    {
        EXPECT_FALSE(PieceMovementManager::checkIfPieceCanMove(*piece, piecesManager_));
    }
}

TEST_F(PieceMovementTest, CheckIfPieceCanMoveNegative_PiecesBlockedInFrontByFriendPiecesAndTheirLastRowWall)
{
    setup({
        {{1, 2}, Player::SOUTH}, {{1, 4}, Player::SOUTH}, {{1, 6}, Player::SOUTH}, {{1, 8}, Player::SOUTH},
        {{2, 1}, Player::SOUTH}, {{2, 3}, Player::SOUTH}, {{2, 5}, Player::SOUTH}, {{2, 7}, Player::SOUTH},
        {{7, 2}, Player::NORTH}, {{7, 4}, Player::NORTH}, {{7, 6}, Player::NORTH}, {{7, 8}, Player::NORTH},
        {{8, 1}, Player::NORTH}, {{8, 3}, Player::NORTH}, {{8, 5}, Player::NORTH}, {{8, 7}, Player::NORTH}
    });

    for (auto& piece: piecesOnCheckerboard_)
    {
        EXPECT_FALSE(PieceMovementManager::checkIfPieceCanMove(*piece, piecesManager_));
    }
}

TEST_F(PieceMovementTest, CheckMovePossibility1)
{
    setup({
        {{3, 4}, Player::NORTH},
        {{6, 5}, Player::SOUTH}
    });

    EXPECT_TRUE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(0), piecesManager_, Coordinates(4, 3)));
    EXPECT_TRUE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(0), piecesManager_, Coordinates(4, 5)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(0), piecesManager_, Coordinates(2, 3)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(0), piecesManager_, Coordinates(2, 5)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(0), piecesManager_, Coordinates(1, 2)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(0), piecesManager_, Coordinates(1, 6)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(0), piecesManager_, Coordinates(5, 2)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(0), piecesManager_, Coordinates(5, 6)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(0), piecesManager_, Coordinates(3, 2)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(0), piecesManager_, Coordinates(3, 6)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(0), piecesManager_, Coordinates(1, 4)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(0), piecesManager_, Coordinates(5, 4)));

    EXPECT_TRUE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(1), piecesManager_, Coordinates(5, 4)));
    EXPECT_TRUE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(1), piecesManager_, Coordinates(5, 6)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(1), piecesManager_, Coordinates(7, 4)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(1), piecesManager_, Coordinates(7, 6)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(1), piecesManager_, Coordinates(4, 3)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(1), piecesManager_, Coordinates(4, 7)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(1), piecesManager_, Coordinates(8, 3)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(1), piecesManager_, Coordinates(8, 7)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(1), piecesManager_, Coordinates(4, 5)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(1), piecesManager_, Coordinates(8, 5)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(1), piecesManager_, Coordinates(6, 3)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(1), piecesManager_, Coordinates(6, 7)));
}

TEST_F(PieceMovementTest, CheckMovePossibility2)
{
    setup({
        {{4, 5}, Player::NORTH},
        {{5, 4}, Player::SOUTH}
    });

    EXPECT_TRUE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(0), piecesManager_, Coordinates(5, 6)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(0), piecesManager_, Coordinates(5, 4)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(0), piecesManager_, Coordinates(3, 4)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(0), piecesManager_, Coordinates(3, 6)));

    EXPECT_TRUE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(1), piecesManager_, Coordinates(4, 3)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(1), piecesManager_, Coordinates(4, 5)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(1), piecesManager_, Coordinates(6, 3)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(1), piecesManager_, Coordinates(6, 5)));
}

TEST_F(PieceMovementTest, WhichPiecesCanMove)
{
    setup({
        {{7, 2}, Player::NORTH},
        {{8, 3}, Player::NORTH},
        {{1, 2}, Player::SOUTH},
        {{4, 5}, Player::SOUTH},
        {{3, 4}, Player::SOUTH},
        {{3, 6}, Player::SOUTH}
    });

    std::vector<Piece*> piecesWhichCanMovePlayerUp = PieceMovementManager::whichPiecesCanMove(Player::NORTH, piecesManager_);
    std::vector<Piece*> piecesWhichCanMovePlayerDown = PieceMovementManager::whichPiecesCanMove(Player::SOUTH, piecesManager_);

    EXPECT_EQ(piecesWhichCanMovePlayerUp.size(), 1);
    EXPECT_EQ(piecesWhichCanMovePlayerDown.size(), 2);
}
