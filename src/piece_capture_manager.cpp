#include "piece_capture_manager.h"

std::vector<Piece*> PieceCaptureManager::whichPiecesCanCapture(const Player activePlayer, const PiecesManager& piecesManager)
{
    std::vector<Piece*> piecesWhichCanCapture;

    for (const auto& piece: piecesManager.getPieces())
    {
        if (!piece->isAlive())
        {
            continue; // ignore dead pieces
        }

        if (piece->getPlayer() != activePlayer)
        {
            continue; // ignore non-active player's pieces
        }

        if (checkIfPieceCanCapture(*piece, piecesManager))
        {
            piecesWhichCanCapture.push_back(piece.get());
        }
    }

    return piecesWhichCanCapture;
}

bool PieceCaptureManager::checkCapturePossibility(const Piece& piece, const PiecesManager& piecesManager, const Coordinates& targetTileCoordinates)
{
    const Coordinates pieceCoordinates = piece.getCoordinates();

    if (!piecesManager.isPieceAtCoordinates(targetTileCoordinates))
    {
        /*Check if this capture is one of possible captures*/

        if (const std::set<Coordinates> captureOptions = generatePossiblePieceCaptureOptionsCoordinates(piece); captureOptions.contains(targetTileCoordinates))
        {
            std::pair targetRowColumnCaptureOffset(targetTileCoordinates - pieceCoordinates);

            if (const Coordinates& pieceBetweenThisPieceAndTargetTileCoordinates{pieceCoordinates.getRow() + targetRowColumnCaptureOffset.first / 2, pieceCoordinates.getColumn() + targetRowColumnCaptureOffset.second / 2}; piecesManager.
                isPieceAtCoordinates(pieceBetweenThisPieceAndTargetTileCoordinates))
            {
                if (const Piece& pieceBetweenThisPieceAndTargetTile = piecesManager.getPieceAtCoordinates(pieceBetweenThisPieceAndTargetTileCoordinates); piece.getPlayer() != pieceBetweenThisPieceAndTargetTile.getPlayer())
                {
                    return true;
                }
            }
        }
    }

    return false;
}

bool PieceCaptureManager::checkIfPieceCanCapture(const Piece& piece, const PiecesManager& piecesManager)
{
    std::set<Coordinates> captureOptions = generatePossiblePieceCaptureOptionsCoordinates(piece);

    return std::ranges::any_of(captureOptions, [&piece, &piecesManager](const Coordinates& captureOption)
    {
        return checkCapturePossibility(piece, piecesManager, captureOption);
    });
}

std::set<Coordinates> PieceCaptureManager::generatePossiblePieceCaptureOptionsCoordinates(const Piece& piece)
{
    const Player piecePlayer = piece.getPlayer();
    std::vector<std::pair<int, int>> validRowColumnCaptureOffsets;

    if (piece.isPromoted())
    {
        validRowColumnCaptureOffsets = {
            {-2, -2},
            {-2, +2},
            {+2, -2},
            {+2, +2}
        };
    }
    else
    {
        if (piecePlayer == Player::SOUTH)
        {
            /*Movement UP is permitted*/
            validRowColumnCaptureOffsets = {
                {-2, -2},
                {-2, +2}
            };
        }
        else if (piecePlayer == Player::NORTH)
        {
            /*Movement DOWN is permitted*/
            validRowColumnCaptureOffsets = {
                {+2, -2},
                {+2, +2}
            };
        }
    }

    const Coordinates pieceCoordinates = piece.getCoordinates();
    std::set<Coordinates> validCaptureCoordinates;

    for (const auto& validRowColumnCaptureOffset: validRowColumnCaptureOffsets)
    {
        if (Coordinates::validateCoordinates(pieceCoordinates + validRowColumnCaptureOffset))
        {
            validCaptureCoordinates.emplace(pieceCoordinates + validRowColumnCaptureOffset);
        }
    }

    return validCaptureCoordinates;
}
