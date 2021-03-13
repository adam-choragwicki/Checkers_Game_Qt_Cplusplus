#include "board.h"
#include "piece.h"
#include "logic.h"
#include "tile.h"
#include <QPen>
#include <QGraphicsScene>
#include <QDebug>

Board::Board(QGraphicsScene& scene)
{
    QGraphicsRectItem::setRect(BOARD_POSITION_X, BOARD_POSITION_Y, BOARD_SIZE, BOARD_SIZE);
    setPen(QPen(BOARD_OUTLINE_COLOR, BOARD_OUTLINE_WIDTH));

    CreateTiles(scene);
    CreatePieces(scene);
}

void Board::CreateTiles(QGraphicsScene& scene)
{
    for(int row = 1; row <= 8; row++)
    {
        for(int column = 1; column <= 8; column++)
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

void Board::ProcessTileClicked(int row, int column, bool tileIsPlayable)
{
    if(tileIsPlayable)
    {
        qDebug("Clicked tile (%d,%d)->PLAYABLE", row, column);
    }
    else
    {
        qDebug("Clicked tile (%d,%d)", row, column);
    }

    Piece* pieceCurrentlyChosen = Piece::GetCurrentlyChosenPiece();

    if(pieceCurrentlyChosen && tileIsPlayable)
    {
        qDebug("Currently chosen piece=(%d,%d)", pieceCurrentlyChosen->GetRow(), pieceCurrentlyChosen->GetColumn());
        qDebug("Destination tile=(%d,%d)", row, column);

        pieceCurrentlyChosen->MoveToTile(row, column);
    }
}
