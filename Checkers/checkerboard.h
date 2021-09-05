#pragma once

#include "piece.h"

class Checkerboard : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
    friend class CheckerboardTest;

public:
    static std::unique_ptr<Checkerboard> MakeCheckerboard();
    void createPiece(Coordinates& coordinates, Player player);
    void removeAllPieces();
    void createAllPieces();
    std::map<Coordinates, Piece*>& getPiecesPlacement() {return piecesPlacement_;}
    void markPiecesWhichCanMove(std::vector<Piece*>& pieces);

signals:
    void tileClickedSignal(const Coordinates& coordinates, bool playable);

private:
    Checkerboard();
    void createTiles();

    const int boardPositionX_ = 0;
    const int boardPositionY_ = 0;
    const int boardSize_ = 640;
    const int boardOutlineWidth_ = 10;
    const QColor boardOutlineColor_ {150, 100, 40};
    std::map<Coordinates, Piece*> piecesPlacement_;
};
