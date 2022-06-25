#pragma once

#include "checkerboard.h"
#include "pieces_placement.h"

class GameEngine : public QObject
{
Q_OBJECT

signals:
    void sceneUpdateSignal();

public:
    explicit GameEngine(const QVector<Tile*>& playableTiles);

public slots:
    void processTileClickedSlot(const Coordinates& targetTileCoordinates);

private:
    void unmarkAllPieces();
    void movePiece(Piece* piece, const Coordinates& targetTileCoordinates);
    void capturePiece(Piece* piece, const Coordinates& targetTileCoordinates);
    void endTurn();
    bool isMultiCaptureInProgress();
    void processMove(const Coordinates& targetTileCoordinates);
    void checkAndMarkPlayerMoveOptions(Player player);
    void checkEligibilityAndPromotePiece(Piece* piece);

    PiecesPlacement piecesPlacement_;

private:
    Piece* multiCaptureInProgressPiece_ = nullptr;
};
