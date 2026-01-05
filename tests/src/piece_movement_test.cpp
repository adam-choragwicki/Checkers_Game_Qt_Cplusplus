#include "common_test_fixture.h"
#include "piece_managers/piece_movement_manager.h"

class PieceMovementTest : public CommonTestFixture
{};

TEST_F(PieceMovementTest, CheckIfPieceCanMovePositive_PiecesInTheirFirstRows)
{
    setup({
        {{1, 4}, NORTH_PLAYER},
        {{1, 6}, NORTH_PLAYER},
        {{8, 3}, SOUTH_PLAYER},
        {{8, 5}, SOUTH_PLAYER}
    });

    for (auto& piece: piecesOnCheckerboard_)
    {
        EXPECT_TRUE(PieceMovementManager::checkIfPieceCanMove(*piece, piecesManager_));
    }
}

TEST_F(PieceMovementTest, CheckIfPieceCanMovePositive_PiecesInMiddleRows)
{
    setup({
        {{3, 4}, NORTH_PLAYER},
        {{3, 6}, NORTH_PLAYER},
        {{6, 3}, SOUTH_PLAYER},
        {{6, 5}, SOUTH_PLAYER}
    });

    for (auto& piece: piecesOnCheckerboard_)
    {
        EXPECT_TRUE(PieceMovementManager::checkIfPieceCanMove(*piece, piecesManager_));
    }
}

TEST_F(PieceMovementTest, CheckIfPieceCanMovePositive_PiecesInSideColumns)
{
    setup({
        {{3, 8}, NORTH_PLAYER},
        {{4, 1}, NORTH_PLAYER},
        {{5, 8}, SOUTH_PLAYER},
        {{6, 1}, SOUTH_PLAYER}
    });

    for (auto& piece: piecesOnCheckerboard_)
    {
        EXPECT_TRUE(PieceMovementManager::checkIfPieceCanMove(*piece, piecesManager_));
    }
}

TEST_F(PieceMovementTest, CheckIfPieceCanMovePositive_PiecesHalfBlockedByOtherFriendlyPieces)
{
    setup({
        {{3, 2}, NORTH_PLAYER},
        {{4, 3}, NORTH_PLAYER},
        {{3, 6}, NORTH_PLAYER},
        {{4, 5}, NORTH_PLAYER},
        {{7, 2}, SOUTH_PLAYER},
        {{6, 3}, SOUTH_PLAYER},
        {{7, 6}, SOUTH_PLAYER},
        {{6, 5}, SOUTH_PLAYER}
    });

    for (auto& piece: piecesOnCheckerboard_)
    {
        EXPECT_TRUE(PieceMovementManager::checkIfPieceCanMove(*piece, piecesManager_));
    }
}

TEST_F(PieceMovementTest, CheckIfPieceCanMovePositive_PiecesHalfBlockedByOtherEnemyPieces)
{
    setup({
        {{3, 2}, NORTH_PLAYER},
        {{4, 3}, SOUTH_PLAYER},
        {{3, 6}, NORTH_PLAYER},
        {{4, 5}, SOUTH_PLAYER},
        {{7, 2}, SOUTH_PLAYER},
        {{6, 3}, NORTH_PLAYER},
        {{7, 6}, SOUTH_PLAYER},
        {{6, 5}, NORTH_PLAYER}
    });

    for (auto& piece: piecesOnCheckerboard_)
    {
        EXPECT_TRUE(PieceMovementManager::checkIfPieceCanMove(*piece, piecesManager_));
    }
}

TEST_F(PieceMovementTest, CheckIfPiecesCanMoveNegative_PiecesInTheirLastRows)
{
    setup({
        {{8, 3}, NORTH_PLAYER},
        {{8, 5}, NORTH_PLAYER},
        {{1, 4}, SOUTH_PLAYER},
        {{1, 6}, SOUTH_PLAYER}
    });

    for (auto& piece: piecesOnCheckerboard_)
    {
        EXPECT_FALSE(PieceMovementManager::checkIfPieceCanMove(*piece, piecesManager_));
    }
}

TEST_F(PieceMovementTest, CheckIfPieceCanMoveNegative_PiecesBlockedInFrontByEnemyPiecesAndWall)
{
    setup({
        {{4, 1}, NORTH_PLAYER},
        {{4, 3}, NORTH_PLAYER},
        {{4, 5}, NORTH_PLAYER},
        {{4, 7}, NORTH_PLAYER},
        {{5, 2}, SOUTH_PLAYER},
        {{5, 4}, SOUTH_PLAYER},
        {{5, 6}, SOUTH_PLAYER},
        {{5, 8}, SOUTH_PLAYER}
    });

    for (auto& piece: piecesOnCheckerboard_)
    {
        EXPECT_FALSE(PieceMovementManager::checkIfPieceCanMove(*piece, piecesManager_));
    }
}

TEST_F(PieceMovementTest, CheckIfPieceCanMoveNegative_PiecesBlockedInFrontByFriendPiecesAndTheirLastRowWall)
{
    setup({
        {{1, 2}, SOUTH_PLAYER}, {{1, 4}, SOUTH_PLAYER}, {{1, 6}, SOUTH_PLAYER}, {{1, 8}, SOUTH_PLAYER},
        {{2, 1}, SOUTH_PLAYER}, {{2, 3}, SOUTH_PLAYER}, {{2, 5}, SOUTH_PLAYER}, {{2, 7}, SOUTH_PLAYER},
        {{7, 2}, NORTH_PLAYER}, {{7, 4}, NORTH_PLAYER}, {{7, 6}, NORTH_PLAYER}, {{7, 8}, NORTH_PLAYER},
        {{8, 1}, NORTH_PLAYER}, {{8, 3}, NORTH_PLAYER}, {{8, 5}, NORTH_PLAYER}, {{8, 7}, NORTH_PLAYER}
    });

    for (auto& piece: piecesOnCheckerboard_)
    {
        EXPECT_FALSE(PieceMovementManager::checkIfPieceCanMove(*piece, piecesManager_));
    }
}

TEST_F(PieceMovementTest, CheckMovePossibility1)
{
    setup({
        {{3, 4}, NORTH_PLAYER},
        {{6, 5}, SOUTH_PLAYER}
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
        {{4, 5}, NORTH_PLAYER},
        {{5, 4}, SOUTH_PLAYER}
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
        {{7, 2}, NORTH_PLAYER},
        {{8, 3}, NORTH_PLAYER},
        {{1, 2}, SOUTH_PLAYER},
        {{4, 5}, SOUTH_PLAYER},
        {{3, 4}, SOUTH_PLAYER},
        {{3, 6}, SOUTH_PLAYER}
    });

    std::vector<Piece*> piecesWhichCanMovePlayerUp = PieceMovementManager::whichPiecesCanMove(NORTH_PLAYER, piecesManager_);
    std::vector<Piece*> piecesWhichCanMovePlayerDown = PieceMovementManager::whichPiecesCanMove(SOUTH_PLAYER, piecesManager_);

    EXPECT_EQ(piecesWhichCanMovePlayerUp.size(), 1);
    EXPECT_EQ(piecesWhichCanMovePlayerDown.size(), 2);
}
