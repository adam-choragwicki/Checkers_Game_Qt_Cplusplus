#include "controller.h"
#include "piece.h"
#include "selected_piece_manager.h"
#include "piece_capture_manager.h"
#include "piece_movement_manager.h"
#include "piece_promotion_manager.h"
#include "piece_state_manager.h"
// #include <QCoreApplication>

Controller::Controller(const GameConfig& gameConfig, Model& model, QQmlApplicationEngine& view) : model_(model), view_(view)
{
    // connect(this, &Controller::sceneUpdateSignal, &view_, &MainWindow::sceneUpdateSlot);
    // connect(&view_, &MainWindow::newGameRequest, this, &Controller::processNewGameRequest);
    // connect(&view_, &MainWindow::applicationTerminationRequest, this, &Controller::processApplicationTerminationRequest);

    // processNewGameRequest();

    checkAndMarkPlayerMoveOptions(model_.getPlayerManager().getActivePlayer());
}

void Controller::onQmlEngineFullyInitialized()
{
    qDebug() << "QML engine fully initialized";

    // windowManager_.setWindow(qmlHelper_.getMainWindow());
    // overlayManager_ = std::make_unique<OverlayManager>(qmlHelper_);

    // Now that QML is loaded, provide QmlHelper to GameCoordinator
    // gameCoordinator_->setQmlHelper(&qmlHelper_);

    qInfo() << "=========================Game started=========================";
    // setGameState(GameStateType::ReadyToStart);
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
        // model_.getPiecesModel().refresh();

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
            /*Capture was possible but player chose other tile so no move was taken and selected piece is reset*/
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
    // model_.getPiecesModel().refresh();
}

void Controller::capturePiece(Piece& piece, const Coordinates& targetTileCoordinates)
{
    Coordinates coordinatesOfPieceBetween((targetTileCoordinates.getRow() + piece.getRow()) / 2, (targetTileCoordinates.getColumn() + piece.getColumn()) / 2);

    movePiece(piece, targetTileCoordinates);

    model_.getPiecesManager().removePieceAtCoordinates(coordinatesOfPieceBetween);
    // view_.removePieceFrontendAtCoordinates(coordinatesOfPieceBetween);
}

void Controller::endTurn()
{
    qDebug() << "============================================= END TURN =============================================";
    if (model_.getPiecesManager().didAnyPlayerRunOutOfPieces())
    {
        endGame(model_.getPiecesManager().getPlayerWithNoPiecesLeft(), GameEndReason::NO_PIECES_LEFT);
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

void Controller::endGame(Player losingPlayer, GameEndReason gameEndReason)
{
    // view_.showEndGameDialog(losingPlayer, gameEndReason);
}
