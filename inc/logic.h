#pragma once

#include "common.h"
#include "coordinates.h"
#include "piece.h"

#include <vector>

namespace logic
{
    std::vector<Coordinates> generatePlayableTilesCoordinates();
    std::vector<Coordinates> generateStartingPiecesCoordinates(Player player);
    std::vector<Piece*> whichPiecesCanMove(Player activePlayer, const std::map<Coordinates, Piece*>& piecesPlacement);
    std::vector<Piece*> whichPiecesCanCapture(Player activePlayer, const std::map<Coordinates, Piece*>& piecesPlacement);
    bool checkIfPieceCanMove(const Piece* piece, const std::map<Coordinates, Piece*>& piecesPlacement);
    bool checkMovePossibility(const Piece* piece, const std::map<Coordinates, Piece*>& piecesPlacement, const Coordinates& targetTileCoordinates);
    bool checkCapturePossibility(const Piece* piece, const std::map<Coordinates, Piece*>& piecesPlacement, const Coordinates& targetTileCoordinates);
    bool checkIfPieceCanCapture(const Piece* piece, const std::map<Coordinates, Piece*>& piecesPlacement);
    bool checkPromotionEligibility(const Piece* piece);
    std::vector<Coordinates> generatePossiblePieceMovementOptionsCoordinates(const Piece* piece);
    std::vector<Coordinates> generatePossiblePieceCaptureOptionsCoordinates(const Piece* piece);
    bool isTileEmpty(const Coordinates &coordinates, const std::map<Coordinates, Piece*> &piecesPlacement);
};
