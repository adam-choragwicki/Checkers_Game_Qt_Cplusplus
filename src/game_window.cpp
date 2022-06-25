#include "game_window.h"
#include "ui_game_window.h"
#include "drawer.h"

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
}

GameWindow::~GameWindow()
{
    delete ui_;
}

void GameWindow::closeEvent(QCloseEvent*)
{
    exit(0);
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
    gameEngine_ = std::make_unique<GameEngine>(checkerboard_->getPlayableTiles());
    QObject::connect(gameEngine_.get(), &GameEngine::sceneUpdateSignal, this, &GameWindow::sceneUpdateSlot);
}
