#pragma once

#include "model.h"
#include "input_handler.h"
#include "game_coordinator.h"
#include "window_manager.h"
#include "overlay_manager.h"
#include "qml_helper.h"
#include "state_machine/i_state_actions.h"
#include "state_machine/game_state_manager.h"
#include <QQmlApplicationEngine>

class Controller : public QObject, public IStateActions
{
    Q_OBJECT

signals:
    void applicationShutdownRequested();

public slots:
    void onTileClicked(int row, int column);
    // void onTileClicked(const Coordinates& targetTileCoordinates); // TODO restore int,int version?
    void onQmlEngineFullyInitialized();
    void processKeyPress(int key);
    void onResumeClicked();
    void onRestartClicked();
    void onQuitClicked();
    void onPlayAgainClicked();

public:
    explicit Controller(const GameConfig& gameConfig, Model& model, QQmlApplicationEngine& view);

    // IStateActions implementation
    void startGameLoop() override; // TODO remove or not?
    void stopGameLoop() override; // TODO remove or not?

    void enablePiecesAnimation() override;
    void disablePiecesAnimation() override;

    void showEscapeMenuOverlay() override;
    void hideEscapeMenuOverlay() override;
    void showEndGameOverlay(GameResult gameResult) override;
    void hideEndGameOverlay() override;

    void setGameState(GameStateType newGameState) override;
    void restorePreviousState() override;

    [[nodiscard]] GameStateManager& getStateManager() { return gameStateManager_; }

private:
    Model& model_;
    QQmlApplicationEngine& view_;
    // std::unique_ptr<GameLoop> gameLoop_; // TODO game loop or not?

    QmlHelper qmlHelper_{view_};
    GameStateManager gameStateManager_;
    WindowManager windowManager_;
    std::unique_ptr<OverlayManager> overlayManager_;
    std::unique_ptr<InputHandler> inputHandler_;
    std::unique_ptr<GameCoordinator> gameCoordinator_;
};
