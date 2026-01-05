#include "common_test_fixture.h"
#include "piece_managers/piece_movement_manager.h"

class PromotedPieceMovementTest : public CommonTestFixture
{};

TEST_F(PromotedPieceMovementTest, CheckIfPieceCanMovePositive_PiecesInTheirFirstRows)
{
    setup({
        {{1, 4}, NORTH_PLAYER, true},
        {{1, 6}, NORTH_PLAYER, true},
        {{8, 3}, SOUTH_PLAYER, true},
        {{8, 5}, SOUTH_PLAYER, true}
    });

    for (auto& piece: piecesOnCheckerboard_)
    {
        EXPECT_TRUE(PieceMovementManager::checkIfPieceCanMove(*piece, piecesManager_));
    }
}

TEST_F(PromotedPieceMovementTest, CheckIfPieceCanMovePositive_PiecesInMiddleRows)
{
    setup({
        {{3, 4}, NORTH_PLAYER, true},
        {{3, 6}, NORTH_PLAYER, true},
        {{6, 3}, SOUTH_PLAYER, true},
        {{6, 5}, SOUTH_PLAYER, true}
    });

    for (auto& piece: piecesOnCheckerboard_)
    {
        EXPECT_TRUE(PieceMovementManager::checkIfPieceCanMove(*piece, piecesManager_));
    }
}

TEST_F(PromotedPieceMovementTest, CheckIfPieceCanMovePositive_PiecesInSideColumns)
{
    setup({
        {{3, 8}, NORTH_PLAYER, true},
        {{4, 1}, NORTH_PLAYER, true},
        {{5, 8}, SOUTH_PLAYER, true},
        {{6, 1}, SOUTH_PLAYER, true}
    });

    for (auto& piece: piecesOnCheckerboard_)
    {
        EXPECT_TRUE(PieceMovementManager::checkIfPieceCanMove(*piece, piecesManager_));
    }
}

TEST_F(PromotedPieceMovementTest, CheckIfPieceCanMovePositive_PiecesHalfBlockedByOtherFriendlyPieces)
{
    setup({
        {{3, 2}, NORTH_PLAYER, true},
        {{4, 3}, NORTH_PLAYER, true},
        {{3, 6}, NORTH_PLAYER, true},
        {{4, 5}, NORTH_PLAYER, true},
        {{7, 2}, SOUTH_PLAYER, true},
        {{6, 3}, SOUTH_PLAYER, true},
        {{7, 6}, SOUTH_PLAYER, true},
        {{6, 5}, SOUTH_PLAYER, true}
    });

    for (auto& piece: piecesOnCheckerboard_)
    {
        EXPECT_TRUE(PieceMovementManager::checkIfPieceCanMove(*piece, piecesManager_));
    }
}

TEST_F(PromotedPieceMovementTest, CheckIfPieceCanMovePositive_PiecesHalfBlockedByOtherEnemyPieces)
{
    setup({
        {{3, 2}, NORTH_PLAYER, true},
        {{4, 3}, SOUTH_PLAYER, true},
        {{3, 6}, NORTH_PLAYER, true},
        {{4, 5}, SOUTH_PLAYER, true},
        {{7, 2}, SOUTH_PLAYER, true},
        {{6, 3}, NORTH_PLAYER, true},
        {{7, 6}, SOUTH_PLAYER, true},
        {{6, 5}, NORTH_PLAYER, true}
    });

    for (auto& piece: piecesOnCheckerboard_)
    {
        EXPECT_TRUE(PieceMovementManager::checkIfPieceCanMove(*piece, piecesManager_));
    }
}

TEST_F(PromotedPieceMovementTest, CheckIfPiecesCanMovePositive_PiecesInTheirLastRows)
{
    setup({
        {{8, 3}, NORTH_PLAYER, true},
        {{8, 5}, NORTH_PLAYER, true},
        {{1, 4}, SOUTH_PLAYER, true},
        {{1, 6}, SOUTH_PLAYER, true}
    });

    for (auto& piece: piecesOnCheckerboard_)
    {
        EXPECT_TRUE(PieceMovementManager::checkIfPieceCanMove(*piece, piecesManager_));
    }
}

