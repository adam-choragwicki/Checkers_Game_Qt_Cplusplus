#include "common_test_fixture.h"
#include "piece_promotion_manager.h"

class PromotionTest : public CommonTestFixture
{};

TEST_F(PromotionTest, CheckPromotionEligibilityPositive)
{
    const Piece playerUpPiece1(Coordinates(8, 3), Player::up);
    const Piece playerUpPiece2(Coordinates(8, 7), Player::up);

    const Piece playerDownPiece1(Coordinates(1, 4), Player::down);
    const Piece playerDownPiece2(Coordinates(1, 8), Player::down);

    EXPECT_TRUE(PiecePromotionManager::checkPromotionEligibility(&playerUpPiece1));
    EXPECT_TRUE(PiecePromotionManager::checkPromotionEligibility(&playerUpPiece2));

    EXPECT_TRUE(PiecePromotionManager::checkPromotionEligibility(&playerDownPiece1));
    EXPECT_TRUE(PiecePromotionManager::checkPromotionEligibility(&playerDownPiece2));
}

TEST_F(PromotionTest, CheckPromotionEligibilityNegative)
{
    const Piece playerUpPiece1(Coordinates(1, 2), Player::up);
    const Piece playerUpPiece2(Coordinates(1, 6), Player::up);
    const Piece playerUpPiece3(Coordinates(4, 3), Player::up);
    const Piece playerUpPiece4(Coordinates(5, 8), Player::up);

    const Piece playerDownPiece1(Coordinates(8, 3), Player::down);
    const Piece playerDownPiece2(Coordinates(8, 7), Player::down);
    const Piece playerDownPiece3(Coordinates(4, 3), Player::down);
    const Piece playerDownPiece4(Coordinates(5, 6), Player::down);

    EXPECT_FALSE(PiecePromotionManager::checkPromotionEligibility(&playerUpPiece1));
    EXPECT_FALSE(PiecePromotionManager::checkPromotionEligibility(&playerUpPiece2));
    EXPECT_FALSE(PiecePromotionManager::checkPromotionEligibility(&playerUpPiece3));
    EXPECT_FALSE(PiecePromotionManager::checkPromotionEligibility(&playerUpPiece4));

    EXPECT_FALSE(PiecePromotionManager::checkPromotionEligibility(&playerDownPiece1));
    EXPECT_FALSE(PiecePromotionManager::checkPromotionEligibility(&playerDownPiece2));
    EXPECT_FALSE(PiecePromotionManager::checkPromotionEligibility(&playerDownPiece3));
    EXPECT_FALSE(PiecePromotionManager::checkPromotionEligibility(&playerDownPiece4));
}

TEST_F(PromotionTest, DoublePromotionNotAllowed)
{
    Piece playerUpPiece1(Coordinates(8, 3), Player::up, true);
    Piece playerDownPiece1(Coordinates(1, 4), Player::down, true);

    EXPECT_FALSE(PiecePromotionManager::checkPromotionEligibility(&playerUpPiece1));

    EXPECT_FALSE(PiecePromotionManager::checkPromotionEligibility(&playerDownPiece1));
}
