#include "piece_capture_manager.h"
#include "tile_manager.h"

bool PieceCaptureManager::checkCapturePossibility(const Piece* piece,
                                                  const PiecesPlacement& piecesPlacement,
                                                  const Coordinates& targetTileCoordinates)
{
    const Coordinates pieceCoordinates = piece->getCoordinates();

    if(TileManager::isTileEmpty(targetTileCoordinates, piecesPlacement))
    {
        /*Check if this capture is one of possible captures*/
        QVector<Coordinates> captureOptions = generatePossiblePieceCaptureOptionsCoordinates(piece);

        if(captureOptions.contains(targetTileCoordinates))
        {
            std::pair<int, int> targetRowColumnCaptureOffset(targetTileCoordinates - pieceCoordinates);

            const Coordinates& pieceBetweenThisPieceAndTargetTileCoordinates{pieceCoordinates.getRow() + targetRowColumnCaptureOffset.first / 2,
                                                                             pieceCoordinates.getColumn() + targetRowColumnCaptureOffset.second / 2};

            if(piecesPlacement.isPieceAtCoordinates(pieceBetweenThisPieceAndTargetTileCoordinates))
            {
                Piece* pieceBetweenThisPieceAndTargetTile = piecesPlacement.getPieceAtCoordinates(pieceBetweenThisPieceAndTargetTileCoordinates);

                if(piece->getPlayer() != pieceBetweenThisPieceAndTargetTile->getPlayer())
                {
                    return true;
                }
            }
        }
    }

    return false;
}

QVector<Piece*> PieceCaptureManager::whichPiecesCanCapture(Player activePlayer, const PiecesPlacement& piecesPlacement)
{
    QVector<Piece*> piecesWhichCanCapture;

    for(const auto& piece : piecesPlacement.getPieces())
    {
        if(piece->getPlayer() == activePlayer)
        {
            if(checkIfPieceCanCapture(piece, piecesPlacement))
            {
                piecesWhichCanCapture.push_back(piece);
            }
        }
    }

    return piecesWhichCanCapture;
}

QVector<Coordinates> PieceCaptureManager::generatePossiblePieceCaptureOptionsCoordinates(const Piece* piece)
{
    const Player piecePlayer = piece->getPlayer();
    QVector<std::pair<int, int>> validRowColumnCaptureOffsets;

    if(piece->isPromoted())
    {
        validRowColumnCaptureOffsets = {{-2, -2}, {-2, +2}, {+2, -2}, {+2, +2}};
    }
    else
    {
        if(piecePlayer == Player::down)
        {
            /*Movement up is permitted*/
            validRowColumnCaptureOffsets = {{-2, -2}, {-2, +2}};
        }
        else if(piecePlayer == Player::up)
        {
            /*Movement down is permitted*/
            validRowColumnCaptureOffsets = {{+2, -2}, {+2, +2}};
        }
    }

    const Coordinates pieceCoordinates = piece->getCoordinates();
    QVector<Coordinates> validCaptureCoordinates;

    for(const auto& validRowColumnCaptureOffset : validRowColumnCaptureOffsets)
    {
        if(Coordinates::validateCoordinates(pieceCoordinates + validRowColumnCaptureOffset))
        {
            validCaptureCoordinates.emplace_back(pieceCoordinates + validRowColumnCaptureOffset);
        }
    }

    return validCaptureCoordinates;
}

bool PieceCaptureManager::checkIfPieceCanCapture(const Piece* piece, const PiecesPlacement& piecesPlacement)
{
    QVector<Coordinates> captureOptions = generatePossiblePieceCaptureOptionsCoordinates(piece);

    return std::ranges::any_of(captureOptions, [&piece, &piecesPlacement](const Coordinates& captureOption)
    {
        return checkCapturePossibility(piece, piecesPlacement, captureOption);
    });
}
