#pragma once

#include "model.h"
#include "main_window.h"
#include "checkerboard.h"
#include "pieces_placement.h"
#include "multi_capture_manager.h"
#include "game_coordinator.h"
#include "input_handler.h"
#include "overlay_manager.h"
#include "qml_helper.h"
#include "window_manager.h"
#include "state_machine/i_state_actions.h"
#include "state_machine/game_state_manager.h"
#include "game_end_reason.h"
#include <QQmlApplicationEngine>

class Controller : public QObject, public IStateActions
{
    Q_OBJECT

signals:
    void applicationShutdownRequested();
    // void sceneUpdateSignal(); // TODO remove

public slots:
    void processTileClicked(int row, int column);
    // void processTileClicked(const Coordinates& targetTileCoordinates);
    void onQmlEngineFullyInitialized();
    void processKeyPress(int key);
    void onResumeClicked();
    void onRestartClicked();
    void onQuitClicked();
    void onPlayAgainClicked();

public:
    // explicit Controller(const GameConfig& gameConfig, Model& model, MainWindow& view);
    explicit Controller(const GameConfig& gameConfig, Model& model, QQmlApplicationEngine& view);

    // IStateActions implementation
    void startGameLoop() override;
    void stopGameLoop() override;

    void enablePiecesAnimation() override;
    void disablePiecesAnimation() override;

    void showEscapeMenuOverlay() override;
    void hideEscapeMenuOverlay() override;
    void showEndGameOverlay(GameResult gameResult) override;
    void hideEndGameOverlay() override;

    void setGameState(GameStateType newGameState) override;
    void restorePreviousState() override;

    [[nodiscard]] GameStateManager& getStateManager() { return gameStateManager_; }

private slots:
    void processNewGameRequest();
    void processApplicationTerminationRequest();

private:
    void gameEnded(Player losingPlayer, GameEndReason gameEndReason);

    Model& model_;
    QQmlApplicationEngine& view_;
    // std::unique_ptr<GameLoop> gameLoop_;

    QmlHelper qmlHelper_{view_};
    GameStateManager gameStateManager_;
    WindowManager windowManager_;
    std::unique_ptr<OverlayManager> overlayManager_;
    std::unique_ptr<InputHandler> inputHandler_;
    std::unique_ptr<GameCoordinator> gameCoordinator_;
};
