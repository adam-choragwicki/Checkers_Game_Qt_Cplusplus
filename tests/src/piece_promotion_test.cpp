#include "common_test_fixture.h"
#include "piece_promotion_manager.h"

class PiecePromotionTest : public CommonTestFixture
{};

TEST_F(PiecePromotionTest, CheckPromotionEligibilityPositive)
{
    const std::initializer_list<Piece> promotablePieces = {
        {{8, 3}, Player::NORTH},
        {{8, 7}, Player::NORTH},
        {{1, 4}, Player::SOUTH},
        {{1, 8}, Player::SOUTH}
    };

    for (const auto& piece: promotablePieces)
    {
        EXPECT_TRUE(PiecePromotionManager::checkPromotionEligibility(piece));
    }
}

TEST_F(PiecePromotionTest, CheckPromotionEligibilityNegative)
{
    const std::initializer_list<Piece> nonPromotablePieces = {
        {{1, 2}, Player::NORTH},
        {{1, 6}, Player::NORTH},
        {{4, 3}, Player::NORTH},
        {{5, 8}, Player::NORTH},
        {{8, 3}, Player::SOUTH},
        {{8, 7}, Player::SOUTH},
        {{4, 3}, Player::SOUTH},
        {{5, 6}, Player::SOUTH}
    };

    for (const auto& piece: nonPromotablePieces)
    {
        EXPECT_FALSE(PiecePromotionManager::checkPromotionEligibility(piece));
    }
}

TEST_F(PiecePromotionTest, DoublePromotionNotAllowed)
{
    const std::initializer_list<Piece> alreadyPromotedPieces = {
        {{8, 3}, Player::NORTH, true},
        {{1, 4}, Player::SOUTH, true}
    };

    for (const auto& piece: alreadyPromotedPieces)
    {
        EXPECT_FALSE(PiecePromotionManager::checkPromotionEligibility(piece));
    }
}
