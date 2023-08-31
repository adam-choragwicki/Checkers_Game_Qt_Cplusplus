#include "common_test_fixture.h"
#include "piece_promotion_manager.h"

class PiecePromotionTest : public CommonTestFixture
{};

TEST_F(PiecePromotionTest, CheckPromotionEligibilityPositive)
{
    const Piece playerUpPiece1(Coordinates(8, 3), Player::UPPER);
    const Piece playerUpPiece2(Coordinates(8, 7), Player::UPPER);

    const Piece playerDownPiece1(Coordinates(1, 4), Player::LOWER);
    const Piece playerDownPiece2(Coordinates(1, 8), Player::LOWER);

    EXPECT_TRUE(PiecePromotionManager::checkPromotionEligibility(playerUpPiece1));
    EXPECT_TRUE(PiecePromotionManager::checkPromotionEligibility(playerUpPiece2));

    EXPECT_TRUE(PiecePromotionManager::checkPromotionEligibility(playerDownPiece1));
    EXPECT_TRUE(PiecePromotionManager::checkPromotionEligibility(playerDownPiece2));
}

TEST_F(PiecePromotionTest, CheckPromotionEligibilityNegative)
{
    const Piece playerUpPiece1(Coordinates(1, 2), Player::UPPER);
    const Piece playerUpPiece2(Coordinates(1, 6), Player::UPPER);
    const Piece playerUpPiece3(Coordinates(4, 3), Player::UPPER);
    const Piece playerUpPiece4(Coordinates(5, 8), Player::UPPER);

    const Piece playerDownPiece1(Coordinates(8, 3), Player::LOWER);
    const Piece playerDownPiece2(Coordinates(8, 7), Player::LOWER);
    const Piece playerDownPiece3(Coordinates(4, 3), Player::LOWER);
    const Piece playerDownPiece4(Coordinates(5, 6), Player::LOWER);

    EXPECT_FALSE(PiecePromotionManager::checkPromotionEligibility(playerUpPiece1));
    EXPECT_FALSE(PiecePromotionManager::checkPromotionEligibility(playerUpPiece2));
    EXPECT_FALSE(PiecePromotionManager::checkPromotionEligibility(playerUpPiece3));
    EXPECT_FALSE(PiecePromotionManager::checkPromotionEligibility(playerUpPiece4));

    EXPECT_FALSE(PiecePromotionManager::checkPromotionEligibility(playerDownPiece1));
    EXPECT_FALSE(PiecePromotionManager::checkPromotionEligibility(playerDownPiece2));
    EXPECT_FALSE(PiecePromotionManager::checkPromotionEligibility(playerDownPiece3));
    EXPECT_FALSE(PiecePromotionManager::checkPromotionEligibility(playerDownPiece4));
}

TEST_F(PiecePromotionTest, DoublePromotionNotAllowed)
{
    Piece playerUpPiece1(Coordinates(8, 3), Player::UPPER, true);
    Piece playerDownPiece1(Coordinates(1, 4), Player::LOWER, true);

    EXPECT_FALSE(PiecePromotionManager::checkPromotionEligibility(playerUpPiece1));

    EXPECT_FALSE(PiecePromotionManager::checkPromotionEligibility(playerDownPiece1));
}
