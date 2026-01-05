#pragma once

#include "piece.h"
#include <vector>
#include <QDebug>

class PieceStateManager;

class PiecesManager : public QObject
{
    Q_OBJECT

public:
    explicit PiecesManager(PieceStateManager& pieceStateManager);

    void reset();

    void enablePiecesAnimations();
    void disablePiecesAnimations();

    [[nodiscard]] const std::vector<std::unique_ptr<Piece>>& getPieces() const { return pieces_; }
    std::vector<std::unique_ptr<Piece>>& getPieces() { return pieces_; }

    void disableAllPieces();
    void disableAllButOnePiece(const Piece& pieceToOmit);

    [[nodiscard]] Piece* findPieceById(int id) const;

    void createPieces();
    void createPiece(const Coordinates& coordinates, const Player& player);

    [[nodiscard]] bool isPieceAtCoordinates(const Coordinates& coordinates) const;
    [[nodiscard]] Piece& getPieceAtCoordinates(const Coordinates& coordinates) const;
    void markPiecesWhichCanMove(const std::vector<Piece*>& pieces);
    void killPiece(Piece& piece);
    [[nodiscard]] size_t countPlayerPieces(const Player& player) const;
    [[nodiscard]] bool didAnyPlayerRunOutOfPieces() const;
    [[nodiscard]] const Player& getPlayerWithNoPiecesLeft() const;

private:
    [[maybe_unused]] void loadVisualTestScenario();

    PieceStateManager& pieceStateManager_;
    std::vector<std::unique_ptr<Piece>> pieces_;
};
