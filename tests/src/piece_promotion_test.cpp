#include "common_test_fixture.h"
#include "piece_promotion_manager.h"

class PiecePromotionTest : public CommonTestFixture
{};

TEST_F(PiecePromotionTest, CheckPromotionEligibilityPositive)
{
    const std::initializer_list<Piece> promotablePieces = {
        {{8, 3}, NORTH_PLAYER},
        {{8, 7}, NORTH_PLAYER},
        {{1, 4}, SOUTH_PLAYER},
        {{1, 8}, SOUTH_PLAYER}
    };

    for (const auto& piece: promotablePieces)
    {
        EXPECT_TRUE(PiecePromotionManager::checkPromotionEligibility(piece));
    }
}

TEST_F(PiecePromotionTest, CheckPromotionEligibilityNegative)
{
    const std::initializer_list<Piece> nonPromotablePieces = {
        {{1, 2}, NORTH_PLAYER},
        {{1, 6}, NORTH_PLAYER},
        {{4, 3}, NORTH_PLAYER},
        {{5, 8}, NORTH_PLAYER},
        {{8, 3}, SOUTH_PLAYER},
        {{8, 7}, SOUTH_PLAYER},
        {{4, 3}, SOUTH_PLAYER},
        {{5, 6}, SOUTH_PLAYER}
    };

    for (const auto& piece: nonPromotablePieces)
    {
        EXPECT_FALSE(PiecePromotionManager::checkPromotionEligibility(piece));
    }
}

TEST_F(PiecePromotionTest, DoublePromotionNotAllowed)
{
    const std::initializer_list<Piece> alreadyPromotedPieces = {
        {{8, 3}, NORTH_PLAYER, true},
        {{1, 4}, SOUTH_PLAYER, true}
    };

    for (const auto& piece: alreadyPromotedPieces)
    {
        EXPECT_FALSE(PiecePromotionManager::checkPromotionEligibility(piece));
    }
}
