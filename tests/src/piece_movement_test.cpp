#include "common_test_fixture.h"
#include "piece_movement_manager.h"

class PieceMovementTest : public CommonTestFixture
{};

TEST_F(PieceMovementTest, CheckIfPieceCanMovePositive_PiecesInTheirFirstRows)
{
    piecesPlacement_.createPiece(Coordinates(1, 4), Player::UPPER);
    piecesPlacement_.createPiece(Coordinates(1, 6), Player::UPPER);

    piecesPlacement_.createPiece(Coordinates(8, 3), Player::LOWER);
    piecesPlacement_.createPiece(Coordinates(8, 5), Player::LOWER);

    placePiecesOnCheckerboard();

    for(auto& piece : piecesOnCheckerboard_)
    {
        EXPECT_TRUE(PieceMovementManager::checkIfPieceCanMove(*piece, piecesPlacement_));
    }
}

TEST_F(PieceMovementTest, CheckIfPieceCanMovePositive_PiecesInMiddleRows)
{
    piecesPlacement_.createPiece(Coordinates(3, 4), Player::UPPER);
    piecesPlacement_.createPiece(Coordinates(3, 6), Player::UPPER);

    piecesPlacement_.createPiece(Coordinates(6, 3), Player::LOWER);
    piecesPlacement_.createPiece(Coordinates(6, 5), Player::LOWER);

    placePiecesOnCheckerboard();

    for(auto& piece : piecesOnCheckerboard_)
    {
        EXPECT_TRUE(PieceMovementManager::checkIfPieceCanMove(*piece, piecesPlacement_));
    }
}

TEST_F(PieceMovementTest, CheckIfPieceCanMovePositive_PiecesInSideColumns)
{
    piecesPlacement_.createPiece(Coordinates(3, 8), Player::UPPER);
    piecesPlacement_.createPiece(Coordinates(4, 1), Player::UPPER);

    piecesPlacement_.createPiece(Coordinates(5, 8), Player::LOWER);
    piecesPlacement_.createPiece(Coordinates(6, 1), Player::LOWER);

    placePiecesOnCheckerboard();

    for(auto& piece : piecesOnCheckerboard_)
    {
        EXPECT_TRUE(PieceMovementManager::checkIfPieceCanMove(*piece, piecesPlacement_));
    }
}

TEST_F(PieceMovementTest, CheckIfPieceCanMovePositive_PiecesHalfBlockedByOtherFriendlyPieces)
{
    piecesPlacement_.createPiece(Coordinates(3, 2), Player::UPPER);
    piecesPlacement_.createPiece(Coordinates(4, 3), Player::UPPER);
    piecesPlacement_.createPiece(Coordinates(3, 6), Player::UPPER);
    piecesPlacement_.createPiece(Coordinates(4, 5), Player::UPPER);

    piecesPlacement_.createPiece(Coordinates(7, 2), Player::LOWER);
    piecesPlacement_.createPiece(Coordinates(6, 3), Player::LOWER);
    piecesPlacement_.createPiece(Coordinates(7, 6), Player::LOWER);
    piecesPlacement_.createPiece(Coordinates(6, 5), Player::LOWER);

    placePiecesOnCheckerboard();

    for(auto& piece : piecesOnCheckerboard_)
    {
        EXPECT_TRUE(PieceMovementManager::checkIfPieceCanMove(*piece, piecesPlacement_));
    }
}

TEST_F(PieceMovementTest, CheckIfPieceCanMovePositive_PiecesHalfBlockedByOtherEnemyPieces)
{
    piecesPlacement_.createPiece(Coordinates(3, 2), Player::UPPER);
    piecesPlacement_.createPiece(Coordinates(4, 3), Player::LOWER);
    piecesPlacement_.createPiece(Coordinates(3, 6), Player::UPPER);
    piecesPlacement_.createPiece(Coordinates(4, 5), Player::LOWER);

    piecesPlacement_.createPiece(Coordinates(7, 2), Player::LOWER);
    piecesPlacement_.createPiece(Coordinates(6, 3), Player::UPPER);
    piecesPlacement_.createPiece(Coordinates(7, 6), Player::LOWER);
    piecesPlacement_.createPiece(Coordinates(6, 5), Player::UPPER);

    placePiecesOnCheckerboard();

    for(auto& piece : piecesOnCheckerboard_)
    {
        EXPECT_TRUE(PieceMovementManager::checkIfPieceCanMove(*piece, piecesPlacement_));
    }
}

TEST_F(PieceMovementTest, CheckIfPiecesCanMoveNegative_PiecesInTheirLastRows)
{
    piecesPlacement_.createPiece(Coordinates(8, 3), Player::UPPER);
    piecesPlacement_.createPiece(Coordinates(8, 5), Player::UPPER);

    piecesPlacement_.createPiece(Coordinates(1, 4), Player::LOWER);
    piecesPlacement_.createPiece(Coordinates(1, 6), Player::LOWER);

    placePiecesOnCheckerboard();

    for(auto& piece : piecesOnCheckerboard_)
    {
        EXPECT_FALSE(PieceMovementManager::checkIfPieceCanMove(*piece, piecesPlacement_));
    }
}

