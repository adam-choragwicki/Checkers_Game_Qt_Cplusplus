#pragma once

class Coordinates
{
public:
    Coordinates(int row, int column);
    Coordinates& operator=(const Coordinates&) = delete;

    void Modify(int newRow, int newColumn);
    int Row() const {return m_Row;}
    int Column() const {return m_Column;}

private:
    int m_Row;
    int m_Column;
};

bool operator<(const Coordinates& coordinates1, const Coordinates& coordinates2);
