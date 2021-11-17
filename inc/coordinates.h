#pragma once

#include <iostream>

class Coordinates
{
    friend std::ostream& operator<<(std::ostream& os, const Coordinates& coordinates);

public:
    Coordinates(int row, int column);

    static bool validateCoordinates(int row, int column);

    int getRow() const {return row_;}
    int getColumn() const {return column_;}

    void modify(int newRow, int newColumn);

private:
    int row_;
    int column_;
};

bool operator<(const Coordinates& coordinates1, const Coordinates& coordinates2);
bool operator==(const Coordinates& coordinates1, const Coordinates& coordinates2);
