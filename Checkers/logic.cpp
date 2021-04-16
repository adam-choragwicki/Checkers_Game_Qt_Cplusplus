#include "logic.h"
#include <memory>

std::vector<Coordinates> Logic::GeneratePlayableTilesCoordinates()
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
                    playableTilesCoordinates.push_back(Coordinates(row, column));
                }
            }
            else
            {
                if(column % 2 == 0)
                {
                    playableTilesCoordinates.push_back(Coordinates(row, column));
                }
            }
        }
    }

    return playableTilesCoordinates;
}

std::vector<Coordinates> Logic::GenerateStartingPiecesCoordinates(Player player)
{
    std::vector<Coordinates> startingPiecesCoordinates;

    if(player == Player::DOWN)
    {
        for(int row = 6; row <= 8; row++)
        {
            for(int column = 1; column <= 8; column++)
            {
                if(row % 2 != 0)
                {
                    if(column % 2 == 0)
                    {
                        startingPiecesCoordinates.push_back(Coordinates(row, column));
                    }
                }
                else
                {
                    if(column % 2 != 0)
                    {
                        startingPiecesCoordinates.push_back(Coordinates(row, column));
                    }
                }
            }
        }
    }
    else if(player == Player::UP)
    {
        for(int row = 1; row <= 3; row++)
        {
            for(int column = 1; column <= 8; column++)
            {
                if(row % 2 != 0)
                {
                    if(column % 2 == 0)
                    {
                        startingPiecesCoordinates.push_back(Coordinates(row, column));
                    }
                }
                else
                {
                    if(column % 2 != 0)
                    {
                        startingPiecesCoordinates.push_back(Coordinates(row, column));
                    }
                }
            }
        }
    }

    return startingPiecesCoordinates;
}

bool Logic::CheckMovePossibility(const Piece* piece, const std::map<Coordinates, Piece*>& piecesPlacement, const Coordinates& targetTileCoordinates)
{
    //qDebug("Piece is on tile=(%d,%d)", piece->Row(), piece->Column());
    //qDebug("Destination tile=(%d,%d)", targetRow, targetColumn);

    if(IsTileEmpty(targetTileCoordinates, piecesPlacement))
    {
        /*Check if this movement is one of possible movements*/
        std::vector<Coordinates> moveOptions = GeneratePossiblePieceMovementOptionsCoordinates(piece);
        return std::find(moveOptions.begin(), moveOptions.end(), targetTileCoordinates) != moveOptions.end();
    }
    else
    {
        //qDebug("Cannot move, destination tile is not empty!");
        return false;
    }
}

bool Logic::CheckCapturePossibility(const Piece* piece, const std::map<Coordinates, Piece*>& piecesPlacement, const Coordinates& targetTileCoordinates)
{
    const Coordinates pieceCoordinates(piece->Row(), piece->Column());

    if(IsTileEmpty(targetTileCoordinates, piecesPlacement))
    {
        /*Check if this capture is one of possible captures*/
        std::vector<Coordinates> captureOptions = GeneratePossiblePieceCaptureOptionsCoordinates(piece);

        if(std::find(captureOptions.begin(), captureOptions.end(), targetTileCoordinates) != captureOptions.end())
        {
            std::pair<int, int> targetRowColumnCaptureOffset(targetTileCoordinates.Row() - pieceCoordinates.Row(),
                                                             targetTileCoordinates.Column() - pieceCoordinates.Column());

            Piece* pieceBetweenThisPieceAndTargetTile = piecesPlacement.at(Coordinates(pieceCoordinates.Row() + targetRowColumnCaptureOffset.first / 2,
                                                                                       pieceCoordinates.Column() + targetRowColumnCaptureOffset.second / 2));

            if(pieceBetweenThisPieceAndTargetTile)
            {
                if(piece->GetPlayer() != pieceBetweenThisPieceAndTargetTile->GetPlayer())
                {
                    //qDebug("Capture is possible");
                    return true;
                }
                else
                {
                    //qDebug("Cannot capture over friendly piece");
                    return false;
                }
            }
            else
            {
                //qDebug("No piece between, capture not possible");
                return false;
            }
        }
        else
        {
            //qDebug("Capture not permitted");
            return false;
        }
    }
    else
    {
        //qDebug("Destination tile is not empty!");
        return false;
    }
}

