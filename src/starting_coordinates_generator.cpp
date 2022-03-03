#include "starting_coordinates_generator.h"

std::vector<Coordinates> StartingCoordinatesGenerator::generatePlayableTilesCoordinates()
{
    static std::vector<Coordinates> playableTilesCoordinates;

    /* Generate playable tiles coordinates only once */
    if(playableTilesCoordinates.empty())
    {
        for(int row = 1; row <= 8; row++)
        {
            for(int column = 1; column <= 8; column++)
            {
                if(row % 2 == 0)
                {
                    if(column % 2 != 0)
                    {
                        playableTilesCoordinates.emplace_back(row, column);
                    }
                }
                else
                {
                    if(column % 2 == 0)
                    {
                        playableTilesCoordinates.emplace_back(row, column);
                    }
                }
            }
        }
    }

    return playableTilesCoordinates;
}

std::vector<Coordinates> StartingCoordinatesGenerator::generateStartingPiecesCoordinates(Player player)
{
    std::vector<Coordinates> startingPiecesCoordinates;

    if(player == Player::down)
    {
        for(int row = 6; row <= 8; row++)
        {
            for(int column = 1; column <= 8; column++)
            {
                if(row % 2 != 0)
                {
                    if(column % 2 == 0)
                    {
                        startingPiecesCoordinates.emplace_back(row, column);
                    }
                }
                else
                {
                    if(column % 2 != 0)
                    {
                        startingPiecesCoordinates.emplace_back(row, column);
                    }
                }
            }
        }
    }
    else if(player == Player::up)
        {
            for(int row = 1; row <= 3; row++)
            {
                for(int column = 1; column <= 8; column++)
                {
                    if(row % 2 != 0)
                    {
                        if(column % 2 == 0)
                        {
                            startingPiecesCoordinates.emplace_back(row, column);
                        }
                    }
                    else
                    {
                        if(column % 2 != 0)
                        {
                            startingPiecesCoordinates.emplace_back(row, column);
                        }
                    }
                }
            }
        }

    return startingPiecesCoordinates;
}
