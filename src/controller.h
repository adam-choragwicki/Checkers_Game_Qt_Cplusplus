#pragma once

#include "model/model.h"
#include "frontend/main_window.h"
#include "frontend/checkerboard.h"
#include "pieces_placement.h"
#include "multi_capture_manager.h"

class Controller : public QObject
{
Q_OBJECT

signals:
    void sceneUpdateSignal();

public slots:
    void processTileClicked(const Coordinates& targetTileCoordinates);

private slots:
    void processNewGameRequest();
    void processApplicationTerminationRequest();

public:
    explicit Controller(Model& model, MainWindow& view);

private:
    void disableAllPieces();
    void movePiece(Piece& piece, const Coordinates& targetTileCoordinates);
    void capturePiece(Piece& piece, const Coordinates& targetTileCoordinates);
    void endTurn();
    void endGame(Player losingPlayer, GameEndReason gameEndReason);

    void processPieceMove(Piece& piece, const Coordinates& targetTileCoordinates);
    void checkAndMarkPlayerMoveOptions(Player player);
    bool checkEligibilityAndPromotePiece(Piece& piece);

    Model& model_;
    MainWindow& view_;
};
