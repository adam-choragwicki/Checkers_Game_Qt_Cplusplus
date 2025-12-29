#include "common_test_fixture.h"
#include "piece_movement_manager.h"

class PromotedPieceMovementTest : public CommonTestFixture
{};

TEST_F(PromotedPieceMovementTest, CheckIfPieceCanMovePositive_PiecesInTheirFirstRows)
{
    setup({
        {{1, 4}, Player::NORTH, true},
        {{1, 6}, Player::NORTH, true},
        {{8, 3}, Player::SOUTH, true},
        {{8, 5}, Player::SOUTH, true}
    });

    for (auto& piece: piecesOnCheckerboard_)
    {
        EXPECT_TRUE(PieceMovementManager::checkIfPieceCanMove(*piece, piecesManager_));
    }
}

TEST_F(PromotedPieceMovementTest, CheckIfPieceCanMovePositive_PiecesInMiddleRows)
{
    setup({
        {{3, 4}, Player::NORTH, true},
        {{3, 6}, Player::NORTH, true},
        {{6, 3}, Player::SOUTH, true},
        {{6, 5}, Player::SOUTH, true}
    });

    for (auto& piece: piecesOnCheckerboard_)
    {
        EXPECT_TRUE(PieceMovementManager::checkIfPieceCanMove(*piece, piecesManager_));
    }
}

TEST_F(PromotedPieceMovementTest, CheckIfPieceCanMovePositive_PiecesInSideColumns)
{
    setup({
        {{3, 8}, Player::NORTH, true},
        {{4, 1}, Player::NORTH, true},
        {{5, 8}, Player::SOUTH, true},
        {{6, 1}, Player::SOUTH, true}
    });

    for (auto& piece: piecesOnCheckerboard_)
    {
        EXPECT_TRUE(PieceMovementManager::checkIfPieceCanMove(*piece, piecesManager_));
    }
}

TEST_F(PromotedPieceMovementTest, CheckIfPieceCanMovePositive_PiecesHalfBlockedByOtherFriendlyPieces)
{
    setup({
        {{3, 2}, Player::NORTH, true},
        {{4, 3}, Player::NORTH, true},
        {{3, 6}, Player::NORTH, true},
        {{4, 5}, Player::NORTH, true},
        {{7, 2}, Player::SOUTH, true},
        {{6, 3}, Player::SOUTH, true},
        {{7, 6}, Player::SOUTH, true},
        {{6, 5}, Player::SOUTH, true}
    });

    for (auto& piece: piecesOnCheckerboard_)
    {
        EXPECT_TRUE(PieceMovementManager::checkIfPieceCanMove(*piece, piecesManager_));
    }
}

TEST_F(PromotedPieceMovementTest, CheckIfPieceCanMovePositive_PiecesHalfBlockedByOtherEnemyPieces)
{
    setup({
        {{3, 2}, Player::NORTH, true},
        {{4, 3}, Player::SOUTH, true},
        {{3, 6}, Player::NORTH, true},
        {{4, 5}, Player::SOUTH, true},
        {{7, 2}, Player::SOUTH, true},
        {{6, 3}, Player::NORTH, true},
        {{7, 6}, Player::SOUTH, true},
        {{6, 5}, Player::NORTH, true}
    });

    for (auto& piece: piecesOnCheckerboard_)
    {
        EXPECT_TRUE(PieceMovementManager::checkIfPieceCanMove(*piece, piecesManager_));
    }
}

TEST_F(PromotedPieceMovementTest, CheckIfPiecesCanMovePositive_PiecesInTheirLastRows)
{
    setup({
        {{8, 3}, Player::NORTH, true},
        {{8, 5}, Player::NORTH, true},
        {{1, 4}, Player::SOUTH, true},
        {{1, 6}, Player::SOUTH, true}
    });

    for (auto& piece: piecesOnCheckerboard_)
    {
        EXPECT_TRUE(PieceMovementManager::checkIfPieceCanMove(*piece, piecesManager_));
    }
}

TEST_F(PromotedPieceMovementTest, CheckIfPieceCanMovePositive_PiecesBlockedInFrontByEnemyPiecesAndWall)
{
    setup({
        {{4, 1}, Player::NORTH, true},
        {{4, 3}, Player::NORTH, true},
        {{4, 5}, Player::NORTH, true},
        {{4, 7}, Player::NORTH, true},
        {{5, 2}, Player::SOUTH, true},
        {{5, 4}, Player::SOUTH, true},
        {{5, 6}, Player::SOUTH, true},
        {{5, 8}, Player::SOUTH, true}
    });

    for (auto& piece: piecesOnCheckerboard_)
    {
        EXPECT_TRUE(PieceMovementManager::checkIfPieceCanMove(*piece, piecesManager_));
    }
}

TEST_F(PromotedPieceMovementTest, CheckMovePossibility1)
{
    setup({
        {{3, 4}, Player::NORTH, true},
        {{6, 5}, Player::SOUTH, true}
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
        {{4, 5}, Player::NORTH, true},
        {{5, 4}, Player::SOUTH, true}
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
        {{7, 2}, Player::NORTH, true},
        {{8, 3}, Player::NORTH, true},
        {{1, 2}, Player::SOUTH, true},
        {{4, 5}, Player::SOUTH, true},
        {{3, 4}, Player::SOUTH, true},
        {{3, 6}, Player::SOUTH, true}
    });

    std::vector<Piece*> piecesWhichCanMovePlayerUp = PieceMovementManager::whichPiecesCanMove(Player::NORTH, piecesManager_);
    std::vector<Piece*> piecesWhichCanMovePlayerDown = PieceMovementManager::whichPiecesCanMove(Player::SOUTH, piecesManager_);

    EXPECT_EQ(piecesWhichCanMovePlayerUp.size(), 2);
    EXPECT_EQ(piecesWhichCanMovePlayerDown.size(), 4);
}
