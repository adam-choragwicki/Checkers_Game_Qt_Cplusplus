#pragma once

#include "model.h"
#include "qml_helper.h"

#include "piece_capture_manager.h"
#include "state_machine/game_state_manager.h"

class GameCoordinator : public QObject
{
    Q_OBJECT

public:
    explicit GameCoordinator(Model& model, IStateActions* stateActions);
    void setQmlHelper(QmlHelper* qmlHelper);

    void startGameLoop(); // TODO remove or not?
    void stopGameLoop(); // TODO remove or not?

    void restartGame();

    void checkAndMarkPlayerMoveOptions(Player player);

    void processPieceMove(Piece& piece, const Coordinates& targetTileCoordinates);

    void movePiece(Piece& piece, const Coordinates& targetTileCoordinates);

    void capturePiece(Piece& piece, const Coordinates& targetTileCoordinates);

    void endTurn();

    void disableAllPieces();

    bool checkEligibilityAndPromotePiece(Piece& piece);

    void endGame(const Player losingPlayer, GameEndReason gameEndReason);

private:
    Model& model_;
    // GameLoop& gameLoop_;
    QmlHelper* qmlHelper_{};

    IStateActions* stateActions_{};
};
