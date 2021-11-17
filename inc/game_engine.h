#pragma once

#include "checkerboard.h"

class GameEngine : public QObject
{
    Q_OBJECT

public:
    GameEngine();

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

    std::unique_ptr<Checkerboard> checkerboard_;
    Piece* multiCaptureInProgressPiece_ = nullptr;

private slots:
    void processTileClicked(const Coordinates& targetTileCoordinates);
};
