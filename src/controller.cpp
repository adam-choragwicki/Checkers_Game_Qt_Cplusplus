#include "controller.h"
#include "piece.h"
#include "selected_piece_manager.h"

Controller::Controller(const GameConfig& gameConfig, Model& model, QQmlApplicationEngine& view) : model_(model), view_(view), gameStateManager_(this)
{
    qInfo() << "Initializing controller";

    // gameCoordinator_ = std::make_unique<GameCoordinator>(model_, *gameLoop_); // TODO game loop or not?
    gameCoordinator_ = std::make_unique<GameCoordinator>(model_);
    inputHandler_ = std::make_unique<InputHandler>(this, &windowManager_);

    // connect(gameLoop_.get(), &GameLoop::endGame, this, &Controller::gameEnded);

    connect(gameCoordinator_.get(), &GameCoordinator::endGame, this, &Controller::gameEnded);

    // connect(this, &Controller::sceneUpdateSignal, &view_, &MainWindow::sceneUpdateSlot);
    // connect(&view_, &MainWindow::newGameRequest, this, &Controller::processNewGameRequest);
    // connect(&view_, &MainWindow::applicationTerminationRequest, this, &Controller::processApplicationTerminationRequest);

    // processNewGameRequest();

    // checkAndMarkPlayerMoveOptions(model_.getPlayerManager().getActivePlayer());
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

void Controller::startGameLoop()
{
    qDebug() << "Controller::startGameLoop()";
    gameCoordinator_->startGameLoop();
}

void Controller::stopGameLoop()
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

void Controller::processNewGameRequest()
{
    // for (PlayableTile* playableTile: model_.getCheckerboard().getPlayableTiles())
    // {
    //     connect(playableTile, &PlayableTile::clickedSignal, this, &Controller::processTileClicked);
    // }

    // for(PieceFrontend* pieceFrontend : view_.getPiecesFrontends())
    // {
    //     connect(&pieceFrontend->getPiece(), &Piece::stateChanged, &view_, &MainWindow::sceneUpdateSlot);
    //     connect(&pieceFrontend->getPiece(), &Piece::startAnimatedMovement, pieceFrontend, &PieceFrontend::animateMovementToNewCoordinates);
    //     connect(&pieceFrontend->getPiece(), &Piece::promoted, pieceFrontend, &PieceFrontend::addCrown);
    //     connect(pieceFrontend, &PieceFrontend::endMovement, &pieceFrontend->getPiece(), &Piece::processEndMovement);
    // }

    gameCoordinator_->checkAndMarkPlayerMoveOptions(model_.getPlayerManager().getActivePlayer());
}

void Controller::processApplicationTerminationRequest()
{
    // QCoreApplication::exit(0);
}



// void Controller::processTileClicked(const Coordinates& targetTileCoordinates)
void Controller::processTileClicked(const int row, const int column) // TODO send coordinates from QML directly?
{
    const Coordinates targetTileCoordinates(row, column);

    qDebug() << "C++: Tile clicked at coordinates" << targetTileCoordinates;

    if (!model_.isMoveInProgress())
    {
        model_.setMoveInProgress(true);

        /*Ignore clicking on tile unless any piece is selected*/
        if (SelectedPieceManager::isAnyPieceSelected())
        {
            Piece& selectedPiece = SelectedPieceManager::getSelectedPiece();
            gameCoordinator_->processPieceMove(selectedPiece, targetTileCoordinates);
        }

        // emit sceneUpdateSignal();

        model_.setMoveInProgress(false);
    }
}

void Controller::gameEnded(const Player losingPlayer, const GameEndReason gameEndReason) // TODO add support for end game reason
{
    // NOTE the function accepts LOSING player as a parameter

    qInfo() << "Ending game";

    if (gameEndReason == GameEndReason::NO_MOVES_LEFT)
    {
        qDebug() << "Player" << static_cast<int>(losingPlayer) << "has no moves left";
    }
    else if (gameEndReason == GameEndReason::NO_PIECES_LEFT)
    {
        qDebug() << "Player" << static_cast<int>(losingPlayer) << "has no pieces left";
    }
    else
    {
        Q_UNREACHABLE();
    }

    if (losingPlayer == Player::LOWER)
    {
        setGameState(GameStateType::EndedVictoryPlayerUpper);
    }
    else if (losingPlayer == Player::UPPER)
    {
        setGameState(GameStateType::EndedVictoryPlayerLower);
    }
    else
    {
        Q_UNREACHABLE();
    }

    // view_.showEndGameDialog(losingPlayer, gameEndReason);
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
