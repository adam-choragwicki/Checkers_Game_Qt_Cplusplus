#include "game_coordinator.h"

// GameCoordinator::GameCoordinator(Model& model, GameLoop& gameLoop) : model_(model), gameLoop_(gameLoop) // TODO loop or not?
GameCoordinator::GameCoordinator(Model& model, IStateActions* stateActions) : model_(model), stateActions_(stateActions)
{
    checkAndMarkPlayerMoveOptions(model_.getPlayerManager().getActivePlayer());
}

void GameCoordinator::setQmlHelper(QmlHelper* qmlHelper)
{
    qmlHelper_ = qmlHelper;
}

void GameCoordinator::startGameLoop() // TODO remove or not?
{
    // gameLoop_.start();
}

void GameCoordinator::stopGameLoop() // TODO remove or not?
{
    // gameLoop_.stop();
}

void GameCoordinator::restartGame()
{
    qInfo() << "Restarting game";

    if (qmlHelper_)
    {
        // Restore keyboard focus to GameInput
        QMetaObject::invokeMethod(qmlHelper_->getGameInput(), "refocus");
    }

    model_.reset();

    checkAndMarkPlayerMoveOptions(model_.getPlayerManager().getActivePlayer());
}