std::vector<Piece*> Logic::WhichPiecesCanMove(Player activePlayer, const std::map<Coordinates, Piece*>& piecesPlacement)
{
    std::vector<Piece*> piecesWhichCanMove;

    for(auto& piecePlacement: piecesPlacement)
    {
        Piece* piece = piecePlacement.second;

        if(piece)
        {
            if(piece->GetPlayer() == activePlayer)
            {
                if(CheckIfPieceCanMove(piece, piecesPlacement))
                {
                    piecesWhichCanMove.push_back(piece);
                }
            }
        }
    }

    return piecesWhichCanMove;
}

std::vector<Piece*> Logic::WhichPiecesCanCapture(Player activePlayer, const std::map<Coordinates, Piece*>& piecesPlacement)
{
    std::vector<Piece*> piecesWhichCanCapture;

    for(auto& piecePlacement : piecesPlacement)
    {
        Piece* piece = piecePlacement.second;

        if(piece)
        {
            if(piece->GetPlayer() == activePlayer)
            {
                if(CheckIfPieceCanCapture(piece, piecesPlacement))
                {
                    piecesWhichCanCapture.push_back(piece);
                }
            }
        }
    }

    return piecesWhichCanCapture;
}

std::vector<Coordinates> Logic::GeneratePossiblePieceMovementOptionsCoordinates(const Piece* piece)
{
    const Coordinates pieceCoordinates(piece->Row(), piece->Column());
    const Player piecePlayer = piece->GetPlayer();
    std::vector<std::pair<int, int>> validRowColumnMovementOffsets;

    if(piecePlayer == Player::DOWN)
    {
        //Movement up is permitted
        validRowColumnMovementOffsets.push_back(std::make_pair(-1, -1));
        validRowColumnMovementOffsets.push_back(std::make_pair(-1, +1));

        if(piece->IsPromoted())
        {
            validRowColumnMovementOffsets.push_back(std::make_pair(+1, -1));
            validRowColumnMovementOffsets.push_back(std::make_pair(+1, +1));
        }
    }
    else if(piecePlayer == Player::UP)
    {
        //Movement down is permitted
        validRowColumnMovementOffsets.push_back(std::make_pair(+1, -1));
        validRowColumnMovementOffsets.push_back(std::make_pair(+1, +1));

        if(piece->IsPromoted())
        {
            validRowColumnMovementOffsets.push_back(std::make_pair(-1, -1));
            validRowColumnMovementOffsets.push_back(std::make_pair(-1, +1));
        }
    }

    std::vector<Coordinates> validMovementCoordinates;

    for(unsigned i = 0; i < validRowColumnMovementOffsets.size(); i++)
    {
        if(Coordinates::ValidateCoordinates(pieceCoordinates.Row() + validRowColumnMovementOffsets.at(i).first,
                                            pieceCoordinates.Column() + validRowColumnMovementOffsets.at(i).second))
        {
            validMovementCoordinates.push_back(Coordinates(pieceCoordinates.Row() + validRowColumnMovementOffsets.at(i).first,
                                                           pieceCoordinates.Column() + validRowColumnMovementOffsets.at(i).second));
        }
    }

    return validMovementCoordinates;
}

