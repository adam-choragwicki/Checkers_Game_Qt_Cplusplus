#include "checkerboard.h"
#include "logic.h"
#include "tile.h"
#include <QPen>
#include <QGraphicsScene>
#include <QDebug>

bool operator<(const Coordinates& coordinates1, const Coordinates& coordinates2);

std::map<Coordinates, Piece*> Checkerboard::m_PiecesPlacement;

Checkerboard::Checkerboard(QGraphicsScene& scene)
{
    QGraphicsRectItem::setRect(BOARD_POSITION_X, BOARD_POSITION_Y, BOARD_SIZE, BOARD_SIZE);
    setPen(QPen(BOARD_OUTLINE_COLOR, BOARD_OUTLINE_WIDTH));

    CreateTiles(scene);
    CreatePieces(scene);
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
        if(CheckCapture(activePiece, targetRow, targetColumn))
        {
            Capture(activePiece, targetRow, targetColumn);
        }
        else
        {
            MovePiece(activePiece, targetRow, targetColumn);
        }
    }
}

void Checkerboard::MovePiece(Piece* activePiece, const int targetRow, const int targetColumn)
{
    qDebug("Active piece is on tile=(%d,%d)", activePiece->Row(), activePiece->Column());
    qDebug("Destination tile=(%d,%d)", targetRow, targetColumn);

    Player activePiecePlayer = activePiece->GetPlayer();

    Piece* pieceOnTargetTile = m_PiecesPlacement.at(Coordinates(targetRow, targetColumn));

    //If target tile is empty
    if(pieceOnTargetTile == nullptr)
    {
        if(activePiecePlayer == Player::Down)
        {
            //Movement up is permitted
            if((targetRow == activePiece->Row() - 1) && ((targetColumn == activePiece->Column() - 1) || (targetColumn == activePiece->Column() + 1)))
            {

            }
            else
            {
                qDebug("Move not permitted");
                return;
            }
        }
        else if(activePiecePlayer == Player::Up)
        {
            //Movement down is permitted
            if(targetRow == activePiece->Row() + 1 && ((targetColumn == activePiece->Column() - 1) || (targetColumn == activePiece->Column() + 1)))
            {

            }
            else
            {
                qDebug("Move not permitted");
                return;
            }
        }
        else
        {
            assert(false);
        }

        m_PiecesPlacement[Coordinates(activePiece->Row(), activePiece->Column())] = nullptr;
        m_PiecesPlacement[Coordinates(targetRow, targetColumn)] = activePiece;
        activePiece->MoveToTile(targetRow, targetColumn);
    }
    else
    {
        qDebug("Destination tile is not empty!");
    }
}

bool Checkerboard::CheckCapture(Piece *activePiece, const int targetRow, const int targetColumn)
{
    Player activePiecePlayer = activePiece->GetPlayer();

    Piece* pieceOnTargetTile = m_PiecesPlacement.at(Coordinates(targetRow, targetColumn));

    //If target tile is empty
    if(pieceOnTargetTile == nullptr)
    {
        if(activePiecePlayer == Player::Down)
        {
            //Movement up is permitted
            if(targetRow == activePiece->Row() - 2)
            {
                if(targetColumn == activePiece->Column() - 2)
                {
                    Piece* pieceBetweenActivePieceAndTargetTile = m_PiecesPlacement.at(Coordinates(activePiece->Row() - 1, activePiece->Column() - 1));

                    if(pieceBetweenActivePieceAndTargetTile)
                    {
                        if(pieceBetweenActivePieceAndTargetTile->GetPlayer() == Player::Up)
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
                else if(targetColumn == activePiece->Column() + 2)
                {
                    Piece* pieceBetweenActivePieceAndTargetTile = m_PiecesPlacement.at(Coordinates(activePiece->Row() - 1, activePiece->Column() + 1));

                    if(pieceBetweenActivePieceAndTargetTile)
                    {
                        if(pieceBetweenActivePieceAndTargetTile->GetPlayer() == Player::Up)
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
        else if(activePiecePlayer == Player::Up)
        {
            //Movement down is permitted
            if(targetRow == activePiece->Row() + 2)
            {
                if(targetColumn == activePiece->Column() - 2)
                {
                    Piece* pieceBetweenActivePieceAndTargetTile = m_PiecesPlacement.at(Coordinates(activePiece->Row() + 1, activePiece->Column() - 1));

                    if(pieceBetweenActivePieceAndTargetTile)
                    {
                        if(pieceBetweenActivePieceAndTargetTile->GetPlayer() == Player::Down)
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
                else if(targetColumn == activePiece->Column() + 2)
                {
                    Piece* pieceBetweenActivePieceAndTargetTile = m_PiecesPlacement.at(Coordinates(activePiece->Row() + 1, activePiece->Column() + 1));

                    if(pieceBetweenActivePieceAndTargetTile)
                    {
                        if(pieceBetweenActivePieceAndTargetTile->GetPlayer() == Player::Down)
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

void Checkerboard::Capture(Piece *activePiece, const int row, const int column)
{
    qDebug("Capture executed!");
}
