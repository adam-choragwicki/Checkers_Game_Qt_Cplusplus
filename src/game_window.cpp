#include "game_window.h"
#include "ui_game_window.h"
#include "drawer.h"

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui_(new Ui::GameWindow)
{
    ui_->setupUi(this);
    setWindowTitle("Checkers");
    setWindowState(Qt::WindowMaximized);
    setFocus(Qt::ActiveWindowFocusReason);

    initializeGameplayAreaScene();

    const QColor backgroundColor(0, 160, 0);
    scene_.setBackgroundBrush(QBrush(backgroundColor));

    QObject::connect(ui_->pushButton_NewGame, &QPushButton::clicked, this, &GameWindow::startNewGame);

    gameEngine_ = std::make_unique<GameEngine>();
}

void GameWindow::initializeGameplayAreaScene()
{
    ui_->graphicsView->setScene(&scene_);
    ui_->graphicsView->setRenderHint(QPainter::Antialiasing);

    Drawer::setScene(&scene_);
}

void GameWindow::startNewGame()
{
    gameEngine_->restartGame();
}

GameWindow::~GameWindow()
{
    delete ui_;
}