std::vector<Coordinates> Logic::GeneratePossiblePieceCaptureOptionsCoordinates(const Piece* piece)
{
    const Coordinates pieceCoordinates(piece->Row(), piece->Column());
    const Player piecePlayer = piece->GetPlayer();
    std::vector<std::pair<int, int>> validRowColumnCaptureOffsets;

    if(piecePlayer == Player::DOWN)
    {
        //Movement up is permitted
        validRowColumnCaptureOffsets.push_back(std::make_pair(-2, -2));
        validRowColumnCaptureOffsets.push_back(std::make_pair(-2, +2));

        if(piece->IsPromoted())
        {
            validRowColumnCaptureOffsets.push_back(std::make_pair(+2, -2));
            validRowColumnCaptureOffsets.push_back(std::make_pair(+2, +2));
        }
    }
    else if(piecePlayer == Player::UP)
    {
        //Movement down is permitted
        validRowColumnCaptureOffsets.push_back(std::make_pair(+2, -2));
        validRowColumnCaptureOffsets.push_back(std::make_pair(+2, +2));

        if(piece->IsPromoted())
        {
            validRowColumnCaptureOffsets.push_back(std::make_pair(-2, -2));
            validRowColumnCaptureOffsets.push_back(std::make_pair(-2, +2));
        }
    }

    std::vector<Coordinates> validCaptureCoordinates;

    for(unsigned i = 0; i < validRowColumnCaptureOffsets.size(); i++)
    {
        if(Coordinates::ValidateCoordinates(pieceCoordinates.Row() + validRowColumnCaptureOffsets.at(i).first,
                                            pieceCoordinates.Column() + validRowColumnCaptureOffsets.at(i).second))
        {
            validCaptureCoordinates.push_back(Coordinates(pieceCoordinates.Row() + validRowColumnCaptureOffsets.at(i).first,
                                                          pieceCoordinates.Column() + validRowColumnCaptureOffsets.at(i).second));
        }
    }

    return validCaptureCoordinates;
}

bool Logic::CheckIfPieceCanMove(const Piece* piece, const std::map<Coordinates, Piece*>& piecesPlacement)
{
    std::vector<Coordinates> moveOptions = GeneratePossiblePieceMovementOptionsCoordinates(piece);

    for (unsigned i = 0; i < moveOptions.size(); i++)
    {
        if(CheckMovePossibility(piece, piecesPlacement, moveOptions.at(i)))
        {
            return true;
        }
    }

    return false;
}

bool Logic::CheckIfPieceCanCapture(const Piece* piece, const std::map<Coordinates, Piece *>& piecesPlacement)
{
    std::vector<Coordinates> captureOptions = GeneratePossiblePieceCaptureOptionsCoordinates(piece);

    for (unsigned i = 0; i < captureOptions.size(); i++)
    {
        if(CheckCapturePossibility(piece, piecesPlacement, captureOptions.at(i)))
        {
            return true;
        }
    }

    return false;
}

bool Logic::CheckPromotionEligibility(const Piece* piece)
{
    if(piece->IsPromoted())
    {
        return false;
    }

    const Player piecePlayer = piece->GetPlayer();
    const Coordinates pieceCoordinates(piece->Row(), piece->Column());

    if(piecePlayer == Player::DOWN)
    {
        //Movement up is permitted
        if(pieceCoordinates.Row() == 1)
        {
            //qDebug("Promotion");
            return true;
        }
    }
    else if(piecePlayer == Player::UP)
    {
        //Movement down is permitted
        if(pieceCoordinates.Row() == 8)
        {
            //qDebug("Promotion");
            return true;
        }
    }
    else
    {
        assert(false);
    }

    return false;
}

bool Logic::IsTileEmpty(const Coordinates& coordinates, const std::map<Coordinates, Piece*>& piecesPlacement)
{
    std::vector<Coordinates> playableTileCoordinates = GeneratePlayableTilesCoordinates();

    if(std::find(playableTileCoordinates.begin(), playableTileCoordinates.end(), coordinates) == playableTileCoordinates.end())
    {
        throw std::logic_error("Error, trying to check if piece is on unplayable tile");
    }

    return piecesPlacement.at(coordinates) == nullptr;
}
