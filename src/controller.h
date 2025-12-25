#pragma once

#include "model.h"
#include "main_window.h"
#include "checkerboard.h"
#include "pieces_placement.h"
#include "multi_capture_manager.h"
#include <QQmlApplicationEngine>

class Controller : public QObject
{
    Q_OBJECT

signals:
    void applicationShutdownRequested();

signals:
    void sceneUpdateSignal();

public slots:
    void processTileClicked(int row, int column);
    // void processTileClicked(const Coordinates& targetTileCoordinates);
    void onQmlEngineFullyInitialized();

private slots:
    void processNewGameRequest();
    void processApplicationTerminationRequest();

public:
    // explicit Controller(const GameConfig& gameConfig, Model& model, MainWindow& view);
    explicit Controller(const GameConfig& gameConfig, Model& model, QQmlApplicationEngine& view);

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
    QQmlApplicationEngine& view_;
};
