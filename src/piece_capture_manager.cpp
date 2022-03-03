#include "piece_capture_manager.h"
#include "tile_manager.h"

bool PieceCaptureManager::checkCapturePossibility(const Piece* piece, const CoordinatesToPiecesMapping& coordinatesToPiecesMapping, const Coordinates& targetTileCoordinates)
{
    const Coordinates pieceCoordinates(piece->getRow(), piece->getColumn());

    if(TileManager::isTileEmpty(targetTileCoordinates, coordinatesToPiecesMapping))
    {
        /*Check if this capture is one of possible captures*/
        std::vector<Coordinates> captureOptions = generatePossiblePieceCaptureOptionsCoordinates(piece);

        if(std::find(captureOptions.begin(), captureOptions.end(), targetTileCoordinates) != captureOptions.end())
        {
            std::pair<int, int> targetRowColumnCaptureOffset(targetTileCoordinates.getRow() - pieceCoordinates.getRow(),
                                                             targetTileCoordinates.getColumn() - pieceCoordinates.getColumn());

            Piece* pieceBetweenThisPieceAndTargetTile = coordinatesToPiecesMapping.at(Coordinates(pieceCoordinates.getRow() + targetRowColumnCaptureOffset.first / 2,
                                                                                                  pieceCoordinates.getColumn() + targetRowColumnCaptureOffset.second / 2));

            if(pieceBetweenThisPieceAndTargetTile)
            {
                if(piece->getPlayer() != pieceBetweenThisPieceAndTargetTile->getPlayer())
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

std::vector<Piece*> PieceCaptureManager::whichPiecesCanCapture(Player activePlayer, const CoordinatesToPiecesMapping& coordinatesToPiecesMapping)
{
    std::vector<Piece*> piecesWhichCanCapture;

    for(auto& coordinatesToPiecesPair : coordinatesToPiecesMapping)
    {
        Piece* piece = coordinatesToPiecesPair.second;

        if(piece)
        {
            if(piece->getPlayer() == activePlayer)
            {
                if(checkIfPieceCanCapture(piece, coordinatesToPiecesMapping))
                {
                    piecesWhichCanCapture.push_back(piece);
                }
            }
        }
    }

    return piecesWhichCanCapture;
}

std::vector<Coordinates> PieceCaptureManager::generatePossiblePieceCaptureOptionsCoordinates(const Piece* piece)
{
    const Coordinates pieceCoordinates(piece->getRow(), piece->getColumn());
    const Player piecePlayer = piece->getPlayer();
    std::vector<std::pair<int, int>> validRowColumnCaptureOffsets;

    if(piecePlayer == Player::down)
    {
        /*Movement up is permitted*/
        validRowColumnCaptureOffsets.emplace_back(-2, -2);
        validRowColumnCaptureOffsets.emplace_back(-2, +2);

        if(piece->isPromoted())
        {
            validRowColumnCaptureOffsets.emplace_back(+2, -2);
            validRowColumnCaptureOffsets.emplace_back(+2, +2);
        }
    }
    else if(piecePlayer == Player::up)
        {
            /*Movement down is permitted*/
            validRowColumnCaptureOffsets.emplace_back(+2, -2);
            validRowColumnCaptureOffsets.emplace_back(+2, +2);

            if(piece->isPromoted())
            {
                validRowColumnCaptureOffsets.emplace_back(-2, -2);
                validRowColumnCaptureOffsets.emplace_back(-2, +2);
            }
        }

    std::vector<Coordinates> validCaptureCoordinates;

    for(auto& validRowColumnCaptureOffset : validRowColumnCaptureOffsets)
    {
        if(Coordinates::validateCoordinates(pieceCoordinates.getRow() + validRowColumnCaptureOffset.first,
                                            pieceCoordinates.getColumn() + validRowColumnCaptureOffset.second))
        {
            validCaptureCoordinates.emplace_back(pieceCoordinates.getRow() + validRowColumnCaptureOffset.first,
                                                 pieceCoordinates.getColumn() + validRowColumnCaptureOffset.second);
        }
    }

    return validCaptureCoordinates;
}

bool PieceCaptureManager::checkIfPieceCanCapture(const Piece* piece, const std::map<Coordinates, Piece *>& coordinatesToPiecesMapping)
{
    std::vector<Coordinates> captureOptions = generatePossiblePieceCaptureOptionsCoordinates(piece);

    for(auto& captureOption : captureOptions)
    {
        if(checkCapturePossibility(piece, coordinatesToPiecesMapping, captureOption))
        {
            return true;
        }
    }

    return false;
}
