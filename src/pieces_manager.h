#pragma once

// #include "abstract_pellets_manager.h"
// #include "standard_pellet.h"
#include <algorithm>
#include "piece.h"
#include <vector>
#include <QDebug>

class PiecesManager : public QObject //, public AbstractPelletsManager<StandardPellet>
{
    Q_OBJECT

signals:
    void resetRequested();

public:
    explicit PiecesManager();

    void reset();

    // const std::vector<Piece>& getPieces() const
    // {
    //     return pieces_;
    // }
    //
    // std::vector<Piece>& getPieces()
    // {
    //     return pieces_;
    // }

    void enablePiecesAnimations();
    void disablePiecesAnimations();

    [[nodiscard]] const std::vector<std::unique_ptr<Piece>>& getPieces() const {return pieces_;}
    std::vector<std::unique_ptr<Piece>>& getPieces(){return pieces_;}

    void disableAllPieces();

    [[nodiscard]] int getAliveStandardPelletsCount() const
    {
        return static_cast<int>(std::ranges::count_if(getPieces(),
                                                      [](const std::unique_ptr<Piece>& piece)
                                                      {
                                                          return piece->isAlive();
                                                      }));
    }

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
    // std::vector<std::unique_ptr<PieceModel>> piecesModels_;

    // std::vector<Piece> pieces_;
};
