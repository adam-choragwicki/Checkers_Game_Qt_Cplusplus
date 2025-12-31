#pragma once

#include "model.h"
#include "qml_helper.h"

#include "piece_capture_manager.h"
#include "state_machine/game_state_manager.h"
#include "game_end_reason.h"

class GameCoordinator : public QObject
{
    Q_OBJECT

public:
    explicit GameCoordinator(Model& model, IStateActions* stateActions);
    void setQmlHelper(QmlHelper* qmlHelper);

    void restartGame();

    void checkAndMarkPlayerMoveOptions(Player player);

    void processPieceMove(Piece& piece, const Coordinates& targetTileCoordinates);

    void movePieceToCoordinates(Piece& piece, const Coordinates& targetTileCoordinates);

    void capturePiece(Piece& piece, const Coordinates& targetTileCoordinates);

    void endTurn();

    bool checkEligibilityAndPromotePiece(Piece& piece);

    void endGame(Player losingPlayer, GameEndReason gameEndReason);

private:
    Model& model_;
    QmlHelper* qmlHelper_{};

    IStateActions* stateActions_{};
};