TEST_F(PieceMovementTest, CheckIfPieceCanMoveNegative_PiecesBlockedInFrontByEnemyPiecesAndWall)
{
    piecesPlacement_.createPiece(Coordinates(4, 1), Player::UPPER);
    piecesPlacement_.createPiece(Coordinates(4, 3), Player::UPPER);
    piecesPlacement_.createPiece(Coordinates(4, 5), Player::UPPER);
    piecesPlacement_.createPiece(Coordinates(4, 7), Player::UPPER);

    piecesPlacement_.createPiece(Coordinates(5, 2), Player::LOWER);
    piecesPlacement_.createPiece(Coordinates(5, 4), Player::LOWER);
    piecesPlacement_.createPiece(Coordinates(5, 6), Player::LOWER);
    piecesPlacement_.createPiece(Coordinates(5, 8), Player::LOWER);

    placePiecesOnCheckerboard();

    for(auto& piece : piecesOnCheckerboard_)
    {
        EXPECT_FALSE(PieceMovementManager::checkIfPieceCanMove(*piece, piecesPlacement_));
    }
}

TEST_F(PieceMovementTest, CheckIfPieceCanMoveNegative_PiecesBlockedInFrontByFriendPiecesAndTheirLastRowWall)
{
    piecesParameters_ = {{{1, 2}, Player::LOWER},
                         {{1, 4}, Player::LOWER},
                         {{1, 6}, Player::LOWER},
                         {{1, 8}, Player::LOWER},
                         {{2, 1}, Player::LOWER},
                         {{2, 3}, Player::LOWER},
                         {{2, 5}, Player::LOWER},
                         {{2, 7}, Player::LOWER},
                         {{7, 2}, Player::UPPER},
                         {{7, 4}, Player::UPPER},
                         {{7, 6}, Player::UPPER},
                         {{7, 8}, Player::UPPER},
                         {{8, 1}, Player::UPPER},
                         {{8, 3}, Player::UPPER},
                         {{8, 5}, Player::UPPER},
                         {{8, 7}, Player::UPPER}};

    placePiecesOnCheckerboard();

    for(auto& piece : piecesOnCheckerboard_)
    {
        EXPECT_FALSE(PieceMovementManager::checkIfPieceCanMove(*piece, piecesPlacement_));
    }
}

TEST_F(PieceMovementTest, CheckMovePossibility1)
{
    piecesParameters_ = {{{3, 4}, Player::UPPER},
                         {{6, 5}, Player::LOWER}};

    placePiecesOnCheckerboard();

    EXPECT_TRUE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(4, 3)));
    EXPECT_TRUE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(4, 5)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(2, 3)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(2, 5)));
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
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(1), piecesPlacement_, Coordinates(7, 4)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(1), piecesPlacement_, Coordinates(7, 6)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(1), piecesPlacement_, Coordinates(4, 3)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(1), piecesPlacement_, Coordinates(4, 7)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(1), piecesPlacement_, Coordinates(8, 3)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(1), piecesPlacement_, Coordinates(8, 7)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(1), piecesPlacement_, Coordinates(4, 5)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(1), piecesPlacement_, Coordinates(8, 5)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(1), piecesPlacement_, Coordinates(6, 3)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(1), piecesPlacement_, Coordinates(6, 7)));
}

TEST_F(PieceMovementTest, CheckMovePossibility2)
{
    piecesParameters_ = {{{4, 5}, Player::UPPER},
                         {{5, 4}, Player::LOWER}};

    placePiecesOnCheckerboard();

    EXPECT_TRUE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(5, 6)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(5, 4)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(3, 4)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(3, 6)));

    EXPECT_TRUE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(1), piecesPlacement_, Coordinates(4, 3)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(1), piecesPlacement_, Coordinates(4, 5)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(1), piecesPlacement_, Coordinates(6, 3)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(*piecesOnCheckerboard_.at(1), piecesPlacement_, Coordinates(6, 5)));
}

TEST_F(PieceMovementTest, WhichPiecesCanMove)
{
    piecesParameters_ = {{{7, 2}, Player::UPPER},
                         {{8, 3}, Player::UPPER},
                         {{1, 2}, Player::LOWER},
                         {{4, 5}, Player::LOWER},
                         {{3, 4}, Player::LOWER},
                         {{3, 6}, Player::LOWER}};

    placePiecesOnCheckerboard();

    std::vector<Piece*> piecesWhichCanMovePlayerUp = PieceMovementManager::whichPiecesCanMove(Player::UPPER, piecesPlacement_);
    std::vector<Piece*> piecesWhichCanMovePlayerDown = PieceMovementManager::whichPiecesCanMove(Player::LOWER, piecesPlacement_);

    EXPECT_EQ(piecesWhichCanMovePlayerUp.size(), 1);
    EXPECT_EQ(piecesWhichCanMovePlayerDown.size(), 2);
}
