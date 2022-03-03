#include "game_window.h"
#include "ui_game_window.h"

GameWindow::GameWindow(GameEngine& gameEngine, QWidget* parent)
        : QMainWindow(parent),
          ui_(new Ui::GameWindow),
          gameEngine_(gameEngine)
{
    ui_->setupUi(this);

    setWindowTitle("Checkers");
    setWindowState(Qt::WindowMaximized);
    setFocus(Qt::ActiveWindowFocusReason);

    initializeGameplayAreaScene();

    drawCheckerboard();

    QObject::connect(ui_->pushButton_NewGame, &QPushButton::clicked, this, &GameWindow::processNewGameButtonClickedSlot);
    QObject::connect(&gameEngine_, &GameEngine::sceneUpdateSignal, this, &GameWindow::sceneUpdateSlot);
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
}

void GameWindow::drawCheckerboard()
{
    scene_.addItem(&gameEngine_.getCheckerboard());
}

void GameWindow::sceneUpdateSlot()
{
    scene_.update();
}

void GameWindow::processNewGameButtonClickedSlot()
{
    gameEngine_.restartGame();
}
