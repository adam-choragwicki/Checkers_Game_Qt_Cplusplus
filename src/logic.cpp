#include "logic.h"
#include "common.h"

#include <memory>

namespace logic {

std::vector<Coordinates> generatePlayableTilesCoordinates()
{
    std::vector<Coordinates> playableTilesCoordinates;

    for(int row = 1; row <= 8; row++)
    {
        for(int column = 1; column <= 8; column++)
        {
            if(row % 2 == 0)
            {
                if(column % 2 != 0)
                {
                    playableTilesCoordinates.emplace_back(row, column);
                }
            }
            else
            {
                if(column % 2 == 0)
                {
                    playableTilesCoordinates.emplace_back(row, column);
                }
            }
        }
    }

    return playableTilesCoordinates;
}

std::vector<Coordinates> generateStartingPiecesCoordinates(Player player)
{
    std::vector<Coordinates> startingPiecesCoordinates;

    if(player == Player::down)
    {
        for(int row = 6; row <= 8; row++)
        {
            for(int column = 1; column <= 8; column++)
            {
                if(row % 2 != 0)
                {
                    if(column % 2 == 0)
                    {
                        startingPiecesCoordinates.emplace_back(row, column);
                    }
                }
                else
                {
                    if(column % 2 != 0)
                    {
                        startingPiecesCoordinates.emplace_back(row, column);
                    }
                }
            }
        }
    }
    else if(player == Player::up)
    {
        for(int row = 1; row <= 3; row++)
        {
            for(int column = 1; column <= 8; column++)
            {
                if(row % 2 != 0)
                {
                    if(column % 2 == 0)
                    {
                        startingPiecesCoordinates.emplace_back(row, column);
                    }
                }
                else
                {
                    if(column % 2 != 0)
                    {
                        startingPiecesCoordinates.emplace_back(row, column);
                    }
                }
            }
        }
    }

    return startingPiecesCoordinates;
}

bool checkMovePossibility(const Piece* piece, const CoordinatesToPiecesMapping& coordinatesToPiecesMapping, const Coordinates& targetTileCoordinates)
{
    if(isTileEmpty(targetTileCoordinates, coordinatesToPiecesMapping))
    {
        /*Check if this movement is one of possible movements*/
        std::vector<Coordinates> moveOptions = generatePossiblePieceMovementOptionsCoordinates(piece);
        return std::find(moveOptions.begin(), moveOptions.end(), targetTileCoordinates) != moveOptions.end();
    }
    else
    {
        return false;
    }
}

bool checkCapturePossibility(const Piece* piece, const CoordinatesToPiecesMapping& coordinatesToPiecesMapping, const Coordinates& targetTileCoordinates)
{
    const Coordinates pieceCoordinates(piece->getRow(), piece->getColumn());

    if(isTileEmpty(targetTileCoordinates, coordinatesToPiecesMapping))
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

std::vector<Piece*> whichPiecesCanMove(Player activePlayer, const CoordinatesToPiecesMapping& coordinatesToPiecesMapping)
{
    std::vector<Piece*> piecesWhichCanMove;

    for(auto& coordinatesToPiecesPair: coordinatesToPiecesMapping)
    {
        Piece* piece = coordinatesToPiecesPair.second;

        if(piece)
        {
            if(piece->getPlayer() == activePlayer)
            {
                if(checkIfPieceCanMove(piece, coordinatesToPiecesMapping))
                {
                    piecesWhichCanMove.push_back(piece);
                }
            }
        }
    }

    return piecesWhichCanMove;
}

std::vector<Piece*> whichPiecesCanCapture(Player activePlayer, const CoordinatesToPiecesMapping& coordinatesToPiecesMapping)
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

std::vector<Coordinates> generatePossiblePieceMovementOptionsCoordinates(const Piece* piece)
{
    const Coordinates pieceCoordinates(piece->getRow(), piece->getColumn());
    const Player piecePlayer = piece->getPlayer();
    std::vector<std::pair<int, int>> validRowColumnMovementOffsets;

    if(piecePlayer == Player::down)
    {
        /*Movement up is permitted*/
        validRowColumnMovementOffsets.emplace_back(-1, -1);
        validRowColumnMovementOffsets.emplace_back(-1, +1);

        if(piece->isPromoted())
        {
            validRowColumnMovementOffsets.emplace_back(+1, -1);
            validRowColumnMovementOffsets.emplace_back(+1, +1);
        }
    }
    else if(piecePlayer == Player::up)
    {
        /*Movement down is permitted*/
        validRowColumnMovementOffsets.emplace_back(+1, -1);
        validRowColumnMovementOffsets.emplace_back(+1, +1);

        if(piece->isPromoted())
        {
            validRowColumnMovementOffsets.emplace_back(-1, -1);
            validRowColumnMovementOffsets.emplace_back(-1, +1);
        }
    }

    std::vector<Coordinates> validMovementCoordinates;

    for(auto& validRowColumnMovementOffset : validRowColumnMovementOffsets)
    {
        if(Coordinates::validateCoordinates(pieceCoordinates.getRow() + validRowColumnMovementOffset.first,
                                            pieceCoordinates.getColumn() + validRowColumnMovementOffset.second))
        {
            validMovementCoordinates.emplace_back(pieceCoordinates.getRow() + validRowColumnMovementOffset.first,
                                                           pieceCoordinates.getColumn() + validRowColumnMovementOffset.second);
        }
    }

    return validMovementCoordinates;
}

std::vector<Coordinates> generatePossiblePieceCaptureOptionsCoordinates(const Piece* piece)
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

bool checkIfPieceCanMove(const Piece* piece, const CoordinatesToPiecesMapping& coordinatesToPiecesMapping)
{
    std::vector<Coordinates> moveOptions = generatePossiblePieceMovementOptionsCoordinates(piece);

    for(auto& moveOption: moveOptions)
    {
        if(checkMovePossibility(piece, coordinatesToPiecesMapping, moveOption))
        {
            return true;
        }
    }

    return false;
}

bool checkIfPieceCanCapture(const Piece* piece, const std::map<Coordinates, Piece *>& coordinatesToPiecesMapping)
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

bool checkPromotionEligibility(const Piece* piece)
{
    if(piece->isPromoted())
    {
        return false;
    }

    const Player piecePlayer = piece->getPlayer();
    const Coordinates pieceCoordinates(piece->getRow(), piece->getColumn());

    if(piecePlayer == Player::down)
    {
        /*Movement up is permitted*/
        if(pieceCoordinates.getRow() == 1)
        {
            return true;
        }
    }
    else if(piecePlayer == Player::up)
    {
        /*Movement down is permitted*/
        if(pieceCoordinates.getRow() == 8)
        {
            return true;
        }
    }

    return false;
}

bool isTileEmpty(const Coordinates& coordinates, const CoordinatesToPiecesMapping& coordinatesToPiecesMapping)
{
    std::vector<Coordinates> playableTileCoordinates = generatePlayableTilesCoordinates();

    if(std::find(playableTileCoordinates.begin(), playableTileCoordinates.end(), coordinates) == playableTileCoordinates.end())
    {
        throw std::logic_error("Error, trying to check if piece is on unplayable tile");
    }

    return coordinatesToPiecesMapping.at(coordinates) == nullptr;
}
}
