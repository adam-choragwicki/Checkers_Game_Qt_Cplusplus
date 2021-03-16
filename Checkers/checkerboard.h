#pragma once

#include <QGraphicsRectItem>
#include <map>
#include "piece.h"

class Checkerboard : public QGraphicsRectItem
{
public:
    Checkerboard(QGraphicsScene& scene);
    static void ProcessTileClicked(const int targetRow, const int targetColumn, bool tileIsPlayable);

private:
    const int BOARD_POSITION_X = 0;
    const int BOARD_POSITION_Y = 0;
    const int BOARD_SIZE = 640;
    const int BOARD_OUTLINE_WIDTH = 10;
    const QColor BOARD_OUTLINE_COLOR{150, 100, 40};

    static std::map<Coordinates, Piece*> m_PiecesPlacement;

    void CreateTiles(QGraphicsScene& scene);
    void CreatePieces(QGraphicsScene& scene);
    static bool CheckMove(Piece* activePiece, const int targetRow, const int targetColumn);
    static void MovePiece(Piece* activePiece, const int targetRow, const int targetColumn);
    static bool CheckCapture(Piece* activePiece, const int targetRow, const int targetColumn);
    static void CapturePiece(Piece* activePiece, const int targetRow, const int targetColumn);
};
