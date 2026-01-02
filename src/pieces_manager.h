#pragma once

#include "piece.h"
#include <vector>
#include <QDebug>

class PiecesManager : public QObject
{
    Q_OBJECT

public:
    explicit PiecesManager();

    void reset();

    void enablePiecesAnimations();
    void disablePiecesAnimations();

    [[nodiscard]] const std::vector<std::unique_ptr<Piece>>& getPieces() const {return pieces_;}
    std::vector<std::unique_ptr<Piece>>& getPieces(){return pieces_;}

    void disableAllPieces();

    [[nodiscard]] Piece* findPieceById(int id) const;

    void createPieces();
    void createPiece(const Coordinates& coordinates, Player player);

    [[nodiscard]] bool isPieceAtCoordinates(const Coordinates& coordinates) const;
    [[nodiscard]] Piece& getPieceAtCoordinates(const Coordinates& coordinates) const;
    void markPiecesWhichCanMove(const std::vector<Piece*>& pieces);
    void killPieceAtCoordinates(const Coordinates& coordinates);
    [[nodiscard]] size_t countPlayerPieces(Player player) const;
    [[nodiscard]] bool didAnyPlayerRunOutOfPieces() const;
    [[nodiscard]] Player getPlayerWithNoPiecesLeft() const;

private:
    std::vector<std::unique_ptr<Piece>> pieces_;
};
