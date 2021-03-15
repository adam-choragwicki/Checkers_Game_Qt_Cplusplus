#pragma once

#include <QGraphicsEllipseItem>
#include "common.h"
#include "coordinates.h"

class Piece : public QGraphicsEllipseItem
{
public:
    Piece(Coordinates coordinates, Player player);
    void MoveToTile(int row, int column);
    int Row() const {return m_Coordinates.Row();}
    int Column() const {return m_Coordinates.Column();}
    Player GetPlayer() const {return m_Player;}

    static Piece* GetActivePiece() {return m_ActivePiece;}

private:
    static Piece* m_ActivePiece;

    Coordinates m_Coordinates;

    const int PIECE_OFFSET_X = 15;
    const int PIECE_OFFSET_Y = 15;
    const int PIECE_SIZE = 50;
    const int PIECE_OUTLINE_WIDTH = 6;

    const QColor BLACK_PIECE_COLOR{50, 50, 50};
    const QColor BLACK_PIECE_OUTLINE_COLOR{0, 0, 0};
    const QColor RED_PIECE_COLOR{220, 0, 0};
    const QColor RED_PIECE_OUTLINE_COLOR{170, 0, 0};
    const QColor PIECE_ACTIVE_OUTLINE_COLOR{255, 255, 0};

    Player m_Player;

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

    void Clicked();
    void Unclicked();
    void ResetActivePiecePointer();
};
