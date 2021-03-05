#include "game_window.h"
#include "./ui_game_window.h"
#include <QGraphicsRectItem>

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    setWindowTitle("Checkers");
    setWindowState(Qt::WindowMaximized);

    ui->graphicsView->setScene(&m_Scene);

    const QColor BACKGROUND_COLOR(0, 160, 0);
    m_Scene.setBackgroundBrush(QBrush(BACKGROUND_COLOR));

    DrawBoard();
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::DrawBoard()
{
    const int BOARD_POSITION_X = 0;
    const int BOARD_POSITION_Y = 0;
    const int BOARD_WIDTH = 640;
    const int BOARD_HEIGHT = 640;
    const QColor BOARD_OUTLINE_COLOR(150, 100, 40);
    const int BOARD_OUTLINE_WIDTH = 10;

    m_pBoard = new QGraphicsRectItem(BOARD_POSITION_X, BOARD_POSITION_Y, BOARD_WIDTH, BOARD_HEIGHT);
    m_pBoard->setPen(QPen(BOARD_OUTLINE_COLOR, BOARD_OUTLINE_WIDTH));

    m_Scene.addItem(m_pBoard);

    const int TILE_SIZE = 80;
    const QColor BROWN_TILE_COLOR(140, 90, 40);
    const QColor WHITE_TILE_COLOR(230, 200, 160);

    for(int row = 0; row < 8; row++)
    {
        for(int column = 0; column < 8; column++)
        {
            QGraphicsRectItem* tile = new QGraphicsRectItem(row * TILE_SIZE, column * TILE_SIZE, TILE_SIZE, TILE_SIZE);

            if(row % 2 == 0)
            {
                column % 2 == 0 ? tile->setBrush(QBrush(WHITE_TILE_COLOR)) : tile->setBrush(QBrush(BROWN_TILE_COLOR));
            }
            else
            {
                column % 2 == 0 ? tile->setBrush(QBrush(BROWN_TILE_COLOR)) : tile->setBrush(QBrush(WHITE_TILE_COLOR));
            }

            tile->setPen(QPen(tile->brush().color()));
            m_Scene.addItem(tile);
        }
    }
}
