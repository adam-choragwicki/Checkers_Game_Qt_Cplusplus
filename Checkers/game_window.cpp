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

    m_Scene.setBackgroundBrush(QBrush(QColor(Qt::green)));

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
    const int BOARD_WIDTH = 700;
    const int BOARD_HEIGHT = 700;

    const QColor BOARD_OUTLINE_COLOR(Qt::white);
    const int BOARD_OUTLINE_WIDTH = 10;

    const int TILE_SIZE = 80;
    const QColor TILE_OUTLINE_COLOR(Qt::red);
    const int TILE_OUTLINE_WIDTH = 2;

    QGraphicsRectItem* board = new QGraphicsRectItem(BOARD_POSITION_X, BOARD_POSITION_Y, BOARD_WIDTH, BOARD_HEIGHT);
    board->setBrush(QBrush(QColor(Qt::black)));
    board->setPen(QPen(BOARD_OUTLINE_COLOR, BOARD_OUTLINE_WIDTH));

    m_Scene.addItem(board);

    for(int row = 0; row < 8; row++)
    {
        for(int column = 0; column < 8; column++)
        {
            QGraphicsRectItem* tile = new QGraphicsRectItem(row * TILE_SIZE, column * TILE_SIZE, TILE_SIZE, TILE_SIZE);
            tile->setBrush(QBrush(QColor(Qt::cyan)));
            tile->setPen(QPen(TILE_OUTLINE_COLOR, TILE_OUTLINE_WIDTH));
            tile->setFlag(QGraphicsItem::GraphicsItemFlag::ItemIsSelectable);
            tile->setAcceptHoverEvents(true);
            m_Scene.addItem(tile);
        }
    }
}
