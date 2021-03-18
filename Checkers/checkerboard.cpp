#include "checkerboard.h"
#include "logic.h"
#include "tile.h"
#include <QPen>
#include <QGraphicsScene>
#include <QDebug>
#include <memory>

bool operator<(const Coordinates& coordinates1, const Coordinates& coordinates2);

std::map<Coordinates, Piece*> Checkerboard::m_PiecesPlacement;

Checkerboard::Checkerboard(QGraphicsScene& scene)
{
    QGraphicsRectItem::setRect(BOARD_POSITION_X, BOARD_POSITION_Y, BOARD_SIZE, BOARD_SIZE);
    setPen(QPen(BOARD_OUTLINE_COLOR, BOARD_OUTLINE_WIDTH));

    CreateTiles(scene);
    CreatePieces(scene);
    WhichPiecesCanMove();
}

void Checkerboard::CreateTiles(QGraphicsScene& scene)
{
    assert(m_PiecesPlacement.size() == 0);

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
        if(CheckCapturePossibility(activePiece, targetRow, targetColumn))
        {
            CapturePiece(activePiece, targetRow, targetColumn);
        }
        else if(CheckMovePossibility(activePiece, targetRow, targetColumn))
        {
            MovePiece(activePiece, targetRow, targetColumn);
        }
    }

    WhichPiecesCanMove();
}

bool Checkerboard::CheckMovePossibility(Piece* piece, const int targetRow, const int targetColumn)
{
    qDebug("Piece is on tile=(%d,%d)", piece->Row(), piece->Column());
    qDebug("Destination tile=(%d,%d)", targetRow, targetColumn);

    Player piecePlayer = piece->GetPlayer();

    Piece* pieceOnTargetTile = m_PiecesPlacement.at(Coordinates(targetRow, targetColumn));

    //If target tile is empty
    if(pieceOnTargetTile == nullptr)
    {
        if(piecePlayer == Player::Down)
        {
            //Movement up is permitted
            if((targetRow == piece->Row() - 1) && ((targetColumn == piece->Column() - 1) || (targetColumn == piece->Column() + 1)))
            {
                return true;
            }
            else
            {
                qDebug("Move not permitted");
                return false;
            }
        }
        else if(piecePlayer == Player::Up)
        {
            //Movement down is permitted
            if(targetRow == piece->Row() + 1 && ((targetColumn == piece->Column() - 1) || (targetColumn == piece->Column() + 1)))
            {
                return true;
            }
            else
            {
                qDebug("Move not permitted");
                return false;
            }
        }
        else
        {
            assert(false);
        }

        return true;
    }
    else
    {
        qDebug("Destination tile is not empty!");
        return false;
    }
}

void Checkerboard::MovePiece(Piece* piece, const int targetRow, const int targetColumn)
{
    m_PiecesPlacement[Coordinates(piece->Row(), piece->Column())] = nullptr;
    m_PiecesPlacement[Coordinates(targetRow, targetColumn)] = piece;
    piece->MoveToTile(targetRow, targetColumn);
}

bool Checkerboard::CheckCapturePossibility(Piece* piece, const int targetRow, const int targetColumn)
{
    Player piecePlayer = piece->GetPlayer();

    Piece* pieceOnTargetTile = m_PiecesPlacement.at(Coordinates(targetRow, targetColumn));

    //If target tile is empty
    if(pieceOnTargetTile == nullptr)
    {
        if(piecePlayer == Player::Down)
        {
            //Movement up is permitted
            if(targetRow == piece->Row() - 2)
            {
                if(targetColumn == piece->Column() - 2)
                {
                    Piece* pieceBetweenThisPieceAndTargetTile = m_PiecesPlacement.at(Coordinates(piece->Row() - 1, piece->Column() - 1));

                    if(pieceBetweenThisPieceAndTargetTile)
                    {
                        if(pieceBetweenThisPieceAndTargetTile->GetPlayer() == Player::Up)
                        {
                            qDebug("Capture is possible");
                            return true;
                        }
                        else
                        {
                            qDebug("Cannot capture over your own piece");
                            return false;
                        }
                    }
                    else
                    {
                        qDebug("Tile between is empty, capture impossible");
                        return false;
                    }
                }
                else if(targetColumn == piece->Column() + 2)
                {
                    Piece* pieceBetweenThisPieceAndTargetTile = m_PiecesPlacement.at(Coordinates(piece->Row() - 1, piece->Column() + 1));

                    if(pieceBetweenThisPieceAndTargetTile)
                    {
                        if(pieceBetweenThisPieceAndTargetTile->GetPlayer() == Player::Up)
                        {
                            qDebug("Capture is possible");
                            return true;
                        }
                        else
                        {
                            qDebug("Cannot capture over your own piece");
                            return false;
                        }
                    }
                    else
                    {
                        qDebug("Tile between is empty, capture impossible");
                        return false;
                    }
                }
                else
                {
                    qDebug("Capture target is not 2 columns away");
                    return false;
                }
            }
            else
            {
                qDebug("Capture target is not 2 rows away");
                return false;
            }
        }
        else if(piecePlayer == Player::Up)
        {
            //Movement down is permitted
            if(targetRow == piece->Row() + 2)
            {
                if(targetColumn == piece->Column() - 2)
                {
                    Piece* pieceBetweenThisPieceAndTargetTile = m_PiecesPlacement.at(Coordinates(piece->Row() + 1, piece->Column() - 1));

                    if(pieceBetweenThisPieceAndTargetTile)
                    {
                        if(pieceBetweenThisPieceAndTargetTile->GetPlayer() == Player::Down)
                        {
                            qDebug("Capture is possible");
                            return true;
                        }
                        else
                        {
                            qDebug("Cannot capture over your own piece");
                            return false;
                        }
                    }
                    else
                    {
                        qDebug("Tile between is empty, capture impossible");
                        return false;
                    }
                }
                else if(targetColumn == piece->Column() + 2)
                {
                    Piece* pieceBetweenThisPieceAndTargetTile = m_PiecesPlacement.at(Coordinates(piece->Row() + 1, piece->Column() + 1));

                    if(pieceBetweenThisPieceAndTargetTile)
                    {
                        if(pieceBetweenThisPieceAndTargetTile->GetPlayer() == Player::Down)
                        {
                            qDebug("Capture is possible");
                            return true;
                        }
                        else
                        {
                            qDebug("Cannot capture over your own piece");
                            return false;
                        }
                    }
                    else
                    {
                        qDebug("Tile between is empty, capture impossible");
                        return false;
                    }
                }
                else
                {
                    qDebug("Capture target is not 2 columns away");
                    return false;
                }
            }
            else
            {
                qDebug("Capture target is not 2 rows away");
                return false;
            }
        }
        else
        {
            assert(false);
            return false;
        }
    }
    else
    {
        qDebug("Destination tile is not empty!");
        return false;
    }
}

