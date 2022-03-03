#include "tile_manager.h"
#include "starting_coordinates_generator.h"

bool TileManager::isTileEmpty(const Coordinates& coordinates, const CoordinatesToPiecesMapping& coordinatesToPiecesMapping)
{
    /* Generate playable tiles coordinates only once */
    static std::vector<Coordinates> playableTileCoordinates;

    if(playableTileCoordinates.empty())
    {
        playableTileCoordinates = StartingCoordinatesGenerator::generatePlayableTilesCoordinates();
    }

    if(std::find(playableTileCoordinates.begin(), playableTileCoordinates.end(), coordinates) == playableTileCoordinates.end())
    {
        throw std::runtime_error("Trying to check if piece is on unplayable tile");
    }

    return coordinatesToPiecesMapping.at(coordinates) == nullptr;
}
