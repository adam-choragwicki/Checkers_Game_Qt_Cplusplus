#pragma once

#include "common.h"
#include "coordinates.h"
#include "piece.h"

#include <vector>

namespace logic
{
    std::vector<Coordinates> generatePlayableTilesCoordinates();
    std::vector<Coordinates> generateStartingPiecesCoordinates(Player player);
    std::vector<Piece*> whichPiecesCanMove(Player activePlayer, const CoordinatesToPiecesMapping& coordinatesToPiecesMapping);
    std::vector<Piece*> whichPiecesCanCapture(Player activePlayer, const CoordinatesToPiecesMapping& coordinatesToPiecesMapping);
    bool checkIfPieceCanMove(const Piece* piece, const CoordinatesToPiecesMapping& coordinatesToPiecesMapping);
    bool checkMovePossibility(const Piece* piece, const CoordinatesToPiecesMapping& coordinatesToPiecesMapping, const Coordinates& targetTileCoordinates);
    bool checkCapturePossibility(const Piece* piece, const CoordinatesToPiecesMapping& coordinatesToPiecesMapping, const Coordinates& targetTileCoordinates);
    bool checkIfPieceCanCapture(const Piece* piece, const CoordinatesToPiecesMapping& coordinatesToPiecesMapping);
    bool checkPromotionEligibility(const Piece* piece);
    std::vector<Coordinates> generatePossiblePieceMovementOptionsCoordinates(const Piece* piece);
    std::vector<Coordinates> generatePossiblePieceCaptureOptionsCoordinates(const Piece* piece);
    bool isTileEmpty(const Coordinates &coordinates, const CoordinatesToPiecesMapping &coordinatesToPiecesMapping);
}
