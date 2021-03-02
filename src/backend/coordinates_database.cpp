#include "coordinates_database.h"

std::set<Coordinates> CoordinatesDatabase::CoordinatesGenerator::generatePlayableTilesCoordinates()
{
    std::set<Coordinates> playableTilesCoordinates;

    for(int row = 1; row <= 8; row++)
    {
        for(int column = 1; column <= 8; column++)
        {
            if(row % 2 == 0)
            {
                if(column % 2 != 0)
                {
                    playableTilesCoordinates.emplace(row, column);
                }
            }
            else
            {
                if(column % 2 == 0)
                {
                    playableTilesCoordinates.emplace(row, column);
                }
            }
        }
    }

    return playableTilesCoordinates;
}

std::set<Coordinates> CoordinatesDatabase::CoordinatesGenerator::generateNonPlayableTilesCoordinates()
{
    std::set<Coordinates> nonPlayableTilesCoordinates;

    for(int row = 1; row <= 8; row++)
    {
        for(int column = 1; column <= 8; column++)
        {
            if(row % 2 == 0)
            {
                if(column % 2 == 0)
                {
                    nonPlayableTilesCoordinates.emplace(row, column);
                }
            }
            else
            {
                if(column % 2 != 0)
                {
                    nonPlayableTilesCoordinates.emplace(row, column);
                }
            }
        }
    }

    return nonPlayableTilesCoordinates;
}

std::set<Coordinates> CoordinatesDatabase::CoordinatesGenerator::generateStartingPiecesCoordinates(Player player)
{
    std::set<Coordinates> startingPiecesCoordinates;

    if(player == Player::LOWER)
    {
        for(int row = 6; row <= 8; row++)
        {
            for(int column = 1; column <= 8; column++)
            {
                if(row % 2 != 0)
                {
                    if(column % 2 == 0)
                    {
                        startingPiecesCoordinates.emplace(row, column);
                    }
                }
                else
                {
                    if(column % 2 != 0)
                    {
                        startingPiecesCoordinates.emplace(row, column);
                    }
                }
            }
        }
    }
    else if(player == Player::UPPER)
    {
        for(int row = 1; row <= 3; row++)
        {
            for(int column = 1; column <= 8; column++)
            {
                if(row % 2 != 0)
                {
                    if(column % 2 == 0)
                    {
                        startingPiecesCoordinates.emplace(row, column);
                    }
                }
                else
                {
                    if(column % 2 != 0)
                    {
                        startingPiecesCoordinates.emplace(row, column);
                    }
                }
            }
        }
    }

    return startingPiecesCoordinates;
}
