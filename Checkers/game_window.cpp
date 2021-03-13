#include "game_window.h"
#include "./ui_game_window.h"

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    setWindowTitle("Checkers");
    setWindowState(Qt::WindowMaximized);

    ui->graphicsView->setScene(&m_Scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    const QColor BACKGROUND_COLOR(0, 160, 0);
    m_Scene.setBackgroundBrush(QBrush(BACKGROUND_COLOR));

    CreateAndPopulateBoard(m_Scene);
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::CreateAndPopulateBoard(QGraphicsScene& scene)
{
    m_pBoard = new Board(scene);
    m_Scene.addItem(m_pBoard);
}
