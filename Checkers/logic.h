#pragma once
#include <vector>
#include "common.h"
#include "coordinates.h"
#include "piece.h"

class Logic
{
public:
    Logic() = delete;
    Logic(const Logic&) = delete;
    static std::vector<Coordinates> GenerateAllValidGameTilesCoordinates();
    static std::vector<Coordinates> GenerateStartingPiecesCoordinates(Player player);
    static bool CheckMovePossibility(const Piece* piece, const std::map<Coordinates, Piece*>& piecesPlacement, const int targetRow, const int targetColumn);
    static bool CheckCapturePossibility(const Piece* piece, const std::map<Coordinates, Piece*>& piecesPlacement, const int targetRow, const int targetColumn);
    static std::vector<Piece*> WhichPiecesCanMove(Player activePlayer, const std::map<Coordinates, Piece*>& piecesPlacement);
    static std::vector<Piece*> WhichPiecesCanCapture(Player activePlayer, const std::map<Coordinates, Piece*>& piecesPlacement);
};
