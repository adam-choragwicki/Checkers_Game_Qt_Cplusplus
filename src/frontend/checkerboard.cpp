#include "checkerboard.h"
#include "../coordinates_database.h"

Checkerboard::Checkerboard()
{
    createTiles();
}

void Checkerboard::createTiles()
{
    for(const Coordinates& coordinates : CoordinatesDatabase::getInstance().getPlayableCoordinates())
    {
        playableTiles_.push_back(std::make_unique<PlayableTile>(coordinates));
    }

    for(const Coordinates& coordinates : CoordinatesDatabase::getInstance().getNonPlayableCoordinates())
    {
        nonPlayableTiles_.push_back(std::make_unique<NonPlayableTile>(coordinates));
    }
}

std::vector<PlayableTile*> Checkerboard::getPlayableTiles() const
{
    std::vector<PlayableTile*> playableTiles;

    for(const auto& playableTile : playableTiles_)
    {
        playableTiles.push_back(playableTile.get());
    }

    return playableTiles;
}
