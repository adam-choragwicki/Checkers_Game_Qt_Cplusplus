#include "game_window.h"
#include "./ui_game_window.h"
#include <QGraphicsRectItem>
#include "piece.h"
#include "logic.h"
#include "board.h"
#include "tile.h"

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

    DrawBoard();
    PopulateBoard();
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::DrawBoard()
{
    Board* board = new Board;
    m_Scene.addItem(board);

    for(int row = 0; row < 8; row++)
    {
        for(int column = 0; column < 8; column++)
        {
            Tile* tile = new Tile(row, column);
            m_Scene.addItem(tile);
        }
    }
}

void GameWindow::PopulateBoard()
{
    std::vector<std::pair<int, int>> playerLowerStartingPiecesCoordinates = Logic::GenerateStartingPiecesCoordinates(Player::Down);
    std::vector<std::pair<int, int>> playerUpperStartingPiecesCoordinates = Logic::GenerateStartingPiecesCoordinates(Player::Up);

    for(auto pieceCoordinates : playerLowerStartingPiecesCoordinates)
    {
        Piece* piece = new Piece(pieceCoordinates, Player::Down);
        m_Scene.addItem(piece);
    }

    for(auto pieceCoordinates : playerUpperStartingPiecesCoordinates)
    {
        Piece* piece = new Piece(pieceCoordinates, Player::Up);
        m_Scene.addItem(piece);
    }
}
