#pragma once

#include "piece.h"
#include "common.h"

class Checkerboard : public QObject, public QGraphicsRectItem
{
Q_OBJECT

signals:
    void tileClickedSignal(const Coordinates& coordinates, bool playable);

public:
    Checkerboard();

    void createPiece(Coordinates& coordinates, Player player);
    void removeAllPieces();
    void createAllPieces();
    CoordinatesToPiecesMapping& getCoordinatesToPiecesMapping() { return coordinatesToPiecesMapping_; }
    void markPiecesWhichCanMove(std::vector<Piece*>& pieces);

private:
    void createTiles();

    const int boardPositionX_ = 0;
    const int boardPositionY_ = 0;
    const int boardSize_ = 640;
    const int boardOutlineWidth_ = 10;
    const QColor boardOutlineColor_{150, 100, 40};
    CoordinatesToPiecesMapping coordinatesToPiecesMapping_;
};
