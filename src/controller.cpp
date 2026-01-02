#include "controller.h"
#include "piece.h"

Controller::Controller(const GameConfig& gameConfig, Model& model, QQmlApplicationEngine& view) : gameConfig_(gameConfig), model_(model), view_(view), gameStateManager_(this)
{
    qInfo() << "Initializing controller";

    inputHandler_ = std::make_unique<InputHandler>(this, &windowManager_);

    connect(&gameStateManager_, &GameStateManager::gameStateChanged, this, &Controller::gameStateChanged, Qt::UniqueConnection);
}

void Controller::onQmlEngineFullyInitialized()
{
    qDebug() << "QML engine fully initialized";

    windowManager_.setWindow(qmlHelper_.getMainWindow());
    overlayManager_ = std::make_unique<OverlayManager>(qmlHelper_);

    gameCoordinator_ = std::make_unique<GameCoordinator>(gameConfig_, model_, qmlHelper_, this);

    setGameState(GameStateType::ReadyToStart);
}

void Controller::showEscapeMenuOverlay()
{
    overlayManager_->showEscapeMenuOverlay();
}

void Controller::hideEscapeMenuOverlay()
{
    overlayManager_->hideEscapeMenuOverlay();
}

void Controller::showEndGameOverlay(const GameResult gameResult)
{
    overlayManager_->showEndGameOverlay(gameResult);
}

void Controller::hideEndGameOverlay()
{
    overlayManager_->hideEndGameOverlay();
}

void Controller::setGameState(const GameStateType newGameState)
{
    gameStateManager_.setGameState(newGameState);
}

void Controller::restorePreviousState()
{
    gameStateManager_.restorePreviousGameState();
}

void Controller::processKeyPress(const int key)
{
    // qDebug() << "Key pressed:" << key;
    inputHandler_->processKeyPress(key);
}

void Controller::onPieceClicked(const int pieceId)
{
    if (Piece* piece = model_.getPiecesManager().findPieceById(pieceId))
    {
        Q_ASSERT(pieceId == piece->getId());

        qDebug() << "C++: Piece" << pieceId << "clicked";

        piece->onClicked();
    }
    else
    {
        qFatal("Piece with id %d not found", pieceId);
    }
}

// void Controller::onTileClicked(const Coordinates& targetTileCoordinates)
void Controller::onTileClicked(const int row, const int column) // TODO send coordinates from QML directly?
{
    const Coordinates clickedTileCoordinates(row, column);

    qDebug() << "C++: Tile clicked at coordinates" << clickedTileCoordinates;

    gameCoordinator_->processTileClicked(clickedTileCoordinates);
}

void Controller::onResumeClicked()
{
    qInfo() << "Resume button clicked";
    gameStateManager_.restorePreviousGameState();
}

void Controller::onRestartClicked()
{
    qInfo() << "Restart button clicked";
    gameCoordinator_->restartGame();
    gameStateManager_.setGameState(GameStateType::ReadyToStart);
}

void Controller::onQuitClicked()
{
    qInfo() << "Quit button clicked";
    emit applicationShutdownRequested();
}

void Controller::onPlayAgainClicked()
{
    gameCoordinator_->restartGame();
    gameStateManager_.setGameState(GameStateType::ReadyToStart);
}

void Controller::enablePiecesAnimation()
{
    model_.getPiecesManager().enablePiecesAnimations();
}

void Controller::disablePiecesAnimation()
{
    model_.getPiecesManager().disablePiecesAnimations();
}
