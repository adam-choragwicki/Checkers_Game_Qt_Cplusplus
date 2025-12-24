#pragma once

#include <iostream>
#include <QString>

class Coordinates
{
    friend std::ostream& operator<<(std::ostream& os, const Coordinates& coordinates);

public:
    Coordinates(int row, int column);

    static bool validateCoordinates(int row, int column);
    static bool validateCoordinates(const Coordinates& coordinates);

    Coordinates operator+(const std::pair<int, int>& coefficientsPair) const;
    std::pair<int, int> operator-(const Coordinates& coordinates) const;

    [[nodiscard]] int getRow() const {return row_;}
    [[nodiscard]] int getColumn() const {return column_;}

    operator QString() const;

private:
    int row_;
    int column_;
};

bool operator<(const Coordinates& coordinates1, const Coordinates& coordinates2);
bool operator==(const Coordinates& coordinates1, const Coordinates& coordinates2);
