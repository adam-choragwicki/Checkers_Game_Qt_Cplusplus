#pragma once

#include <QGraphicsEllipseItem>
#include "common.h"

class Piece : public QGraphicsEllipseItem
{
public:
    Piece(std::pair<int, int>& coordinates, Player player);

private:
    static Piece* m_PieceCurrentlyChosen;

    int row;
    int column;

    const int PIECE_OFFSET_X = 15;
    const int PIECE_OFFSET_Y = 15;
    const int PIECE_SIZE = 50;
    const int PIECE_OUTLINE_WIDTH = 6;

    const QColor BLACK_PIECE_COLOR{50, 50, 50};
    const QColor BLACK_PIECE_OUTLINE_COLOR{0, 0, 0};
    const QColor RED_PIECE_COLOR{220, 0, 0};
    const QColor RED_PIECE_OUTLINE_COLOR{170, 0, 0};
    const QColor PIECE_CHOSEN_OUTLINE_COLOR{255, 255, 0};

    Player m_Player;

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

    void Clicked();
    void Unclicked();
};
