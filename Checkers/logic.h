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
    static std::vector<Coordinates> GeneratePlayableTilesCoordinates();
    static std::vector<Coordinates> GenerateStartingPiecesCoordinates(Player player);
    static std::vector<Piece*> WhichPiecesCanMove(Player activePlayer, const std::map<Coordinates, Piece*>& piecesPlacement);
    static std::vector<Piece*> WhichPiecesCanCapture(Player activePlayer, const std::map<Coordinates, Piece*>& piecesPlacement);
    static bool CheckIfPieceCanMove(const Piece* piece, const std::map<Coordinates, Piece *>& piecesPlacement);
    static bool CheckMovePossibility(const Piece* piece, const std::map<Coordinates, Piece*>& piecesPlacement, const Coordinates& targetTileCoordinates);
    static bool CheckCapturePossibility(const Piece* piece, const std::map<Coordinates, Piece*>& piecesPlacement, const Coordinates& targetTileCoordinates);
    static bool CheckIfPieceCanCapture(const Piece* piece, const std::map<Coordinates, Piece*>& piecesPlacement);
    static bool CheckPromotionEligibility(const Piece* piece);

protected:
    static std::vector<Coordinates> GeneratePossiblePieceMovementOptionsCoordinates(const Piece* piece);
    static std::vector<Coordinates> GeneratePossiblePieceCaptureOptionsCoordinates(const Piece* piece);
    static bool IsTileEmpty(const Coordinates &coordinates, const std::map<Coordinates, Piece *> &piecesPlacement);
};
