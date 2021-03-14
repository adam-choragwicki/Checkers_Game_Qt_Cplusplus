#pragma once

#include <QGraphicsRectItem>
#include <map>
#include "piece.h"

class Board : public QGraphicsRectItem
{
public:
    Board(QGraphicsScene& scene);
    static void ProcessTileClicked(const int row, const int column, bool tileIsPlayable);

private:
    const int BOARD_POSITION_X = 0;
    const int BOARD_POSITION_Y = 0;
    const int BOARD_SIZE = 640;
    const int BOARD_OUTLINE_WIDTH = 10;
    const QColor BOARD_OUTLINE_COLOR{150, 100, 40};

    static std::map<std::pair<int, int>, Piece*> m_PiecesPlacement;

    void CreateTiles(QGraphicsScene& scene);
    void CreatePieces(QGraphicsScene& scene);
};
