#include <set>
#include "piece_capture_manager.h"

bool PieceCaptureManager::checkCapturePossibility(const Piece& piece, const PiecesManager& piecesPlacement, const Coordinates& targetTileCoordinates)
{
    const Coordinates pieceCoordinates = piece.getCoordinates();

    if(!piecesPlacement.isPieceAtCoordinates(targetTileCoordinates))
    {
        /*Check if this capture is one of possible captures*/
        std::set<Coordinates> captureOptions = generatePossiblePieceCaptureOptionsCoordinates(piece);

        if(captureOptions.contains(targetTileCoordinates))
        {
            std::pair<int, int> targetRowColumnCaptureOffset(targetTileCoordinates - pieceCoordinates);

            const Coordinates& pieceBetweenThisPieceAndTargetTileCoordinates{pieceCoordinates.getRow() + targetRowColumnCaptureOffset.first / 2, pieceCoordinates.getColumn() + targetRowColumnCaptureOffset.second / 2};

            if(piecesPlacement.isPieceAtCoordinates(pieceBetweenThisPieceAndTargetTileCoordinates))
            {
                Piece& pieceBetweenThisPieceAndTargetTile = piecesPlacement.getPieceAtCoordinates(pieceBetweenThisPieceAndTargetTileCoordinates);

                if(piece.getPlayer() != pieceBetweenThisPieceAndTargetTile.getPlayer())
                {
                    return true;
                }
            }
        }
    }

    return false;
}

std::vector<Piece*> PieceCaptureManager::whichPiecesCanCapture(Player activePlayer, const PiecesManager& piecesPlacement)
{
    std::vector<Piece*> piecesWhichCanCapture;

    for(const auto& piece : piecesPlacement.getPieces())
    {
        if(piece->getPlayer() == activePlayer)
        {
            if(checkIfPieceCanCapture(*piece, piecesPlacement))
            {
                piecesWhichCanCapture.push_back(piece.get());
            }
        }
    }

    return piecesWhichCanCapture;
}

std::set<Coordinates> PieceCaptureManager::generatePossiblePieceCaptureOptionsCoordinates(const Piece& piece)
{
    const Player piecePlayer = piece.getPlayer();
    std::vector<std::pair<int, int>> validRowColumnCaptureOffsets;

    if(piece.isPromoted())
    {
        validRowColumnCaptureOffsets = {{-2, -2},
                                        {-2, +2},
                                        {+2, -2},
                                        {+2, +2}};
    }
    else
    {
        if(piecePlayer == Player::SOUTH)
        {
            /*Movement UP is permitted*/
            validRowColumnCaptureOffsets = {{-2, -2},
                                            {-2, +2}};
        }
        else if(piecePlayer == Player::NORTH)
        {
            /*Movement DOWN is permitted*/
            validRowColumnCaptureOffsets = {{+2, -2},
                                            {+2, +2}};
        }
    }

    const Coordinates pieceCoordinates = piece.getCoordinates();
    std::set<Coordinates> validCaptureCoordinates;

    for(const auto& validRowColumnCaptureOffset : validRowColumnCaptureOffsets)
    {
        if(Coordinates::validateCoordinates(pieceCoordinates + validRowColumnCaptureOffset))
        {
            validCaptureCoordinates.emplace(pieceCoordinates + validRowColumnCaptureOffset);
        }
    }

    return validCaptureCoordinates;
}

bool PieceCaptureManager::checkIfPieceCanCapture(const Piece& piece, const PiecesManager& piecesPlacement)
{
    std::set<Coordinates> captureOptions = generatePossiblePieceCaptureOptionsCoordinates(piece);

    return std::ranges::any_of(captureOptions, [&piece, &piecesPlacement](const Coordinates& captureOption)
    {
        return checkCapturePossibility(piece, piecesPlacement, captureOption);
    });
}
