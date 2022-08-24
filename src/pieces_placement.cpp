#include "pieces_placement.h"
#include "starting_coordinates_generator.h"

PiecesPlacement::~PiecesPlacement()
{
    for(Piece* piece : pieces_)
    {
        delete piece;
    }
}

void PiecesPlacement::createPiece(const Coordinates& coordinates, Player player)
{
    if(!isPieceAtCoordinates(coordinates))
    {
        pieces_.append(new Piece(coordinates, player));
    }
    else
    {
        throw std::runtime_error("Piece is already present on given coordinates");
    }
}

void PiecesPlacement::createAllPieces()
{
    QVector<Coordinates> playerLowerStartingPiecesCoordinates = StartingCoordinatesGenerator::generateStartingPiecesCoordinates(Player::down);
    QVector<Coordinates> playerUpperStartingPiecesCoordinates = StartingCoordinatesGenerator::generateStartingPiecesCoordinates(Player::up);

    QVector<Coordinates> playableTilesCoordinates = StartingCoordinatesGenerator::generatePlayableTilesCoordinates();

    auto placePieces = [this, &playableTilesCoordinates](const QVector<Coordinates>& piecesCoordinates, const Player& player)
    {
        for(auto& pieceCoordinates : piecesCoordinates)
        {
            if(playableTilesCoordinates.contains(pieceCoordinates))
            {
                createPiece(pieceCoordinates, player);
            }
            else
            {
                throw std::runtime_error("Cannot place piece on non-playable tile");
            }
        }
    };

    placePieces(playerLowerStartingPiecesCoordinates, Player::down);
    placePieces(playerUpperStartingPiecesCoordinates, Player::up);
}

void PiecesPlacement::markPiecesWhichCanMove(QVector<Piece*>& pieces)
{
    for(auto& piece : pieces)
    {
        piece->markValidMovePossible();
    }
}

bool PiecesPlacement::isPieceAtCoordinates(const Coordinates& coordinates) const
{
    return std::ranges::find_if(pieces_, [&coordinates](Piece* piece)
    {
        return piece->getCoordinates() == coordinates;
    }) != pieces_.end();
}

Piece* PiecesPlacement::getPieceAtCoordinates(const Coordinates& coordinates) const
{
    auto iter = std::ranges::find_if(pieces_, [&coordinates](Piece* piece)
    {
        return piece->getCoordinates() == coordinates;
    });

    if(iter != pieces_.end())
    {
        return *iter;
    }
    else
    {
        throw std::runtime_error("No piece at given coordinates");
    }
}

void PiecesPlacement::removePiece(Piece* piece)
{
    if(pieces_.contains(piece))
    {
        pieces_.remove(pieces_.indexOf(piece));
        delete piece;
    }
    else
    {
        throw std::runtime_error("Removing piece which is not present in pieces placement");
    }
}

void PiecesPlacement::removePieceAtCoordinates(const Coordinates& coordinates)
{
    Piece* piece = getPieceAtCoordinates(coordinates);
    removePiece(piece);
}

int PiecesPlacement::countPlayerPieces(Player player) const
{
    return std::ranges::count_if(pieces_, [&player](Piece* piece)
    {
        return piece->getPlayer() == player;
    });
}

bool PiecesPlacement::didAnyPlayerRunOutOfPieces() const
{
    return (countPlayerPieces(Player::down) == 0) || (countPlayerPieces(Player::up) == 0);
}

Player PiecesPlacement::getPlayerWithNoPiecesLeft() const
{
    if(countPlayerPieces(Player::down) == 0)
    {
        return Player::down;
    }
    else if(countPlayerPieces(Player::up) == 0)
    {
        return Player::up;
    }
    else
    {
        throw std::runtime_error("Both players have pieces left");
    }
}
