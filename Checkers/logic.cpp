#include "logic.h"

std::vector<Coordinates> Logic::GenerateAllValidGameTilesCoordinates()
{
    std::vector<Coordinates> validGameTilesCoordinates;

    bool chooseEvenColumns = true;

    for(int row = 1; row <= 8; row++)
    {
        for(int column = 1; column <= 8; column++)
        {
            if(chooseEvenColumns)
            {
                if(column % 2 == 0)
                {
                    validGameTilesCoordinates.push_back(Coordinates(row, column));
                }
            }
            else
            {
                if(column % 2 != 0)
                {
                    validGameTilesCoordinates.push_back(Coordinates(row, column));
                }
            }
        }
        chooseEvenColumns ^= true;
    }

    return validGameTilesCoordinates;
}

std::vector<Coordinates> Logic::GenerateStartingPiecesCoordinates(Player player)
{
    std::vector<Coordinates> startingPiecesCoordinates;

    if(player == Player::Down)
    {
        bool chooseEvenColumns = false;

        for(int row = 6; row <= 8; row++)
        {
            for(int column = 1; column <= 8; column++)
            {
                if(chooseEvenColumns)
                {
                    if(column % 2 == 0)
                    {
                        startingPiecesCoordinates.push_back(Coordinates(row, column));
                    }
                }
                else
                {
                    if(column % 2 != 0)
                    {
                        startingPiecesCoordinates.push_back(Coordinates(row, column));
                    }
                }
            }
            chooseEvenColumns ^= true;
        }
    }
    else if(player == Player::Up)
    {
        bool chooseEvenColumns = true;

        for(int row = 1; row <= 3; row++)
        {
            for(int column = 1; column <= 8; column++)
            {
                if(chooseEvenColumns)
                {
                    if(column % 2 == 0)
                    {
                        startingPiecesCoordinates.push_back(Coordinates(row, column));
                    }
                }
                else
                {
                    if(column % 2 != 0)
                    {
                        startingPiecesCoordinates.push_back(Coordinates(row, column));
                    }
                }
            }
            chooseEvenColumns ^= true;
        }
    }

    return startingPiecesCoordinates;
}
