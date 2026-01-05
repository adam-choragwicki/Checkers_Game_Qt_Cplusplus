#include "common_test_fixture.h"
#include "coordinates_database.h"

class CoordinatesGenerationTest : public CommonTestFixture
{};

TEST_F(CoordinatesGenerationTest, GeneratePlayableTilesCoordinates)
{
    const std::set<Coordinates> playableTilesCoordinates = CoordinatesDatabase::getInstance().getPlayableCoordinates();

    EXPECT_EQ(playableTilesCoordinates.size(), 32);
}

TEST_F(CoordinatesGenerationTest, GenerateStartingPiecesCoordinates)
{
    const std::set<Coordinates> northPlayerStartingPiecesCoordinates = CoordinatesDatabase::getInstance().getStartingPieceCoordinatesOfNorthPlayer();
    const std::set<Coordinates> southPlayerStartingPiecesCoordinates = CoordinatesDatabase::getInstance().getStartingPieceCoordinatesOfSouthPlayer();

    EXPECT_EQ(northPlayerStartingPiecesCoordinates.size(), 12);
    EXPECT_EQ(southPlayerStartingPiecesCoordinates.size(), 12);
}