TEST_F(PromotedPieceMovementTest, CheckIfPieceCanMovePositive_PiecesBlockedInFrontByEnemyPiecesAndWall)
{
    setup({
        {{4, 1}, NORTH_PLAYER, true},
        {{4, 3}, NORTH_PLAYER, true},
        {{4, 5}, NORTH_PLAYER, true},
        {{4, 7}, NORTH_PLAYER, true},
        {{5, 2}, SOUTH_PLAYER, true},
        {{5, 4}, SOUTH_PLAYER, true},
        {{5, 6}, SOUTH_PLAYER, true},
        {{5, 8}, SOUTH_PLAYER, true}
    });

    for (auto& piece: piecesOnCheckerboard_)
    {
        EXPECT_TRUE(PieceMovementManager::checkIfPieceCanMove(*piece, piecesManager_));
    }
}

TEST_F(PromotedPieceMovementTest, CheckMovePossibility1)
{
    setup({
        {{3, 4}, NORTH_PLAYER, true},
        {{6, 5}, SOUTH_PLAYER, true}
    });

    const std::vector<Coordinates> targetsPlayer1True = {{4, 3}, {4, 5}, {2, 3}, {2, 5}};
    const std::vector<Coordinates> targetsPlayer1False = {{1, 2}, {1, 6}, {5, 2}, {5, 6}, {3, 2}, {3, 6}, {1, 4}, {5, 4}};

    for (auto& target: targetsPlayer1True)
    {
        EXPECT_TRUE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(0), piecesManager_, target));
    }

    for (auto& target: targetsPlayer1False)
    {
        EXPECT_FALSE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(0), piecesManager_, target));
    }

    const std::vector<Coordinates> targetsPlayer2True = {{5, 4}, {5, 6}, {7, 4}, {7, 6}};
    const std::vector<Coordinates> targetsPlayer2False = {{4, 3}, {4, 7}, {8, 3}, {8, 7}, {4, 5}, {8, 5}, {6, 3}, {6, 7}};

    for (auto& target: targetsPlayer2True)
    {
        EXPECT_TRUE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(1), piecesManager_, target));
    }

    for (auto& target: targetsPlayer2False)
    {
        EXPECT_FALSE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(1), piecesManager_, target));
    }
}

TEST_F(PromotedPieceMovementTest, CheckMovePossibility2)
{
    setup({
        {{4, 5}, NORTH_PLAYER, true},
        {{5, 4}, SOUTH_PLAYER, true}
    });

    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(0), piecesManager_, {5, 4}));
    EXPECT_TRUE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(0), piecesManager_, {5, 6}));
    EXPECT_TRUE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(0), piecesManager_, {3, 4}));
    EXPECT_TRUE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(0), piecesManager_, {3, 6}));

    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(1), piecesManager_, {4, 5}));
    EXPECT_TRUE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(1), piecesManager_, {4, 3}));
    EXPECT_TRUE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(1), piecesManager_, {6, 3}));
    EXPECT_TRUE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(1), piecesManager_, {6, 5}));
}

TEST_F(PromotedPieceMovementTest, WhichPiecesCanMove)
{
    setup({
        {{7, 2}, NORTH_PLAYER, true},
        {{8, 3}, NORTH_PLAYER, true},
        {{1, 2}, SOUTH_PLAYER, true},
        {{4, 5}, SOUTH_PLAYER, true},
        {{3, 4}, SOUTH_PLAYER, true},
        {{3, 6}, SOUTH_PLAYER, true}
    });

    std::vector<Piece*> piecesWhichCanMovePlayerUp = PieceMovementManager::whichPiecesCanMove(NORTH_PLAYER, piecesManager_);
    std::vector<Piece*> piecesWhichCanMovePlayerDown = PieceMovementManager::whichPiecesCanMove(SOUTH_PLAYER, piecesManager_);

    EXPECT_EQ(piecesWhichCanMovePlayerUp.size(), 2);
    EXPECT_EQ(piecesWhichCanMovePlayerDown.size(), 4);
}
