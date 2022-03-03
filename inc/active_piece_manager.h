#pragma once

#include "piece.h"

class ActivePieceManager
{
public:
    ActivePieceManager() = delete;
    ActivePieceManager(const ActivePieceManager&) = delete;
    ActivePieceManager& operator=(ActivePieceManager&) = delete;
    ActivePieceManager(const ActivePieceManager&&) = delete;
    ActivePieceManager& operator=(ActivePieceManager&&) = delete;

    static Piece* getActivePiece() {return activePiece_;}
    static void setActivePiece(Piece* piece) {activePiece_ = piece;}
    static void resetActivePiece() {activePiece_ = nullptr;}

private:
    inline static Piece* activePiece_ = nullptr;
};
