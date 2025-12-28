#include "controller.h"
#include "piece.h"
#include "selected_piece_manager.h"

Controller::Controller(const GameConfig& gameConfig, Model& model, QQmlApplicationEngine& view) : model_(model), view_(view), gameStateManager_(this)
{
    qInfo() << "Initializing controller";

    // gameCoordinator_ = std::make_unique<GameCoordinator>(model_, *gameLoop_); // TODO game loop or not?
    gameCoordinator_ = std::make_unique<GameCoordinator>(model_, this);
    inputHandler_ = std::make_unique<InputHandler>(this, &windowManager_);

    // connect(gameLoop_.get(), &GameLoop::endGame, this, &Controller::gameEnded);

    connect(&gameStateManager_, &GameStateManager::gameStateChanged, this, &Controller::gameStateChanged, Qt::UniqueConnection);
}

void Controller::onQmlEngineFullyInitialized()
{
    qDebug() << "QML engine fully initialized";

    windowManager_.setWindow(qmlHelper_.getMainWindow());
    overlayManager_ = std::make_unique<OverlayManager>(qmlHelper_);

    // Now that QML is loaded, provide QmlHelper to GameCoordinator
    gameCoordinator_->setQmlHelper(&qmlHelper_);

    setGameState(GameStateType::ReadyToStart);
}

void Controller::startGameLoop() // TODO remove or not?
{
    qDebug() << "Controller::startGameLoop()";
    gameCoordinator_->startGameLoop();
}

void Controller::stopGameLoop() // TODO remove or not?
{
    qDebug() << "Controller::stopGameLoop()";
    gameCoordinator_->stopGameLoop();
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

        if (piece->isActive())
        {
            qDebug() << "C++: Setting piece" << pieceId << "as selected";
            piece->setState(Piece::State::SELECTED);
        }
    }
    else
    {
        qFatal("Piece with id %d not found", pieceId);
    }
}

// void Controller::onTileClicked(const Coordinates& targetTileCoordinates)
void Controller::onTileClicked(const int row, const int column) // TODO send coordinates from QML directly?
{
    const Coordinates targetTileCoordinates(row, column);

    qDebug() << "C++: Tile clicked at coordinates" << targetTileCoordinates;

    if (!model_.isMoveInProgress())
    {
        model_.setMoveInProgress(true);

        /*Ignore clicking on a tile unless any piece is selected*/
        if (SelectedPieceManager::isAnyPieceSelected())
        {
            Piece& selectedPiece = SelectedPieceManager::getSelectedPiece();
            gameCoordinator_->processPieceMove(selectedPiece, targetTileCoordinates);
        }

        model_.setMoveInProgress(false);
    }
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
