#include "logic.h"
#include <memory>

std::vector<Coordinates> Logic::GeneratePlayableTilesCoordinates()
{
    std::vector<Coordinates> validGameTilesCoordinates;

    for(int row = 1; row <= 8; row++)
    {
        for(int column = 1; column <= 8; column++)
        {
            if(row % 2 == 0)
            {
                if(column % 2 != 0)
                {
                    validGameTilesCoordinates.push_back(Coordinates(row, column));
                }
            }
            else
            {
                if(column % 2 == 0)
                {
                    validGameTilesCoordinates.push_back(Coordinates(row, column));
                }
            }
        }
    }

    return validGameTilesCoordinates;
}

std::vector<Coordinates> Logic::GenerateStartingPiecesCoordinates(Player player)
{
    std::vector<Coordinates> startingPiecesCoordinates;

    if(player == Player::Down)
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
    else if(player == Player::Up)
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

bool Logic::CheckMovePossibility(const Piece* piece, const std::map<Coordinates, Piece*>& piecesPlacement, const int targetRow, const int targetColumn)
{
    //qDebug("Piece is on tile=(%d,%d)", piece->Row(), piece->Column());
    //qDebug("Destination tile=(%d,%d)", targetRow, targetColumn);

    const Player piecePlayer = piece->GetPlayer();
    const Piece* pieceOnTargetTile = piecesPlacement.at(Coordinates(targetRow, targetColumn));

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
            //Movement down is permitted for promoted piece
            else if(piece->IsPromoted() == true && (targetRow == piece->Row() + 1) && ((targetColumn == piece->Column() - 1) || (targetColumn == piece->Column() + 1)))
            {
                qDebug("Movement down is permitted for promoted piece");
                return true;
            }
            else
            {
                //qDebug("Movement not permitted");
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
            //Movement up is permitted for promoted piece
            else if(piece->IsPromoted() == true && (targetRow == piece->Row() - 1) && ((targetColumn == piece->Column() - 1) || (targetColumn == piece->Column() + 1)))
            {
                qDebug("Movement up is permitted for promoted piece");
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
    const Player piecePlayer = piece->GetPlayer();
    const Piece* pieceOnTargetTile = piecesPlacement.at(Coordinates(targetRow, targetColumn));

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
            else if(piece->IsPromoted() && (targetRow == piece->Row() + 2))
            {
                if(targetColumn == piece->Column() - 2)
                {
                    Piece* pieceBetweenThisPieceAndTargetTile = piecesPlacement.at(Coordinates(piece->Row() + 1, piece->Column() - 1));

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
                    Piece* pieceBetweenThisPieceAndTargetTile = piecesPlacement.at(Coordinates(piece->Row() + 1, piece->Column() + 1));

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
            else if(piece->IsPromoted() && (targetRow == piece->Row() - 2))
            {
                if(targetColumn == piece->Column() - 2)
                {
                    Piece* pieceBetweenThisPieceAndTargetTile = piecesPlacement.at(Coordinates(piece->Row() - 1, piece->Column() - 1));

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
                    Piece* pieceBetweenThisPieceAndTargetTile = piecesPlacement.at(Coordinates(piece->Row() - 1, piece->Column() + 1));

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

    for(auto piecePlacement: piecesPlacement)
    {
        if(piecePlacement.second != nullptr)
        {
            const Player piecePlayer = piecePlacement.second->GetPlayer();

            if(piecePlayer == activePlayer)
            {
                if(CheckIfPieceCanMove(piecePlacement.second, piecesPlacement))
                {
                    piecesWhichCanMove.push_back(piecePlacement.second);
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
            const Player piecePlayer = piecePlacement.second->GetPlayer();

            if(piecePlayer == activePlayer)
            {
                if(CheckIfPieceCanCapture(piecePlacement.second, piecesPlacement))
                {
                    piecesWhichCanCapture.push_back(piecePlacement.second);
                }
            }
        }
    }

    return piecesWhichCanCapture;
}

bool Logic::CheckIfPieceCanMove(const Piece* piece, const std::map<Coordinates, Piece *>& piecesPlacement)
{
    const Player piecePlayer = piece->GetPlayer();

    if(piecePlayer == Player::Down)
    {
        //Movement up is permitted
        const Coordinates pieceCoordinates(piece->Row(), piece->Column());
        std::array<std::unique_ptr<Coordinates>, 4> moveOptions;

        try {
            moveOptions[0] = std::make_unique<Coordinates>(pieceCoordinates.Row() - 1, pieceCoordinates.Column() - 1);
        }
        catch(std::out_of_range& exception) {
            moveOptions[0] = nullptr;
        }

        try {
            moveOptions[1] = std::make_unique<Coordinates>(pieceCoordinates.Row() - 1, pieceCoordinates.Column() + 1);
        }
        catch(std::out_of_range& exception) {
            moveOptions[1] = nullptr;
        }

        if(piece->IsPromoted())
        {
            try {
                moveOptions[2] = std::make_unique<Coordinates>(pieceCoordinates.Row() + 1, pieceCoordinates.Column() - 1);
            }
            catch(std::out_of_range& exception) {
                moveOptions[2] = nullptr;
            }

            try {
                moveOptions[3] = std::make_unique<Coordinates>(pieceCoordinates.Row() + 1, pieceCoordinates.Column() + 1);
            }
            catch(std::out_of_range& exception) {
                moveOptions[3] = nullptr;
            }
        }

        for(auto& moveOption : moveOptions)
        {
            //If move option is valid and the target tile is empty
            if(moveOption && piecesPlacement.at(*moveOption) == nullptr)
            {
                return true;
            }
        }
    }
    else if(piecePlayer == Player::Up)
    {
        //Movement down is permitted
        const Coordinates pieceCoordinates(piece->Row(), piece->Column());
        std::array<std::unique_ptr<Coordinates>, 4> moveOptions;

        try {
            moveOptions[0] = std::make_unique<Coordinates>(pieceCoordinates.Row() + 1, pieceCoordinates.Column() - 1);
        }
        catch(std::out_of_range& exception) {
            moveOptions[0] = nullptr;
        }

        try {
            moveOptions[1] = std::make_unique<Coordinates>(pieceCoordinates.Row() + 1, pieceCoordinates.Column() + 1);
        }
        catch(std::out_of_range& exception) {
            moveOptions[1] = nullptr;
        }

        if(piece->IsPromoted())
        {
            try {
                moveOptions[2] = std::make_unique<Coordinates>(pieceCoordinates.Row() - 1, pieceCoordinates.Column() - 1);
            }
            catch(std::out_of_range& exception) {
                moveOptions[2] = nullptr;
            }

            try {
                moveOptions[3] = std::make_unique<Coordinates>(pieceCoordinates.Row() - 1, pieceCoordinates.Column() + 1);
            }
            catch(std::out_of_range& exception) {
                moveOptions[3] = nullptr;
            }
        }

        for(auto& moveOption : moveOptions)
        {
            //If move option is valid and the target tile is empty
            if(moveOption && piecesPlacement.at(*moveOption) == nullptr)
            {
                return true;
            }
        }
    }

    return false;
}

bool Logic::CheckIfPieceCanCapture(const Piece* piece, const std::map<Coordinates, Piece *>& piecesPlacement)
{
    const Player piecePlayer = piece->GetPlayer();

    if(piecePlayer == Player::Down)
    {
        //Movement up is permitted
        const Coordinates pieceCoordinates(piece->Row(), piece->Column());
        std::array<std::unique_ptr<Coordinates>, 4> moveOptions;

        try {
            moveOptions[0] = std::make_unique<Coordinates>(pieceCoordinates.Row() - 2, pieceCoordinates.Column() - 2);
        }
        catch(std::out_of_range& exception) {
            moveOptions[0] = nullptr;
        }

        try {
            moveOptions[1] = std::make_unique<Coordinates>(pieceCoordinates.Row() - 2, pieceCoordinates.Column() + 2);
        }
        catch(std::out_of_range& exception) {
            moveOptions[1] = nullptr;
        }

        if(piece->IsPromoted())
        {
            try {
                moveOptions[2] = std::make_unique<Coordinates>(pieceCoordinates.Row() + 2, pieceCoordinates.Column() - 2);
            }
            catch(std::out_of_range& exception) {
                moveOptions[2] = nullptr;
            }

            try {
                moveOptions[3] = std::make_unique<Coordinates>(pieceCoordinates.Row() + 2, pieceCoordinates.Column() + 2);
            }
            catch(std::out_of_range& exception) {
                moveOptions[3] = nullptr;
            }
        }

        for(auto& moveOption : moveOptions)
        {
            if(moveOption && CheckCapturePossibility(piece, piecesPlacement, moveOption->Row(), moveOption->Column()))
            {
                return true;
            }
        }
    }
    else if(piecePlayer == Player::Up)
    {
        //Movement down is permitted
        const Coordinates pieceCoordinates(piece->Row(), piece->Column());
        std::array<std::unique_ptr<Coordinates>, 4> moveOptions;

        try {
            moveOptions[0] = std::make_unique<Coordinates>(pieceCoordinates.Row() + 2, pieceCoordinates.Column() - 2);
        }
        catch(std::out_of_range& exception) {
            moveOptions[0] = nullptr;
        }

        try {
            moveOptions[1] = std::make_unique<Coordinates>(pieceCoordinates.Row() + 2, pieceCoordinates.Column() + 2);
        }
        catch(std::out_of_range& exception) {
            moveOptions[1] = nullptr;
        }

        if(piece->IsPromoted())
        {
            try {
                moveOptions[2] = std::make_unique<Coordinates>(pieceCoordinates.Row() - 2, pieceCoordinates.Column() - 2);
            }
            catch(std::out_of_range& exception) {
                moveOptions[2] = nullptr;
            }

            try {
                moveOptions[3] = std::make_unique<Coordinates>(pieceCoordinates.Row() - 2, pieceCoordinates.Column() + 2);
            }
            catch(std::out_of_range& exception) {
                moveOptions[3] = nullptr;
            }
        }

        for(auto& moveOption : moveOptions)
        {
            if(moveOption && CheckCapturePossibility(piece, piecesPlacement, moveOption->Row(), moveOption->Column()))
            {
                return true;
            }
        }
    }

    return false;
}

bool Logic::CheckPromotion(const Piece* piece)
{
    const Player piecePlayer = piece->GetPlayer();
    const Coordinates pieceCoordinates(piece->Row(), piece->Column());

    if(piecePlayer == Player::Down)
    {
        //Movement up is permitted

        if(pieceCoordinates.Row() == 1)
        {
            qDebug("Promotion");
            return true;
        }
    }
    else if(piecePlayer == Player::Up)
    {
        //Movement down is permitted
        if(pieceCoordinates.Row() == 8)
        {
            qDebug("Promotion");
            return true;
        }
    }
    else
    {
        assert(false);
    }

    return false;
}
