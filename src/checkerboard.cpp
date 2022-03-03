#include "checkerboard.h"
#include "logic.h"
#include "tile.h"

#include <QPen>

Checkerboard::Checkerboard() : QGraphicsRectItem(nullptr)
{
    QGraphicsRectItem::setRect(boardPositionX_, boardPositionY_, boardSize_, boardSize_);
    setPen(QPen(boardOutlineColor_, boardOutlineWidth_));

    /*Checkerboard and tiles are only created once, pieces are recreated during every game restart*/
    createTiles();
}

void Checkerboard::createTiles()
{
    std::vector<Coordinates> playableTilesCoordinates = logic::generatePlayableTilesCoordinates();

    for(int row = 1; row <= 8; row++)
    {
        for(int column = 1; column <= 8; column++)
        {
            const Coordinates tileCoordinates(row, column);
            bool playable = false;

            /*Check if the tile is playable*/
            if(std::find(playableTilesCoordinates.cbegin(), playableTilesCoordinates.cend(), tileCoordinates) != playableTilesCoordinates.cend())
            {
                playable = true;
                piecesPlacement_[tileCoordinates] = nullptr;
            }

            Tile* tile = new Tile(tileCoordinates, playable, this);

            if(playable)
            {
                QObject::connect(tile, &Tile::clickedSignal, this, &Checkerboard::tileClickedSignal);
            }
        }
    }
}

void Checkerboard::createPiece(Coordinates &coordinates, Player player)
{
    auto* piece = new Piece(coordinates, player, this);
    piecesPlacement_[Coordinates(coordinates.getRow(), coordinates.getColumn())] = piece;
}

void Checkerboard::createAllPieces()
{
    std::vector<Coordinates> playerLowerStartingPiecesCoordinates = logic::generateStartingPiecesCoordinates(Player::down);
    std::vector<Coordinates> playerUpperStartingPiecesCoordinates = logic::generateStartingPiecesCoordinates(Player::up);

    for(auto& pieceCoordinates : playerLowerStartingPiecesCoordinates)
    {
        createPiece(pieceCoordinates, Player::down);
    }

    for(auto& pieceCoordinates : playerUpperStartingPiecesCoordinates)
    {
        createPiece(pieceCoordinates, Player::up);
    }
}

void Checkerboard::removeAllPieces()
{
    for(auto& piecePlacement : piecesPlacement_)
    {
        if(piecePlacement.second)
        {
            delete piecePlacement.second;
            piecePlacement.second = nullptr;
        }
    }
}

void Checkerboard::markPiecesWhichCanMove(std::vector<Piece*>& pieces)
{
    for(auto& piece : pieces)
    {
        piece->markValidMoveAvailable();
    }
}
