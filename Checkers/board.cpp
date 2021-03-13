#include "board.h"
#include "piece.h"
#include "logic.h"
#include "tile.h"
#include <QPen>
#include <QGraphicsScene>

Board::Board(QGraphicsScene& scene)
{
    QGraphicsRectItem::setRect(BOARD_POSITION_X, BOARD_POSITION_Y, BOARD_SIZE, BOARD_SIZE);
    setPen(QPen(BOARD_OUTLINE_COLOR, BOARD_OUTLINE_WIDTH));

    CreateTiles(scene);
    CreatePieces(scene);
}

void Board::CreateTiles(QGraphicsScene& scene)
{
    for(int row = 0; row < 8; row++)
    {
        for(int column = 0; column < 8; column++)
        {
            Tile* tile = new Tile(row, column);
            scene.addItem(tile);
        }
    }
}

void Board::CreatePieces(QGraphicsScene& scene)
{
    std::vector<std::pair<int, int>> playerLowerStartingPiecesCoordinates = Logic::GenerateStartingPiecesCoordinates(Player::Down);
    std::vector<std::pair<int, int>> playerUpperStartingPiecesCoordinates = Logic::GenerateStartingPiecesCoordinates(Player::Up);

    for(auto pieceCoordinates : playerLowerStartingPiecesCoordinates)
    {
        Piece* piece = new Piece(pieceCoordinates, Player::Down);
        scene.addItem(piece);
    }

    for(auto pieceCoordinates : playerUpperStartingPiecesCoordinates)
    {
        Piece* piece = new Piece(pieceCoordinates, Player::Up);
        scene.addItem(piece);
    }
}
