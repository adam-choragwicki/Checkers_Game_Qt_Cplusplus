#pragma once

#include "coordinates.h"
#include "player_manager.h"
#include "piece.h"
#include "piece_model.h"
#include <vector>

class PiecesPlacement
{
public:
    void createPieces();
    void createPiece(const Coordinates& coordinates, Player player);

    [[nodiscard]] const std::vector<std::unique_ptr<Piece>>& getPieces() const
    { return pieces_; }

    [[nodiscard]] bool isPieceAtCoordinates(const Coordinates& coordinates) const;
    [[nodiscard]] Piece& getPieceAtCoordinates(const Coordinates& coordinates) const;
    void markPiecesWhichCanMove(std::vector<Piece*>& pieces);
    void removePieceAtCoordinates(const Coordinates& coordinates);
    [[nodiscard]] size_t countPlayerPieces(Player player) const;
    [[nodiscard]] bool didAnyPlayerRunOutOfPieces() const;
    [[nodiscard]] Player getPlayerWithNoPiecesLeft() const;

    std::vector<std::unique_ptr<Piece>> pieces_;
    std::vector<std::unique_ptr<PieceModel>> piecesModels_;
};
