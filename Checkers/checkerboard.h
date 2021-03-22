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
    static Piece* m_MultiCaptureInProgressPiece;

    void CreateTiles(QGraphicsScene& scene);
    void CreatePieces(QGraphicsScene& scene);
    void CreatePiecesCustomCoordinates(QGraphicsScene& scene);
    static void MarkPieces(std::vector<Piece*>& pieces);
    static void UnmarkAllPieces();
    static void MovePiece(Piece* piece, const int targetRow, const int targetColumn);
    static void CapturePiece(Piece* piece, const int targetRow, const int targetColumn);
    static void EndTurn();

    static bool IsMultiCaptureInProgress();
};
