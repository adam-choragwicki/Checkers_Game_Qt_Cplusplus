#pragma once

#include <QGraphicsRectItem>
#include <map>
#include "piece.h"

class Checkerboard : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
    friend class CheckerboardTest;

public:
    Checkerboard(QGraphicsScene& scene);

public slots:
    void RestartGame(QGraphicsScene& scene);

private:
    const int BOARD_POSITION_X = 0;
    const int BOARD_POSITION_Y = 0;
    const int BOARD_SIZE = 640;
    const int BOARD_OUTLINE_WIDTH = 10;
    const QColor BOARD_OUTLINE_COLOR{150, 100, 40};

    std::map<Coordinates, Piece*> m_PiecesPlacement;
    Piece* m_MultiCaptureInProgressPiece = nullptr;

    void StartNewGame(QGraphicsScene& scene);
    void ClearPreviousGame(QGraphicsScene& scene);
    void CreateTiles(QGraphicsScene& scene);
    void CreatePieces(QGraphicsScene& scene);
    void CreatePiecesCustomCoordinates(QGraphicsScene& scene);
    void MarkPieces(std::vector<Piece*>& pieces);
    void UnmarkAllPieces();
    void MovePiece(Piece* piece, const Coordinates& targetTileCoordinates);
    void CapturePiece(Piece* piece, const Coordinates& targetTileCoordinates);
    void EndTurn();
    bool IsMultiCaptureInProgress();
    void ProcessMove(const Coordinates& targetTileCoordinates);
    void CheckAndMarkPlayerMoveOptions(Player player);
    void CheckEligibilityAndPromotePiece(Piece* piece);
    
private slots:
    void ProcessTileClicked(const Coordinates& targetTileCoordinates);
};
