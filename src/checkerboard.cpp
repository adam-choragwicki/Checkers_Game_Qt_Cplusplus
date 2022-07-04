#include "checkerboard.h"
#include "starting_coordinates_generator.h"

Checkerboard::Checkerboard()
{
    createTiles();
}

Checkerboard::~Checkerboard()
{
    for(Tile* tile : tiles_)
    {
        delete tile;
    }
}

void Checkerboard::createTiles()
{
    QVector<Coordinates> playableTilesCoordinates = StartingCoordinatesGenerator::generatePlayableTilesCoordinates();

    for(int row = 1; row <= 8; row++)
    {
        for(int column = 1; column <= 8; column++)
        {
            const Coordinates tileCoordinates(row, column);
            bool playable = playableTilesCoordinates.contains(tileCoordinates);

            Tile* tile = new Tile(tileCoordinates, playable);
            tiles_.push_back(tile);
        }
    }
}

QVector<Tile*> Checkerboard::getPlayableTiles() const
{
    QVector<Tile*> playableTiles;

    for(Tile* tile : tiles_)
    {
        if(tile->isPlayable())
        {
            playableTiles.push_back(tile);
        }
    }

    return playableTiles;
}
