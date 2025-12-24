#include "main_window.h"
#include "ui_main_window.h"
#include "drawer.h"
#include <QMessageBox>
#include <QCloseEvent>

MainWindow::MainWindow(const Model& model) : model_(model), ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);
    setWindowTitle("Checkers");
    setFocus(Qt::ActiveWindowFocusReason);

    connect(ui_->pushButton_NewGame, &QPushButton::clicked, this, &MainWindow::newGameRequest);

    initializeGameplayAreaScene();

    // checkerboard_ = std::make_unique<Checkerboard>();

    reset();

    setFixedSize(730, 800);

    centerOnPrimaryScreen();
}

MainWindow::~MainWindow()
{
    delete ui_;
}

void MainWindow::centerOnPrimaryScreen()
{
    QScreen* primaryScreen = QGuiApplication::primaryScreen();
    centerOnScreen(primaryScreen);
}

void MainWindow::centerOnScreen(QScreen* screen)
{
    setScreen(screen);
    const QRect screenRect = screen->availableGeometry();
    const QRect widgetRect({}, frameSize().boundedTo(screenRect.size()));
    move(screenRect.center() - widgetRect.center());
}

void MainWindow::reset()
{
    // piecesFrontends_.clear();
    //
    // for(const auto& piece : model_.getPiecesPlacement().getPieces())
    // {
    //     piecesFrontends_.push_back(std::make_unique<PieceFrontend>(*piece));
    // }
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    event->ignore();
    emit applicationTerminationRequest();
}

void MainWindow::initializeGameplayAreaScene()
{
    ui_->graphicsView->setScene(&scene_);
    ui_->graphicsView->setRenderHint(QPainter::Antialiasing);

    const QColor backgroundColor(0, 160, 0);
    scene_.setBackgroundBrush(QBrush(backgroundColor));

    Drawer::setScene(&scene_);
}

// void MainWindow::sceneUpdateSlot()
// {
//     scene_.update();
//     updatePiecesFrontends();
// }

void MainWindow::showEndGameDialog(Player losingPlayer, GameEndReason reason)
{
    QString losingPlayerString = (losingPlayer == Player::LOWER) ? "Black" : "Red";
    QString message;

    if(reason == GameEndReason::NO_PIECES_LEFT)
    {
        message = losingPlayerString + " are out of pieces";
    }
    else if(reason == GameEndReason::NO_MOVES_LEFT)
    {
        message = losingPlayerString + " are out of moves";
    }
    else
    {
        throw std::runtime_error("Error, unsupported src end reason");
    }

    message += ", RESTART?";

    int response = QMessageBox::question(this, "Game over", message, QMessageBox::StandardButton::Ok, QMessageBox::StandardButton::Cancel);

    if(response == QMessageBox::Ok)
    {
        emit newGameRequest();
    }
    else
    {
        emit applicationTerminationRequest();
    }
}

// std::vector<PlayableTile*> MainWindow::getPlayableTiles() const
// {
//     return checkerboard_->getPlayableTiles();
// }

// std::vector<PieceFrontend*> MainWindow::getPiecesFrontends() const
// {
//     std::vector<PieceFrontend*> piecesFrontends;
//
//     for(const auto& pieceFrontend : piecesFrontends_)
//     {
//         piecesFrontends.push_back(pieceFrontend.get());
//     }
//
//     return piecesFrontends;
// }

// void MainWindow::updatePiecesFrontends()
// {
//     for(const auto& elem : piecesFrontends_)
//     {
//         elem->updateColours();
//     }
// }

// void MainWindow::removePieceFrontendAtCoordinates(const Coordinates& coordinates)
// {
//     auto iter = std::ranges::find_if(piecesFrontends_, [coordinates](const auto& pieceFrontend)
//     {
//         return pieceFrontend->getPiece().getCoordinates() == coordinates;
//     });
//
//     if(iter != piecesFrontends_.end())
//     {
//         piecesFrontends_.erase(iter);
//     }
//     else
//     {
//         throw std::runtime_error("Error, trying to remove piece frontend which is not present in pieces frontends");
//     }
// }
