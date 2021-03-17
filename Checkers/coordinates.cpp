#include "coordinates.h"
#include <stdexcept>

Coordinates::Coordinates(int row, int column)
{
    if((row >= 1 && row <= 8) && (column >= 1 && column <= 8))
    {
        m_Row = row;
        m_Column = column;
    }
    else
    {
        throw std::out_of_range("Error! Coordinates out of range");
    }
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
