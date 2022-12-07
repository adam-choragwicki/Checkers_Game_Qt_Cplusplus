#include "common_test_fixture.h"
#include "piece_movement_manager.h"

class MovementTest : public CommonTestFixture
{};

TEST_F(MovementTest, CheckIfPieceCanMovePositive_PiecesInTheirFirstRows)
{
    piecesPlacement_.createPiece(Coordinates(1, 4), Player::up);
    piecesPlacement_.createPiece(Coordinates(1, 6), Player::up);

    piecesPlacement_.createPiece(Coordinates(8, 3), Player::down);
    piecesPlacement_.createPiece(Coordinates(8, 5), Player::down);

    placePiecesOnCheckerboard();

    for(auto& piece : piecesOnCheckerboard_)
    {
        EXPECT_TRUE(PieceMovementManager::checkIfPieceCanMove(piece, piecesPlacement_));
    }
}

TEST_F(MovementTest, CheckIfPieceCanMovePositive_PiecesInMiddleRows)
{
    piecesPlacement_.createPiece(Coordinates(3, 4), Player::up);
    piecesPlacement_.createPiece(Coordinates(3, 6), Player::up);

    piecesPlacement_.createPiece(Coordinates(6, 3), Player::down);
    piecesPlacement_.createPiece(Coordinates(6, 5), Player::down);

    placePiecesOnCheckerboard();

    for(auto& piece : piecesOnCheckerboard_)
    {
        EXPECT_TRUE(PieceMovementManager::checkIfPieceCanMove(piece, piecesPlacement_));
    }
}

TEST_F(MovementTest, CheckIfPieceCanMovePositive_PiecesInSideColumns)
{
    piecesPlacement_.createPiece(Coordinates(3, 8), Player::up);
    piecesPlacement_.createPiece(Coordinates(4, 1), Player::up);

    piecesPlacement_.createPiece(Coordinates(5, 8), Player::down);
    piecesPlacement_.createPiece(Coordinates(6, 1), Player::down);

    placePiecesOnCheckerboard();

    for(auto& piece : piecesOnCheckerboard_)
    {
        EXPECT_TRUE(PieceMovementManager::checkIfPieceCanMove(piece, piecesPlacement_));
    }
}

TEST_F(MovementTest, CheckIfPieceCanMovePositive_PiecesHalfBlockedByOtherFriendlyPieces)
{
    piecesPlacement_.createPiece(Coordinates(3, 2), Player::up);
    piecesPlacement_.createPiece(Coordinates(4, 3), Player::up);
    piecesPlacement_.createPiece(Coordinates(3, 6), Player::up);
    piecesPlacement_.createPiece(Coordinates(4, 5), Player::up);

    piecesPlacement_.createPiece(Coordinates(7, 2), Player::down);
    piecesPlacement_.createPiece(Coordinates(6, 3), Player::down);
    piecesPlacement_.createPiece(Coordinates(7, 6), Player::down);
    piecesPlacement_.createPiece(Coordinates(6, 5), Player::down);

    placePiecesOnCheckerboard();

    for(auto& piece : piecesOnCheckerboard_)
    {
        EXPECT_TRUE(PieceMovementManager::checkIfPieceCanMove(piece, piecesPlacement_));
    }
}

TEST_F(MovementTest, CheckIfPieceCanMovePositive_PiecesHalfBlockedByOtherEnemyPieces)
{
    piecesPlacement_.createPiece(Coordinates(3, 2), Player::up);
    piecesPlacement_.createPiece(Coordinates(4, 3), Player::down);
    piecesPlacement_.createPiece(Coordinates(3, 6), Player::up);
    piecesPlacement_.createPiece(Coordinates(4, 5), Player::down);

    piecesPlacement_.createPiece(Coordinates(7, 2), Player::down);
    piecesPlacement_.createPiece(Coordinates(6, 3), Player::up);
    piecesPlacement_.createPiece(Coordinates(7, 6), Player::down);
    piecesPlacement_.createPiece(Coordinates(6, 5), Player::up);

    placePiecesOnCheckerboard();

    for(auto& piece : piecesOnCheckerboard_)
    {
        EXPECT_TRUE(PieceMovementManager::checkIfPieceCanMove(piece, piecesPlacement_));
    }
}

TEST_F(MovementTest, CheckIfPiecesCanMoveNegative_PiecesInTheirLastRows)
{
    piecesPlacement_.createPiece(Coordinates(8, 3), Player::up);
    piecesPlacement_.createPiece(Coordinates(8, 5), Player::up);

    piecesPlacement_.createPiece(Coordinates(1, 4), Player::down);
    piecesPlacement_.createPiece(Coordinates(1, 6), Player::down);

    placePiecesOnCheckerboard();

    for(auto& piece : piecesOnCheckerboard_)
    {
        EXPECT_FALSE(PieceMovementManager::checkIfPieceCanMove(piece, piecesPlacement_));
    }
}

