#pragma once

#include "common.h"
#include "coordinates.h"

class PiecesPlacement
{
public:
    PiecesPlacement() = default;
    ~PiecesPlacement();

    void createPiece(const Coordinates& coordinates, Player player);
    void createAllPieces();

    [[nodiscard]] const QVector<Piece*>& getPieces() const
    { return pieces_; }

    [[nodiscard]] bool isPieceAtCoordinates(const Coordinates& coordinates) const;
    [[nodiscard]] Piece* getPieceAtCoordinates(const Coordinates& coordinates) const;
    void markPiecesWhichCanMove(QVector<Piece*>& pieces);
    void removePiece(Piece* piece);
    void removePieceAtCoordinates(const Coordinates& coordinates);
    [[nodiscard]] int countPlayerPieces(Player player) const;
    [[nodiscard]] bool didAnyPlayerRunOutOfPieces() const;
    [[nodiscard]] Player getPlayerWithNoPiecesLeft() const;

    QVector<Piece*> pieces_;
};
