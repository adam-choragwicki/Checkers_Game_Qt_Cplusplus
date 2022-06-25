#include "tile_manager.h"
#include "starting_coordinates_generator.h"

bool TileManager::isTileEmpty(const Coordinates& coordinates, const PiecesPlacement& piecesPlacement)
{
    /* Generate playable tiles coordinates only once */
    static QVector<Coordinates> playableTileCoordinates;

    if(playableTileCoordinates.empty())
    {
        playableTileCoordinates = StartingCoordinatesGenerator::generatePlayableTilesCoordinates();
    }

    if(!playableTileCoordinates.contains(coordinates))
    {
        throw std::runtime_error("Trying to check if piece is on unplayable tile");
    }

    return !piecesPlacement.isPieceAtCoordinates(coordinates);
}
