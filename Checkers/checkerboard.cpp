#include "checkerboard.h"
#include "logic.h"
#include "tile.h"
#include <QPen>
#include <QGraphicsScene>
#include <QDebug>

std::map<std::pair<int, int>, Piece*> Checkerboard::m_PiecesPlacement;

Checkerboard::Checkerboard(QGraphicsScene& scene)
{
    QGraphicsRectItem::setRect(BOARD_POSITION_X, BOARD_POSITION_Y, BOARD_SIZE, BOARD_SIZE);
    setPen(QPen(BOARD_OUTLINE_COLOR, BOARD_OUTLINE_WIDTH));

    CreateTiles(scene);
    CreatePieces(scene);
}

void Checkerboard::CreateTiles(QGraphicsScene& scene)
{
    for(int row = 1; row <= 8; row++)
    {
        for(int column = 1; column <= 8; column++)
        {
            Tile* tile = new Tile(row, column);
            m_PiecesPlacement[std::pair(row, column)] = nullptr;
            scene.addItem(tile);
        }
    }
}

void Checkerboard::CreatePieces(QGraphicsScene& scene)
{
    std::vector<std::pair<int, int>> playerLowerStartingPiecesCoordinates = Logic::GenerateStartingPiecesCoordinates(Player::Down);
    std::vector<std::pair<int, int>> playerUpperStartingPiecesCoordinates = Logic::GenerateStartingPiecesCoordinates(Player::Up);

    for(auto pieceCoordinates : playerLowerStartingPiecesCoordinates)
    {
        Piece* piece = new Piece(pieceCoordinates, Player::Down);
        m_PiecesPlacement[std::pair(pieceCoordinates.first, pieceCoordinates.second)] = piece;
        scene.addItem(piece);
    }

    for(auto pieceCoordinates : playerUpperStartingPiecesCoordinates)
    {
        Piece* piece = new Piece(pieceCoordinates, Player::Up);
        m_PiecesPlacement[std::pair(pieceCoordinates.first, pieceCoordinates.second)] = piece;
        scene.addItem(piece);
    }
}

void Checkerboard::ProcessTileClicked(const int row, const int column, bool tileIsPlayable)
{
    if(tileIsPlayable)
    {
        if(m_PiecesPlacement.at(std::pair(row, column)) == nullptr)
        {
            qDebug("Clicked tile (%d,%d) is PLAYABLE and EMPTY", row, column);
        }
        else
        {
            qDebug("Clicked tile (%d,%d) is PLAYABLE and THERE IS PIECE ON IT", row, column);
        }
    }
    else
    {
        assert(m_PiecesPlacement.at(std::pair(row, column)) == nullptr);
        qDebug("Clicked tile (%d,%d)", row, column);
    }

    Piece* activePiece = Piece::GetActivePiece();

    if(activePiece && tileIsPlayable)
    {
        MovePiece(activePiece, row, column);
    }
}

void Checkerboard::MovePiece(Piece* activePiece, const int row, const int column)
{
    qDebug("Active piece=(%d,%d)", activePiece->GetRow(), activePiece->GetColumn());
    qDebug("Destination tile=(%d,%d)", row, column);

    if(m_PiecesPlacement.at(std::pair(row, column)) == nullptr)
    {
        m_PiecesPlacement[std::pair(activePiece->GetRow(), activePiece->GetColumn())] = nullptr;
        m_PiecesPlacement[std::pair(row, column)] = activePiece;
        activePiece->MoveToTile(row, column);
    }
    else
    {
        qDebug("Destination tile is not empty!");
    }
}
