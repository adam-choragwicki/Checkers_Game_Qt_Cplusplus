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
    explicit GameCoordinator(const GameConfig& gameConfig, Model& model, QmlHelper& qmlHelper, IStateActions* stateActions);

    void restartGame();
    void processTileClicked(const Coordinates& targetTileCoordinates);

private:
    void movePieceToCoordinates(Piece& piece, const Coordinates& targetTileCoordinates);

    Coordinates getCapturedPieceCoordinates(const Piece& piece, const Coordinates& targetTileCoordinates) const;
    void killCapturedPiece(const Coordinates& coordinates);

    void endTurn();
    bool checkEligibilityAndPromotePiece(Piece& piece);
    void endGame(Player losingPlayer, GameEndReason gameEndReason);
    void checkAndMarkPlayerMoveOptions(Player player);

    void onPieceAnimationFinished(Piece* piece, bool movementWasCapture, std::optional<Coordinates> capturedPieceCoordinates);

    Model& model_;
    QmlHelper& qmlHelper_;
    IStateActions* stateActions_{};

    QTimer pieceMovementAnimationTimer_;
};
