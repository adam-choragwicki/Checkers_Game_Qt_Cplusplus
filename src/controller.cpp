#include "controller.h"
#include "piece.h"
#include "selected_piece_manager.h"
#include "piece_capture_manager.h"
#include "piece_movement_manager.h"
#include "piece_promotion_manager.h"
#include "piece_state_manager.h"

Controller::Controller(const GameConfig& gameConfig, Model& model, QQmlApplicationEngine& view) : model_(model), view_(view), gameStateManager_(this)
{
    qInfo() << "Initializing controller";

    // gameCoordinator_ = std::make_unique<GameCoordinator>(model_, *gameLoop_); // TODO game loop or not?
    gameCoordinator_ = std::make_unique<GameCoordinator>(model_);
    inputHandler_ = std::make_unique<InputHandler>(this, &windowManager_);

    // connect(gameLoop_.get(), &GameLoop::endGame, this, &Controller::gameEnded);

    // connect(this, &Controller::sceneUpdateSignal, &view_, &MainWindow::sceneUpdateSlot);
    // connect(&view_, &MainWindow::newGameRequest, this, &Controller::processNewGameRequest);
    // connect(&view_, &MainWindow::applicationTerminationRequest, this, &Controller::processApplicationTerminationRequest);

    // processNewGameRequest();

    checkAndMarkPlayerMoveOptions(model_.getPlayerManager().getActivePlayer());
}

void Controller::onQmlEngineFullyInitialized()
{
    qDebug() << "QML engine fully initialized";

    windowManager_.setWindow(qmlHelper_.getMainWindow());
    overlayManager_ = std::make_unique<OverlayManager>(qmlHelper_);

    // Now that QML is loaded, provide QmlHelper to GameCoordinator
    gameCoordinator_->setQmlHelper(&qmlHelper_);

    qInfo() << "=========================Game started=========================";
    setGameState(GameStateType::ReadyToStart);

    setGameState(GameStateType::Running); // TODO start game immediately, ready to start may not be needed in this game
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
    if (!model_.isGameBeforeFirstRun())
    {
        model_.reset();
        // view_.reset();
    }

    model_.setGameBeforeFirstRun(false);

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

    checkAndMarkPlayerMoveOptions(model_.getPlayerManager().getActivePlayer());
}

void Controller::processApplicationTerminationRequest()
{
    // QCoreApplication::exit(0);
}

void Controller::checkAndMarkPlayerMoveOptions(Player player)
{
    if (model_.getMultiCaptureManager().isMultiCaptureInProgress())
    {
        qDebug() << "Multi capture in progress";

        if (PieceCaptureManager::checkIfPieceCanCapture(*model_.getMultiCaptureManager().getMulticapturingPiece(), model_.getPiecesManager()))
        {
            std::vector<Piece*> piecesWhichCanCapture{model_.getMultiCaptureManager().getMulticapturingPiece()};
            model_.getPiecesManager().markPiecesWhichCanMove(piecesWhichCanCapture);
            return;
        }
        else
        {
            model_.getMultiCaptureManager().endMultiCapture();
        }
    }

    std::vector<Piece*> piecesWhichCanCapture = PieceCaptureManager::whichPiecesCanCapture(player, model_.getPiecesManager());

    if (piecesWhichCanCapture.empty())
    {
        qDebug() << "Player" << static_cast<int>(player) << "has no pieces which can capture";

        std::vector<Piece*> piecesWhichCanMove = PieceMovementManager::whichPiecesCanMove(player, model_.getPiecesManager());

        if (piecesWhichCanMove.empty())
        {
            qInfo() << "Player" << static_cast<int>(player) << "has no pieces which can move, game over";
            endGame(model_.getPlayerManager().getActivePlayer(), GameEndReason::NO_MOVES_LEFT);
        }
        else
        {
            qDebug() << "Player" << static_cast<int>(player) << "has pieces which can move";
            model_.getPiecesManager().markPiecesWhichCanMove(piecesWhichCanMove);
        }
    }
    else
    {
        qDebug() << "Player" << static_cast<int>(player) << "has pieces which can capture";
        model_.getPiecesManager().markPiecesWhichCanMove(piecesWhichCanCapture);
    }
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
            processPieceMove(selectedPiece, targetTileCoordinates);
        }

        // emit sceneUpdateSignal();

        model_.setMoveInProgress(false);
    }
}

