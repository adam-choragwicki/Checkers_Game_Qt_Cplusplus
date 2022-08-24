#pragma once

#include "checkerboard.h"
#include "pieces_placement.h"
#include "multi_capture_manager.h"

class GameEngine : public QObject
{
Q_OBJECT

signals:
    void sceneUpdateSignal();
    void dialogRestartGameSignal(Player player, GameEndReason gameEndReason);

public:
    explicit GameEngine(const QVector<Tile*>& playableTiles);

public slots:
    void processTileClickedSlot(const Coordinates& targetTileCoordinates);

private:
    void disableAllPieces();
    void movePiece(Piece* piece, const Coordinates& targetTileCoordinates);
    void capturePiece(Piece* piece, const Coordinates& targetTileCoordinates);
    void endTurn();

    void processPieceMove(Piece* piece, const Coordinates& targetTileCoordinates);
    void checkAndMarkPlayerMoveOptions(Player player);
    bool checkEligibilityAndPromotePiece(Piece* piece);

    PiecesPlacement piecesPlacement_;
    MultiCaptureManager multiCaptureManager_;
    PlayerManager playerManager_;
    bool moveInProgress_ = false;

private:
    void endGame(Player losingPlayer, GameEndReason gameEndReason);
};
