#include "common_test_fixture.h"
#include "coordinates_database.h"

class CoordinatesGenerationTest : public CommonTestFixture
{};

TEST_F(CoordinatesGenerationTest, GeneratePlayableTilesCoordinates)
{
    std::set<Coordinates> playableTilesCoordinates = CoordinatesDatabase::getInstance().getPlayableCoordinates();

    EXPECT_EQ(playableTilesCoordinates.size(), 32);
}

TEST_F(CoordinatesGenerationTest, GenerateStartingPiecesCoordinates)
{
    std::set<Coordinates> playerUpStartingPiecesCoordinates = CoordinatesDatabase::getInstance().getStartingPieceCoordinatesPlayerUpper();
    std::set<Coordinates> playerDownStartingPiecesCoordinates = CoordinatesDatabase::getInstance().getStartingPieceCoordinatesPlayerLower();

    EXPECT_EQ(playerUpStartingPiecesCoordinates.size(), 12);
    EXPECT_EQ(playerDownStartingPiecesCoordinates.size(), 12);
}
