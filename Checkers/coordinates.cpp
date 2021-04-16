#include "coordinates.h"
#include <stdexcept>

Coordinates::Coordinates(int row, int column)
{
    if(ValidateCoordinates(row, column))
    {
        m_Row = row;
        m_Column = column;
    }
    else
    {
        throw std::out_of_range("Error! Coordinates out of range");
    }
}

bool Coordinates::ValidateCoordinates(int row, int column)
{
    return (row >= 1 && row <= 8) && (column >= 1 && column <= 8);
}

void Coordinates::Modify(int newRow, int newColumn)
{
    m_Row = newRow;
    m_Column = newColumn;
}

bool operator<(const Coordinates& coordinates1, const Coordinates& coordinates2)
{
    if(coordinates1.Row() < coordinates2.Row())
    {
        return true;
    }
    else if(coordinates1.Row() > coordinates2.Row())
    {
        return false;
    }
    else
    {
        if(coordinates1.Column() < coordinates2.Column())
        {
            return true;
        }
        else if(coordinates1.Column() > coordinates2.Column())
        {
            return false;
        }
        else
        {
            return false;
        }
    }
}

bool operator==(const Coordinates& coordinates1, const Coordinates& coordinates2)
{
    return (coordinates1.Row() == coordinates2.Row()) && (coordinates1.Column() == coordinates2.Column());
}