TEST_F(MovementTest, CheckIfPieceCanMoveNegative_PiecesBlockedInFrontByEnemyPiecesAndWall)
{
    piecesPlacement_.createPiece(Coordinates(4, 1), Player::up);
    piecesPlacement_.createPiece(Coordinates(4, 3), Player::up);
    piecesPlacement_.createPiece(Coordinates(4, 5), Player::up);
    piecesPlacement_.createPiece(Coordinates(4, 7), Player::up);

    piecesPlacement_.createPiece(Coordinates(5, 2), Player::down);
    piecesPlacement_.createPiece(Coordinates(5, 4), Player::down);
    piecesPlacement_.createPiece(Coordinates(5, 6), Player::down);
    piecesPlacement_.createPiece(Coordinates(5, 8), Player::down);

    placePiecesOnCheckerboard();

    for(auto& piece : piecesOnCheckerboard_)
    {
        EXPECT_FALSE(PieceMovementManager::checkIfPieceCanMove(piece, piecesPlacement_));
    }
}

TEST_F(MovementTest, CheckIfPieceCanMoveNegative_PiecesBlockedInFrontByFriendPiecesAndTheirLastRowWall)
{
    piecesParameters_ = {{{1, 2}, Player::down},
                         {{1, 4}, Player::down},
                         {{1, 6}, Player::down},
                         {{1, 8}, Player::down},
                         {{2, 1}, Player::down},
                         {{2, 3}, Player::down},
                         {{2, 5}, Player::down},
                         {{2, 7}, Player::down},
                         {{7, 2}, Player::up},
                         {{7, 4}, Player::up},
                         {{7, 6}, Player::up},
                         {{7, 8}, Player::up},
                         {{8, 1}, Player::up},
                         {{8, 3}, Player::up},
                         {{8, 5}, Player::up},
                         {{8, 7}, Player::up}};

    placePiecesOnCheckerboard();

    for(auto& piece : piecesOnCheckerboard_)
    {
        EXPECT_FALSE(PieceMovementManager::checkIfPieceCanMove(piece, piecesPlacement_));
    }
}

TEST_F(MovementTest, CheckMovePossibility1)
{
    piecesParameters_ = {{{3, 4}, Player::up},
                         {{6, 5}, Player::down}};

    placePiecesOnCheckerboard();

    EXPECT_TRUE(PieceMovementManager::checkMovePossibility(piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(4, 3)));
    EXPECT_TRUE(PieceMovementManager::checkMovePossibility(piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(4, 5)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(2, 3)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(2, 5)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(1, 2)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(1, 6)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(5, 2)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(5, 6)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(3, 2)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(3, 6)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(1, 4)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(5, 4)));

    EXPECT_TRUE(PieceMovementManager::checkMovePossibility(piecesOnCheckerboard_.at(1), piecesPlacement_, Coordinates(5, 4)));
    EXPECT_TRUE(PieceMovementManager::checkMovePossibility(piecesOnCheckerboard_.at(1), piecesPlacement_, Coordinates(5, 6)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(piecesOnCheckerboard_.at(1), piecesPlacement_, Coordinates(7, 4)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(piecesOnCheckerboard_.at(1), piecesPlacement_, Coordinates(7, 6)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(piecesOnCheckerboard_.at(1), piecesPlacement_, Coordinates(4, 3)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(piecesOnCheckerboard_.at(1), piecesPlacement_, Coordinates(4, 7)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(piecesOnCheckerboard_.at(1), piecesPlacement_, Coordinates(8, 3)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(piecesOnCheckerboard_.at(1), piecesPlacement_, Coordinates(8, 7)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(piecesOnCheckerboard_.at(1), piecesPlacement_, Coordinates(4, 5)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(piecesOnCheckerboard_.at(1), piecesPlacement_, Coordinates(8, 5)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(piecesOnCheckerboard_.at(1), piecesPlacement_, Coordinates(6, 3)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(piecesOnCheckerboard_.at(1), piecesPlacement_, Coordinates(6, 7)));
}

TEST_F(MovementTest, CheckMovePossibility2)
{
    piecesParameters_ = {{{4, 5}, Player::up},
                         {{5, 4}, Player::down}};

    placePiecesOnCheckerboard();

    EXPECT_TRUE(PieceMovementManager::checkMovePossibility(piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(5, 6)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(5, 4)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(3, 4)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(piecesOnCheckerboard_.at(0), piecesPlacement_, Coordinates(3, 6)));

    EXPECT_TRUE(PieceMovementManager::checkMovePossibility(piecesOnCheckerboard_.at(1), piecesPlacement_, Coordinates(4, 3)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(piecesOnCheckerboard_.at(1), piecesPlacement_, Coordinates(4, 5)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(piecesOnCheckerboard_.at(1), piecesPlacement_, Coordinates(6, 3)));
    EXPECT_FALSE(PieceMovementManager::checkMovePossibility(piecesOnCheckerboard_.at(1), piecesPlacement_, Coordinates(6, 5)));
}

TEST_F(MovementTest, WhichPiecesCanMove)
{
    piecesParameters_ = {{{7, 2}, Player::up},
                         {{8, 3}, Player::up},
                         {{1, 2}, Player::down},
                         {{4, 5}, Player::down},
                         {{3, 4}, Player::down},
                         {{3, 6}, Player::down}};

    placePiecesOnCheckerboard();

    QVector<Piece*> piecesWhichCanMovePlayerUp = PieceMovementManager::whichPiecesCanMove(Player::up, piecesPlacement_);
    QVector<Piece*> piecesWhichCanMovePlayerDown = PieceMovementManager::whichPiecesCanMove(Player::down, piecesPlacement_);

    EXPECT_EQ(piecesWhichCanMovePlayerUp.size(), 1);
    EXPECT_EQ(piecesWhichCanMovePlayerDown.size(), 2);
}
