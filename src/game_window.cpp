#include "game_window.h"
#include "ui_game_window.h"
#include "drawer.h"

#include <QMessageBox>

GameWindow::GameWindow(QWidget* parent)
        : QMainWindow(parent),
          ui_(new Ui::GameWindow)
{
    ui_->setupUi(this);
    setWindowTitle("Checkers");
    setFocus(Qt::ActiveWindowFocusReason);
    setWindowState(Qt::WindowMaximized);

    QObject::connect(ui_->pushButton_NewGame, &QPushButton::clicked, this, &GameWindow::processNewGameButtonClickedSlot);

    initializeGameplayAreaScene();

    checkerboard_ = std::make_unique<Checkerboard>();
    gameEngine_ = std::make_unique<GameEngine>(checkerboard_->getPlayableTiles());
    QObject::connect(gameEngine_.get(), &GameEngine::sceneUpdateSignal, this, &GameWindow::sceneUpdateSlot);
    QObject::connect(gameEngine_.get(), &GameEngine::dialogRestartGameSignal, this, &GameWindow::dialogRestartGameSlot);
}

GameWindow::~GameWindow()
{
    delete ui_;
}

void GameWindow::closeEvent(QCloseEvent*)
{
    QApplication::exit(static_cast<int>(Status::exit));
}

void GameWindow::initializeGameplayAreaScene()
{
    ui_->graphicsView->setScene(&scene_);
    ui_->graphicsView->setRenderHint(QPainter::Antialiasing);

    const QColor backgroundColor(0, 160, 0);
    scene_.setBackgroundBrush(QBrush(backgroundColor));

    Drawer::setScene(&scene_);
}

void GameWindow::sceneUpdateSlot()
{
    scene_.update();
}

void GameWindow::processNewGameButtonClickedSlot()
{
    QApplication::exit(static_cast<int>(Status::restart));
}

void GameWindow::dialogRestartGameSlot(Player losingPlayer, GameEndReason reason)
{
    QString losingPlayerString = (losingPlayer == Player::down) ? "Black" : "Red";
    QString message;

    if(reason == GameEndReason::NoPiecesLeft)
    {
        message = losingPlayerString + " are out of pieces";
    }
    else if(reason == GameEndReason::NoMovesLeft)
    {
        message = losingPlayerString + " are out of moves";
    }
    else
    {
        throw std::runtime_error("Unsupported game end reason");
    }

    message += ", restart?";

    int response = QMessageBox::question(this, "Game over", message, QMessageBox::StandardButton::Ok, QMessageBox::StandardButton::Cancel);

    if(response == QMessageBox::Ok)
    {
        QApplication::exit(static_cast<int>(Status::restart));
    }
    else
    {
        QApplication::exit(static_cast<int>(Status::exit));
    }
}
