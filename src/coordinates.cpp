#include "coordinates.h"

#include <stdexcept>

Coordinates::Coordinates(int row, int column)
{
    if(validateCoordinates(row, column))
    {
        row_ = row;
        column_ = column;
    }
    else
    {
        throw std::out_of_range("Error! Coordinates out of range");
    }
}

bool Coordinates::validateCoordinates(int row, int column)
{
    return (row >= 1 && row <= 8) && (column >= 1 && column <= 8);
}

bool operator<(const Coordinates& coordinates1, const Coordinates& coordinates2)
{
    if(coordinates1.getRow() < coordinates2.getRow())
    {
        return true;
    }
    else if(coordinates1.getRow() > coordinates2.getRow())
    {
        return false;
    }
    else
    {
        if(coordinates1.getColumn() < coordinates2.getColumn())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

bool operator==(const Coordinates& coordinates1, const Coordinates& coordinates2)
{
    return (coordinates1.getRow() == coordinates2.getRow()) && (coordinates1.getColumn() == coordinates2.getColumn());
}

std::ostream& operator<<(std::ostream& os, const Coordinates& coordinates)
{
    os << "(" << coordinates.getRow() << "," << coordinates.getColumn() << ")";

    return os;
}
