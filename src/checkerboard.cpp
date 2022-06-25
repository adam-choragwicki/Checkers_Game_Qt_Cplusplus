#include "checkerboard.h"
#include "starting_coordinates_generator.h"
#include "log_manager.h"
#include "drawer.h"

#include <QPen>

Checkerboard::Checkerboard()
{
    QGraphicsRectItem::setRect(boardPositionX_, boardPositionY_, boardSize_, boardSize_);
    setPen(QPen(boardOutlineColor_, boardOutlineWidth_));

    Drawer::drawItem(this);

    /*Tiles are child items of Checkerboard item*/
    /*PiecesPlacement and tiles are only created once, pieces are recreated during every game restart*/
    createTiles();
}

Checkerboard::~Checkerboard()
{
    Drawer::eraseItem(this);
}

void Checkerboard::createTiles()
{
    QVector<Coordinates> playableTilesCoordinates = StartingCoordinatesGenerator::generatePlayableTilesCoordinates();

    for(int row = 1; row <= 8; row++)
    {
        for(int column = 1; column <= 8; column++)
        {
            const Coordinates tileCoordinates(row, column);
            bool playable = playableTilesCoordinates.contains(tileCoordinates);

            Tile* tile = new Tile(tileCoordinates, playable, this);

            if(playable)
            {
                playableTiles_.append(tile);
            }
        }
    }
}
