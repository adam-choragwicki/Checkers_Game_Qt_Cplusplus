#include "coordinates.h"

#include <stdexcept>

Coordinates::Coordinates(int row, int column) : row_(row), column_(column)
{}

bool Coordinates::validateCoordinates(int row, int column)
{
    return (row >= 1 && row <= 8) && (column >= 1 && column <= 8);
}

bool Coordinates::validateCoordinates(const Coordinates& coordinates)
{
    return validateCoordinates(coordinates.row_, coordinates.column_);
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
        return coordinates1.getColumn() < coordinates2.getColumn();
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

Coordinates Coordinates::operator+(const std::pair<int, int>& coefficientsPair) const
{
    return {row_ + coefficientsPair.first, column_ + coefficientsPair.second};
}

std::pair<int, int> Coordinates::operator-(const Coordinates& coordinates) const
{
    return {row_ - coordinates.row_, column_ - coordinates.column_};
}