void Controller::processPieceMove(Piece& piece, const Coordinates& targetTileCoordinates)
{
    /*If any capture is possible, then any capture has to be the next move*/
    if (PieceCaptureManager::checkIfPieceCanCapture(piece, model_.getPiecesManager()))
    {
        if (PieceCaptureManager::checkCapturePossibility(piece, model_.getPiecesManager(), targetTileCoordinates))
        {
            capturePiece(piece, targetTileCoordinates);

            if (checkEligibilityAndPromotePiece(piece))
            {
                model_.getMultiCaptureManager().endMultiCapture();

                /*Turn ends immediately after promotion, no immediate backward capture is possible*/
                endTurn();
            }
            else if (PieceCaptureManager::checkIfPieceCanCapture(piece, model_.getPiecesManager()))
            {
                model_.getMultiCaptureManager().startMultiCapture(piece);
                disableAllPieces();
                checkAndMarkPlayerMoveOptions(model_.getPlayerManager().getActivePlayer());
            }
            else
            {
                endTurn();
            }
        }
        else
        {
            /*Capture was possible but player chose another tile, so no move was taken and a selected piece is reset*/
            PieceStateManager::deselectPiece(piece);
        }
    }
    else if (PieceMovementManager::checkIfPieceCanMove(piece, model_.getPiecesManager()))
    {
        if (PieceMovementManager::checkMovePossibility(piece, model_.getPiecesManager(), targetTileCoordinates))
        {
            movePiece(piece, targetTileCoordinates);
            checkEligibilityAndPromotePiece(piece);
            endTurn();
        }
    }
    else
    {
        throw std::runtime_error("Error, piece is in undefined state, cannot capture and cannot move");
    }
}

void Controller::disableAllPieces()
{
    for (const auto& piece: model_.getPiecesManager().getPieces())
    {
        if (!piece->isDisabled())
        {
            PieceStateManager::disablePiece(*piece);
        }
    }
}

void Controller::movePiece(Piece& piece, const Coordinates& targetTileCoordinates)
{
    piece.moveToTile(targetTileCoordinates);
}

void Controller::capturePiece(Piece& piece, const Coordinates& targetTileCoordinates)
{
    Coordinates coordinatesOfPieceBetween((targetTileCoordinates.getRow() + piece.getRow()) / 2, (targetTileCoordinates.getColumn() + piece.getColumn()) / 2);

    movePiece(piece, targetTileCoordinates);

    model_.getPiecesManager().killPieceAtCoordinates(coordinatesOfPieceBetween); // TODO add delay, piece should be removed after animation is finished
    // view_.removePieceFrontendAtCoordinates(coordinatesOfPieceBetween);
}

void Controller::endTurn()
{
    qDebug() << "============================================= END TURN =============================================";
    if (model_.getPiecesManager().didAnyPlayerRunOutOfPieces())
    {
        const Player playerWithNoPiecesLeft = model_.getPiecesManager().getPlayerWithNoPiecesLeft();

        qDebug() << "Player" << static_cast<int>(playerWithNoPiecesLeft) << "has no pieces left";

        endGame(playerWithNoPiecesLeft, GameEndReason::NO_PIECES_LEFT);
    }

    disableAllPieces();
    model_.getPlayerManager().switchPlayer();
    checkAndMarkPlayerMoveOptions(model_.getPlayerManager().getActivePlayer());
}

bool Controller::checkEligibilityAndPromotePiece(Piece& piece)
{
    if (PiecePromotionManager::checkPromotionEligibility(piece))
    {
        piece.promote();
        return true;
    }

    return false;
}

void Controller::endGame(const Player losingPlayer, const GameEndReason gameEndReason) // TODO add support for end game reason
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
