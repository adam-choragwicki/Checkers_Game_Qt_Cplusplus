#include "logic.h"
#include <memory>

std::vector<Coordinates> Logic::GenerateAllValidGameTilesCoordinates()
{
    std::vector<Coordinates> validGameTilesCoordinates;

    bool chooseEvenColumns = true;

    for(int row = 1; row <= 8; row++)
    {
        for(int column = 1; column <= 8; column++)
        {
            if(chooseEvenColumns)
            {
                if(column % 2 == 0)
                {
                    validGameTilesCoordinates.push_back(Coordinates(row, column));
                }
            }
            else
            {
                if(column % 2 != 0)
                {
                    validGameTilesCoordinates.push_back(Coordinates(row, column));
                }
            }
        }
        chooseEvenColumns ^= true;
    }

    return validGameTilesCoordinates;
}

std::vector<Coordinates> Logic::GenerateStartingPiecesCoordinates(Player player)
{
    std::vector<Coordinates> startingPiecesCoordinates;

    if(player == Player::Down)
    {
        bool chooseEvenColumns = false;

        for(int row = 6; row <= 8; row++)
        {
            for(int column = 1; column <= 8; column++)
            {
                if(chooseEvenColumns)
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
            chooseEvenColumns ^= true;
        }
    }
    else if(player == Player::Up)
    {
        bool chooseEvenColumns = true;

        for(int row = 1; row <= 3; row++)
        {
            for(int column = 1; column <= 8; column++)
            {
                if(chooseEvenColumns)
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
            chooseEvenColumns ^= true;
        }
    }

    return startingPiecesCoordinates;
}

bool Logic::CheckMovePossibility(const Piece* piece, const std::map<Coordinates, Piece*>& piecesPlacement, const int targetRow, const int targetColumn)
{
    //qDebug("Piece is on tile=(%d,%d)", piece->Row(), piece->Column());
    //qDebug("Destination tile=(%d,%d)", targetRow, targetColumn);

    Player piecePlayer = piece->GetPlayer();

    Piece* pieceOnTargetTile = piecesPlacement.at(Coordinates(targetRow, targetColumn));

    //If target tile is empty
    if(pieceOnTargetTile == nullptr)
    {
        if(piecePlayer == Player::Down)
        {
            //Movement up is permitted
            if((targetRow == piece->Row() - 1) && ((targetColumn == piece->Column() - 1) || (targetColumn == piece->Column() + 1)))
            {
                return true;
            }
            else
            {
                //qDebug("Move not permitted");
                return false;
            }
        }
        else if(piecePlayer == Player::Up)
        {
            //Movement down is permitted
            if(targetRow == piece->Row() + 1 && ((targetColumn == piece->Column() - 1) || (targetColumn == piece->Column() + 1)))
            {
                return true;
            }
            else
            {
                //qDebug("Move not permitted");
                return false;
            }
        }
        else
        {
            assert(false);
        }

        return true;
    }
    else
    {
        //qDebug("Destination tile is not empty!");
        return false;
    }
}

bool Logic::CheckCapturePossibility(const Piece* piece, const std::map<Coordinates, Piece*>& piecesPlacement, const int targetRow, const int targetColumn)
{
    Player piecePlayer = piece->GetPlayer();

    Piece* pieceOnTargetTile = piecesPlacement.at(Coordinates(targetRow, targetColumn));

    //If target tile is empty
    if(pieceOnTargetTile == nullptr)
    {
        if(piecePlayer == Player::Down)
        {
            //Movement up is permitted
            if(targetRow == piece->Row() - 2)
            {
                if(targetColumn == piece->Column() - 2)
                {
                    Piece* pieceBetweenThisPieceAndTargetTile = piecesPlacement.at(Coordinates(piece->Row() - 1, piece->Column() - 1));

                    if(pieceBetweenThisPieceAndTargetTile)
                    {
                        if(pieceBetweenThisPieceAndTargetTile->GetPlayer() == Player::Up)
                        {
                            //qDebug("Capture is possible");
                            return true;
                        }
                        else
                        {
                            //qDebug("Cannot capture over your own piece");
                            return false;
                        }
                    }
                    else
                    {
                        //qDebug("Tile between is empty, capture impossible");
                        return false;
                    }
                }
                else if(targetColumn == piece->Column() + 2)
                {
                    Piece* pieceBetweenThisPieceAndTargetTile = piecesPlacement.at(Coordinates(piece->Row() - 1, piece->Column() + 1));

                    if(pieceBetweenThisPieceAndTargetTile)
                    {
                        if(pieceBetweenThisPieceAndTargetTile->GetPlayer() == Player::Up)
                        {
                            //qDebug("Capture is possible");
                            return true;
                        }
                        else
                        {
                            //qDebug("Cannot capture over your own piece");
                            return false;
                        }
                    }
                    else
                    {
                        //qDebug("Tile between is empty, capture impossible");
                        return false;
                    }
                }
                else
                {
                    //qDebug("Capture target is not 2 columns away");
                    return false;
                }
            }
            else
            {
                //qDebug("Capture target is not 2 rows away");
                return false;
            }
        }
        else if(piecePlayer == Player::Up)
        {
            //Movement down is permitted
            if(targetRow == piece->Row() + 2)
            {
                if(targetColumn == piece->Column() - 2)
                {
                    Piece* pieceBetweenThisPieceAndTargetTile = piecesPlacement.at(Coordinates(piece->Row() + 1, piece->Column() - 1));

                    if(pieceBetweenThisPieceAndTargetTile)
                    {
                        if(pieceBetweenThisPieceAndTargetTile->GetPlayer() == Player::Down)
                        {
                            //qDebug("Capture is possible");
                            return true;
                        }
                        else
                        {
                            //qDebug("Cannot capture over your own piece");
                            return false;
                        }
                    }
                    else
                    {
                        //qDebug("Tile between is empty, capture impossible");
                        return false;
                    }
                }
                else if(targetColumn == piece->Column() + 2)
                {
                    Piece* pieceBetweenThisPieceAndTargetTile = piecesPlacement.at(Coordinates(piece->Row() + 1, piece->Column() + 1));

                    if(pieceBetweenThisPieceAndTargetTile)
                    {
                        if(pieceBetweenThisPieceAndTargetTile->GetPlayer() == Player::Down)
                        {
                            //qDebug("Capture is possible");
                            return true;
                        }
                        else
                        {
                            //qDebug("Cannot capture over your own piece");
                            return false;
                        }
                    }
                    else
                    {
                        //qDebug("Tile between is empty, capture impossible");
                        return false;
                    }
                }
                else
                {
                    //qDebug("Capture target is not 2 columns away");
                    return false;
                }
            }
            else
            {
                //qDebug("Capture target is not 2 rows away");
                return false;
            }
        }
        else
        {
            assert(false);
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

    for(auto piece: piecesPlacement)
    {
        if(piece.second != nullptr)
        {
            Player piecePlayer = piece.second->GetPlayer();

            if(piecePlayer == activePlayer)
            {
                if(piecePlayer == Player::Down)
                {
                    //Movement up is permitted
                    Coordinates pieceCoordinates(piece.second->Row(), piece.second->Column());

                    std::unique_ptr<Coordinates> moveOption1;
                    std::unique_ptr<Coordinates> moveOption2;

                    try {
                        moveOption1 = std::make_unique<Coordinates>(pieceCoordinates.Row() - 1, pieceCoordinates.Column() - 1);
                    }
                    catch(std::out_of_range& exception) {
                        moveOption1 = nullptr;
                    }

                    try {
                        moveOption2 = std::make_unique<Coordinates>(pieceCoordinates.Row() - 1, pieceCoordinates.Column() + 1);
                    }  catch(std::out_of_range& exception) {
                        moveOption2 = nullptr;
                    }

                    if(moveOption1)
                    {
                        if(piecesPlacement.at(*moveOption1) == nullptr)
                        {
                            piecesWhichCanMove.push_back(piece.second);

                        }
                    }

                    if(moveOption2)
                    {
                        if(piecesPlacement.at(*moveOption2) == nullptr)
                        {
                            piecesWhichCanMove.push_back(piece.second);
                        }
                    }
                }
                else if(piecePlayer == Player::Up)
                {
                    //Movement down is permitted
                    Coordinates pieceCoordinates(piece.second->Row(), piece.second->Column());

                    std::unique_ptr<Coordinates> moveOption1;
                    std::unique_ptr<Coordinates> moveOption2;

                    try {
                        moveOption1 = std::make_unique<Coordinates>(pieceCoordinates.Row() + 1, pieceCoordinates.Column() - 1);
                    }
                    catch(std::out_of_range& exception) {
                        moveOption1 = nullptr;
                    }

                    try {
                        moveOption2 = std::make_unique<Coordinates>(pieceCoordinates.Row() + 1, pieceCoordinates.Column() + 1);
                    }  catch(std::out_of_range& exception) {
                        moveOption2 = nullptr;
                    }

                    if(moveOption1)
                    {
                        if(piecesPlacement.at(*moveOption1) == nullptr)
                        {
                            piecesWhichCanMove.push_back(piece.second);
                        }
                    }

                    if(moveOption2)
                    {
                        if(piecesPlacement.at(*moveOption2) == nullptr)
                        {
                            piecesWhichCanMove.push_back(piece.second);
                        }
                    }
                }
            }
        }
    }

    return piecesWhichCanMove;
}

std::vector<Piece*> Logic::WhichPiecesCanCapture(Player activePlayer, const std::map<Coordinates, Piece*>& piecesPlacement)
{
    std::vector<Piece*> piecesWhichCanCapture;

    for(auto piecePlacement : piecesPlacement)
    {
        if(piecePlacement.second != nullptr)
        {
            Player piecePlayer = piecePlacement.second->GetPlayer();

            if(piecePlayer == activePlayer)
            {
                if(piecePlayer == Player::Down)
                {
                    //Movement up is permitted
                    Coordinates pieceCoordinates(piecePlacement.second->Row(), piecePlacement.second->Column());

                    std::unique_ptr<Coordinates> moveOption1;
                    std::unique_ptr<Coordinates> moveOption2;

                    try {
                        moveOption1 = std::make_unique<Coordinates>(pieceCoordinates.Row() - 2, pieceCoordinates.Column() - 2);
                    }
                    catch(std::out_of_range& exception) {
                        moveOption1 = nullptr;
                    }

                    try {
                        moveOption2 = std::make_unique<Coordinates>(pieceCoordinates.Row() - 2, pieceCoordinates.Column() + 2);
                    }
                    catch(std::out_of_range& exception) {
                        moveOption2 = nullptr;
                    }

                    if(moveOption1)
                    {
                        if(CheckCapturePossibility(piecePlacement.second, piecesPlacement, moveOption1->Row(), moveOption1->Column()))
                        {
                            piecesWhichCanCapture.push_back(piecePlacement.second);
                        }
                    }

                    if(moveOption2)
                    {
                        if(CheckCapturePossibility(piecePlacement.second, piecesPlacement, moveOption2->Row(), moveOption2->Column()))
                        {
                            piecesWhichCanCapture.push_back(piecePlacement.second);
                        }
                    }
                }
                else if(piecePlayer == Player::Up)
                {
                    //Movement down is permitted
                    Coordinates pieceCoordinates(piecePlacement.second->Row(), piecePlacement.second->Column());

                    std::unique_ptr<Coordinates> moveOption1;
                    std::unique_ptr<Coordinates> moveOption2;

                    try {
                        moveOption1 = std::make_unique<Coordinates>(pieceCoordinates.Row() + 2, pieceCoordinates.Column() - 2);
                    }
                    catch(std::out_of_range& exception) {
                        moveOption1 = nullptr;
                    }

                    try {
                        moveOption2 = std::make_unique<Coordinates>(pieceCoordinates.Row() + 2, pieceCoordinates.Column() + 2);
                    }
                    catch(std::out_of_range& exception) {
                        moveOption2 = nullptr;
                    }

                    if(moveOption1)
                    {
                        if(CheckCapturePossibility(piecePlacement.second, piecesPlacement, moveOption1->Row(), moveOption1->Column()))
                        {
                            piecesWhichCanCapture.push_back(piecePlacement.second);
                        }
                    }

                    if(moveOption2)
                    {
                        if(CheckCapturePossibility(piecePlacement.second, piecesPlacement, moveOption2->Row(), moveOption2->Column()))
                        {
                            piecesWhichCanCapture.push_back(piecePlacement.second);
                        }
                    }
                }
            }
        }
    }

    return piecesWhichCanCapture;
}
