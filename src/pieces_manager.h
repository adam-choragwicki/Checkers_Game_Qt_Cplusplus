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
    explicit PiecesManager() //const std::set<Coordinates>& standardPelletPositions) : AbstractPelletsManager(standardPelletPositions)
    {
        createPieces();

        qDebug() << "Created" << pieces_.size() << "pieces";


        // const auto& ref = pieces_.emplace_back(std::make_unique<Piece>(coordinates, player));
        //pieces_.emplace_back(std::make_unique<Piece>(Coordinates{0, 0}, Player::LOWER));

        // pieces_.emplace_back(Coordinates{0, 0}, Player::LOWER);

        // for (const auto& coordinates: pelletPositions)
        // {
        //     pellets_.emplace_back(coordinates);
        // }
    }

    void reset() // override
    {
        // AbstractPelletsManager::reset();

        // emit resetRequested();
    }

    // const std::vector<Piece>& getPieces() const
    // {
    //     return pieces_;
    // }
    //
    // std::vector<Piece>& getPieces()
    // {
    //     return pieces_;
    // }

    const std::vector<std::unique_ptr<Piece>>& getPieces() const
    {
        return pieces_;
    }

    std::vector<std::unique_ptr<Piece>>& getPieces()
    {
        return pieces_;
    }

    // [[nodiscard]] int getAliveStandardPelletsCount() const
    // {
    //     return static_cast<int>(std::ranges::count_if(getPieces(),
    //                                                   [](const Piece& piece)
    //                                                   {
    //                                                       return piece.isAlive();
    //                                                   }));
    // }

    [[nodiscard]] int getAliveStandardPelletsCount() const
    {
        return static_cast<int>(std::ranges::count_if(getPieces(),
                                                      [](const std::unique_ptr<Piece>& piece)
                                                      {
                                                          return piece->isAlive();
                                                      }));
    }


    void createPieces();
    void createPiece(const Coordinates& coordinates, Player player);

    [[nodiscard]] bool isPieceAtCoordinates(const Coordinates& coordinates) const;
    [[nodiscard]] Piece& getPieceAtCoordinates(const Coordinates& coordinates) const;
    void markPiecesWhichCanMove(const std::vector<Piece*>& pieces);
    void removePieceAtCoordinates(const Coordinates& coordinates);
    [[nodiscard]] size_t countPlayerPieces(Player player) const;
    [[nodiscard]] bool didAnyPlayerRunOutOfPieces() const;
    [[nodiscard]] Player getPlayerWithNoPiecesLeft() const;

private:
    std::vector<std::unique_ptr<Piece>> pieces_;
    // std::vector<std::unique_ptr<PieceModel>> piecesModels_;

    // std::vector<Piece> pieces_;
};
