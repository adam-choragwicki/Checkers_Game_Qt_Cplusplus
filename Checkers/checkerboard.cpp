#include "checkerboard.h"
#include "logic.h"
#include "tile.h"
#include <QPen>
#include <QGraphicsScene>
#include <QDebug>

std::map<Coordinates, Piece*> Checkerboard::m_PiecesPlacement;

Checkerboard::Checkerboard(QGraphicsScene& scene)
{
    QGraphicsRectItem::setRect(BOARD_POSITION_X, BOARD_POSITION_Y, BOARD_SIZE, BOARD_SIZE);
    setPen(QPen(BOARD_OUTLINE_COLOR, BOARD_OUTLINE_WIDTH));

    CreateTiles(scene);
    CreatePieces(scene);

    std::vector<Piece*> piecesWhichCanMove = Logic::WhichPiecesCanMove(m_PiecesPlacement);
    MarkPieces(piecesWhichCanMove);
}

void Checkerboard::CreateTiles(QGraphicsScene& scene)
{
    for(int row = 1; row <= 8; row++)
    {
        for(int column = 1; column <= 8; column++)
        {
            Tile* tile = new Tile(row, column);
            m_PiecesPlacement[Coordinates(row, column)] = nullptr;
            scene.addItem(tile);
        }
    }

    assert(m_PiecesPlacement.size() == 64);
}

void Checkerboard::CreatePieces(QGraphicsScene& scene)
{
    std::vector<Coordinates> playerLowerStartingPiecesCoordinates = Logic::GenerateStartingPiecesCoordinates(Player::Down);
    std::vector<Coordinates> playerUpperStartingPiecesCoordinates = Logic::GenerateStartingPiecesCoordinates(Player::Up);

    for(auto pieceCoordinates : playerLowerStartingPiecesCoordinates)
    {
        Piece* piece = new Piece(pieceCoordinates, Player::Down);
        m_PiecesPlacement[Coordinates(pieceCoordinates.Row(), pieceCoordinates.Column())] = piece;
        scene.addItem(piece);
    }

    for(auto pieceCoordinates : playerUpperStartingPiecesCoordinates)
    {
        Piece* piece = new Piece(pieceCoordinates, Player::Up);
        m_PiecesPlacement[Coordinates(pieceCoordinates.Row(), pieceCoordinates.Column())] = piece;
        scene.addItem(piece);
    }
}

void Checkerboard::ProcessTileClicked(const int targetRow, const int targetColumn, bool tileIsPlayable)
{
    if(tileIsPlayable)
    {
        if(m_PiecesPlacement.at(Coordinates(targetRow, targetColumn)) == nullptr)
        {
            qDebug("Clicked tile (%d,%d) is PLAYABLE and EMPTY", targetRow, targetColumn);
        }
        else
        {
            qDebug("Clicked tile (%d,%d) is PLAYABLE and THERE IS PIECE ON IT", targetRow, targetColumn);
        }
    }
    else
    {
        assert(m_PiecesPlacement.at(Coordinates(targetRow, targetColumn)) == nullptr);
        qDebug("Clicked tile (%d,%d)", targetRow, targetColumn);
    }

    Piece* activePiece = Piece::GetActivePiece();

    if(activePiece && tileIsPlayable)
    {
        if(Logic::CheckCapturePossibility(activePiece, m_PiecesPlacement, targetRow, targetColumn))
        {
            CapturePiece(activePiece, targetRow, targetColumn);
        }
        else if(Logic::CheckMovePossibility(activePiece, m_PiecesPlacement, targetRow, targetColumn))
        {
            MovePiece(activePiece, targetRow, targetColumn);
        }
    }

    UnmarkAllPieces();

    std::vector<Piece*> piecesWhichCanCapture = Logic::WhichPiecesCanCapture(m_PiecesPlacement);

    if(piecesWhichCanCapture.size() == 0)
    {
        std::vector<Piece*> piecesWhichCanMove = Logic::WhichPiecesCanMove(m_PiecesPlacement);
        MarkPieces(piecesWhichCanMove);
    }
    else
    {
        MarkPieces(piecesWhichCanCapture);
    }
}

void Checkerboard::MarkPieces(std::vector<Piece*>& pieces)
{
    for(auto piece : pieces)
    {
        piece->Mark();
    }
}

void Checkerboard::UnmarkAllPieces()
{
    for(auto piecePlacement : m_PiecesPlacement)
    {
        if(piecePlacement.second != nullptr)
        {
            piecePlacement.second->Unmark();
        }
    }
}

void Checkerboard::MovePiece(Piece* piece, const int targetRow, const int targetColumn)
{
    m_PiecesPlacement[Coordinates(piece->Row(), piece->Column())] = nullptr;
    m_PiecesPlacement[Coordinates(targetRow, targetColumn)] = piece;
    piece->MoveToTile(targetRow, targetColumn);
}

void Checkerboard::CapturePiece(Piece* piece, const int targetRow, const int targetColumn)
{
    qDebug("Capture executed!");
    Coordinates pieceBetween((targetRow + piece->Row()) / 2, (targetColumn + piece->Column()) / 2);
    delete m_PiecesPlacement.at(pieceBetween);
    m_PiecesPlacement[pieceBetween] = nullptr;
    MovePiece(piece, targetRow, targetColumn);
}
