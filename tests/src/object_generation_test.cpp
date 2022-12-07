#include "common_test_fixture.h"
#include "starting_coordinates_generator.h"

class ObjectGenerationTest : public CommonTestFixture
{};

TEST_F(ObjectGenerationTest, GeneratePlayableTilesCoordinates)
{
    QVector<Coordinates> playableTilesCoordinates = StartingCoordinatesGenerator::generatePlayableTilesCoordinates();

    EXPECT_EQ(playableTilesCoordinates.size(), 32);
}

TEST_F(ObjectGenerationTest, GenerateStartingPiecesCoordinates)
{
    QVector<Coordinates> playerUpStartingPiecesCoordinates = StartingCoordinatesGenerator::generateStartingPiecesCoordinates(Player::up);
    QVector<Coordinates> playerDownStartingPiecesCoordinates = StartingCoordinatesGenerator::generateStartingPiecesCoordinates(Player::down);

    EXPECT_EQ(playerUpStartingPiecesCoordinates.size(), 12);
    EXPECT_EQ(playerDownStartingPiecesCoordinates.size(), 12);
}