void Checkerboard::CapturePiece(Piece* piece, const int targetRow, const int targetColumn)
{
    qDebug("Capture executed!");
    Coordinates pieceBetween((targetRow + piece->Row()) / 2, (targetColumn + piece->Column()) / 2);
    delete m_PiecesPlacement.at(pieceBetween);
    m_PiecesPlacement[pieceBetween] = nullptr;
    MovePiece(piece, targetRow, targetColumn);
}

void Checkerboard::WhichPiecesCanMove()
{
    for(auto piece: m_PiecesPlacement)
    {
        if(piece.second != nullptr)
        {
            Player piecePlayer = piece.second->GetPlayer();

            if(piecePlayer == Player::Down)
            {
                //Movement up is permitted
                Coordinates pieceCoordinates(piece.second->Row(), piece.second->Column());

                std::unique_ptr<Coordinates> moveOption1;
                std::unique_ptr<Coordinates> moveOption2;

                try {
                    moveOption1 = std::make_unique<Coordinates>(pieceCoordinates.Row() - 1, pieceCoordinates.Column() - 1);
                }
                catch(std::out_of_range exception) {
                    moveOption1 = nullptr;
                }

                try {
                    moveOption2 = std::make_unique<Coordinates>(pieceCoordinates.Row() - 1, pieceCoordinates.Column() + 1);
                }  catch(std::out_of_range exception) {
                    moveOption2 = nullptr;
                }

                if(moveOption1)
                {
                    if(m_PiecesPlacement.at(*moveOption1) == nullptr)
                    {
                        MarkPiece(piece.second);
                    }
                }

                if(moveOption2)
                {
                    if(m_PiecesPlacement.at(*moveOption2) == nullptr)
                    {
                        MarkPiece(piece.second);
                    }
                }
            }
            else if(piecePlayer == Player::Up)
            {
                //Movement down is permitted
                Coordinates pieceCoordinates(piece.second->Row(), piece.second->Column());

                std::unique_ptr<Coordinates> moveOption1;
                std::unique_ptr<Coordinates> moveOption2;

                try {
                    moveOption1 = std::make_unique<Coordinates>(pieceCoordinates.Row() + 1, pieceCoordinates.Column() - 1);
                }
                catch(std::out_of_range exception) {
                    moveOption1 = nullptr;
                }

                try {
                    moveOption2 = std::make_unique<Coordinates>(pieceCoordinates.Row() + 1, pieceCoordinates.Column() + 1);
                }  catch(std::out_of_range exception) {
                    moveOption2 = nullptr;
                }

                if(moveOption1)
                {
                    if(m_PiecesPlacement.at(*moveOption1) == nullptr)
                    {
                        MarkPiece(piece.second);
                    }
                }

                if(moveOption2)
                {
                    if(m_PiecesPlacement.at(*moveOption2) == nullptr)
                    {
                        MarkPiece(piece.second);
                    }
                }
            }

            qDebug("Piece=(%d,%d)", piece.second->Row(), piece.second->Column());
        }
    }
}

void Checkerboard::MarkPiece(Piece* piece)
{
    piece->Mark();
}
