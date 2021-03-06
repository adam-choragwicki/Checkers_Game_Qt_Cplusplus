#include "logic.h"

std::vector<std::pair<int, int>> Logic::GenerateAllValidGameTilesCoordinates()
{
    std::vector<std::pair<int, int>> validGameTilesCoordinates;

    bool chooseEvenColumns = true;

    for(int row = 1; row <= 8; row++)
    {
        for(int column = 1; column <= 8; column++)
        {
            if(chooseEvenColumns)
            {
                if(column % 2 == 0)
                {
                    validGameTilesCoordinates.push_back(std::pair<int, int>(row, column));
                }
            }
            else
            {
                if(column % 2 != 0)
                {
                    validGameTilesCoordinates.push_back(std::pair<int, int>(row, column));
                }
            }
        }
        chooseEvenColumns ^= true;
    }

    return validGameTilesCoordinates;
}

std::vector<std::pair<int, int>> Logic::GenerateStartingPiecesCoordinates(PLAYER player)
{
    std::vector<std::pair<int, int>> startingPiecesCoordinates;

    if(player == PLAYER_LOWER)
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
                        startingPiecesCoordinates.push_back(std::pair<int, int>(row, column));
                    }
                }
                else
                {
                    if(column % 2 != 0)
                    {
                        startingPiecesCoordinates.push_back(std::pair<int, int>(row, column));
                    }
                }
            }
            chooseEvenColumns ^= true;
        }
    }
    else if(player == PLAYER_UPPER)
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
                        startingPiecesCoordinates.push_back(std::pair<int, int>(row, column));
                    }
                }
                else
                {
                    if(column % 2 != 0)
                    {
                        startingPiecesCoordinates.push_back(std::pair<int, int>(row, column));
                    }
                }
            }
            chooseEvenColumns ^= true;
        }
    }

    return startingPiecesCoordinates;
}
