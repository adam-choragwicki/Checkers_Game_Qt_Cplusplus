#pragma once

#include "checkerboard.h"

class GameEngine : public QObject
{
    Q_OBJECT

public:
    GameEngine();

    Checkerboard& getCheckerboard() {return checkerboard_;}

public slots:
    void restartGame();

private:
    void startGame();
    void clearPreviousGame();
    void unmarkAllPieces();
    void movePiece(Piece* piece, const Coordinates& targetTileCoordinates);
    void capturePiece(Piece* piece, const Coordinates& targetTileCoordinates);
    void endTurn();
    bool isMultiCaptureInProgress();
    void processMove(const Coordinates& targetTileCoordinates);
    void checkAndMarkPlayerMoveOptions(Player player);
    void checkEligibilityAndPromotePiece(Piece* piece);

    Checkerboard checkerboard_;

private:
    Piece* multiCaptureInProgressPiece_ = nullptr;

private slots:
    void processTileClickedSlot(const Coordinates& targetTileCoordinates);
};
