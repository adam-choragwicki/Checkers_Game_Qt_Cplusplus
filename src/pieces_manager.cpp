#include "pieces_manager.h"

#include "pieces_placement.h"
#include "coordinates_database.h"
#include "piece_state_manager.h"

void PiecesManager::createPiece(const Coordinates& coordinates, Player player)
{
    if (!isPieceAtCoordinates(coordinates))
    {
        pieces_.emplace_back(std::make_unique<Piece>(coordinates, player));
        // const auto& ref = pieces_.emplace_back(std::make_unique<Piece>(coordinates, player));
        // piecesModels_.push_back(std::make_unique<PieceModel>(*ref));

        // qDebug() << "Piece created at coordinates: " << coordinates;
    }
    else
    {
        throw std::runtime_error("Error, piece is already present on given coorrHdinates");
    }
}

Piece* PiecesManager::findPieceById(const int id) const
{
    for (const auto& piece: pieces_)
    {
        if (piece->getId() == id)
        {
            return piece.get();
        }
    }

    qFatal("Piece with id %d not found", id);
    throw std::runtime_error("Error, piece with given id not found");
}

void PiecesManager::createPieces()
{
    pieces_.reserve(24); // 24 pieces in total

    std::set<Coordinates> playerLowerStartingPiecesCoordinates = CoordinatesDatabase::getInstance().getStartingPieceCoordinatesPlayerLower();
    std::set<Coordinates> playerUpperStartingPiecesCoordinates = CoordinatesDatabase::getInstance().getStartingPieceCoordinatesPlayerUpper();

    std::set<Coordinates> playableTilesCoordinates = CoordinatesDatabase::getInstance().getPlayableCoordinates();

    auto placePieces = [this, &playableTilesCoordinates](const std::set<Coordinates>& piecesCoordinates, const Player& player)
    {
        for (const auto& pieceCoordinates: piecesCoordinates)
        {
            if (playableTilesCoordinates.contains(pieceCoordinates))
            {
                createPiece(pieceCoordinates, player);
            }
            else
            {
                throw std::runtime_error("Error, cannot place piece on non-playable tile");
            }

            return; // TODO temporary to just create one piece per player
        }
    };

    placePieces(playerLowerStartingPiecesCoordinates, Player::LOWER);
    placePieces(playerUpperStartingPiecesCoordinates, Player::UPPER);
}

void PiecesManager::markPiecesWhichCanMove(const std::vector<Piece*>& pieces)
{
    qDebug() << "Marking" << pieces.size() << "pieces which can move";

    for (auto& piece: pieces)
    {
        qDebug() << "Piece" << piece->getId() << "can move";
        PieceStateManager::markPieceHasValidMovePossible(*piece);
    }
}

bool PiecesManager::isPieceAtCoordinates(const Coordinates& coordinates) const
{
    return std::ranges::find_if(pieces_, [&coordinates](const auto& piece)
    {
        return piece->getCoordinates() == coordinates;
    }) != pieces_.end();
}

Piece& PiecesManager::getPieceAtCoordinates(const Coordinates& coordinates) const
{
    if (isPieceAtCoordinates(coordinates))
    {
        auto iter = std::find_if(pieces_.begin(), pieces_.end(), [coordinates](const std::unique_ptr<Piece>& piece)
        {
            return piece->getCoordinates() == coordinates;
        });

        return *(iter->get());
    }
    else
    {
        throw std::runtime_error("Error, no piece at given coordinates");
    }
}

void PiecesManager::killPieceAtCoordinates(const Coordinates& coordinates)
{
    auto iter = std::ranges::find_if(pieces_, [coordinates](const auto& piece)
    {
        return piece->getCoordinates() == coordinates;
    });

    if (iter != pieces_.end())
    {
        (*iter)->setAlive(false);
    }
    else
    {
        throw std::runtime_error("Error, trying to kill piece which is not present in pieces placement");
    }
}

size_t PiecesManager::countPlayerPieces(Player player) const
{
    return std::ranges::count_if(pieces_, [&player](const auto& piece)
    {
        return piece->getPlayer() == player;
    });
}

bool PiecesManager::didAnyPlayerRunOutOfPieces() const
{
    return (countPlayerPieces(Player::LOWER) == 0) || (countPlayerPieces(Player::UPPER) == 0);
}

Player PiecesManager::getPlayerWithNoPiecesLeft() const
{
    if (countPlayerPieces(Player::LOWER) == 0)
    {
        return Player::LOWER;
    }
    else if (countPlayerPieces(Player::UPPER) == 0)
    {
        return Player::UPPER;
    }
    else
    {
        throw std::runtime_error("Error, both players have pieces left");
    }
}
