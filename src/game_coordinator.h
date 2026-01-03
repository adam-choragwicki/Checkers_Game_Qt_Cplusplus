#pragma once

#include "model.h"
#include "qml_helper.h"
#include "piece_capture_manager.h"
#include "state_machine/game_state_manager.h"
#include "game_end_reason.h"
#include <QTimer>

class GameCoordinator : public QObject
{
    Q_OBJECT

public:
    explicit GameCoordinator(const GameConfig& gameConfig, Model& model, QmlHelper& qmlHelper, IStateActions&  stateActions);

    void startGame();
    void restartGame();
    void processTileClicked(const Coordinates& targetTileCoordinates);

private:
    void movePieceToCoordinates(Piece& piece, const Coordinates& targetTileCoordinates);

    Coordinates getCapturedPieceCoordinates(const Piece& piece, const Coordinates& targetTileCoordinates) const;

    void startNewTurn();
    void endTurn();
    bool checkEligibilityAndPromotePiece(Piece& piece);
    void endGame(const Player& losingPlayer, GameEndReason gameEndReason);
    void checkAndMarkPlayerMoveOptions(const Player& player);

    void onPieceAnimationFinished(Piece* piece, bool movementWasCapture, std::optional<std::reference_wrapper<Piece>> capturedPiece);

    Model& model_;
    QmlHelper& qmlHelper_;
    IStateActions& stateActions_;

    QTimer pieceMovementAnimationTimer_;

    int turnCounter_{};
};
