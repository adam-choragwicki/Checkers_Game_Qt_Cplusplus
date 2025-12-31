#include "pieces_manager.h"

#include "pieces_placement.h"
#include "coordinates_database.h"
#include "piece_state_manager.h"

PiecesManager::PiecesManager()
{
    // TODO eventually the PiecesManager cannot create pieces in constructor (tests require piece manager to be empty)

    // Movement and capture testing
    createPiece(Coordinates{6, 3}, Player::SOUTH);
    createPiece(Coordinates{4, 5}, Player::NORTH);

    // Promotion testing
    // createPiece(Coordinates{2, 5}, Player::SOUTH);
    // createPiece(Coordinates{7, 6}, Player::NORTH);

    // Multi pieces testing
    // createPiece(Coordinates{6, 3}, Player::SOUTH);
    // createPiece(Coordinates{6, 1}, Player::SOUTH);
    // createPiece(Coordinates{4, 5}, Player::NORTH);
    // createPiece(Coordinates{4, 3}, Player::NORTH);
}

void PiecesManager::reset()
{
    for (const auto& piece: pieces_)
    {
        qDebug() << "Resetting piece" << piece->getId();
        piece->reset();
    }
}

void PiecesManager::enablePiecesAnimations()
{
    for (const auto& piece: pieces_)
    {
        piece->setAnimationEnabled(true);
    }
}

void PiecesManager::disablePiecesAnimations()
{
    for (auto& piece: pieces_)
    {
        piece->setAnimationEnabled(false);
    }
}

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
        throw std::runtime_error("Error, piece is already present on given coordinates");
    }
}

void PiecesManager::disableAllPieces()
{
    for (const auto& piece: pieces_)
    {
        if (!piece->isDisabled())
        {
            PieceStateManager::disablePiece(*piece);
        }
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

    const std::set<Coordinates> southPlayerStartingPiecesCoordinates = CoordinatesDatabase::getInstance().getStartingPieceCoordinatesOfSouthPlayer();
    const std::set<Coordinates> northPlayerStartingPiecesCoordinates = CoordinatesDatabase::getInstance().getStartingPieceCoordinatesOfNorthPlayer();

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
        }
    };

    placePieces(southPlayerStartingPiecesCoordinates, Player::SOUTH);
    placePieces(northPlayerStartingPiecesCoordinates, Player::NORTH);

    qDebug() << "Created" << pieces_.size() << "pieces";
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
        // Consider a piece present at coordinates only if it is alive // TODO maybe go back to removing dead pieces?
        return piece->isAlive() && piece->getCoordinates() == coordinates;
    }) != pieces_.end();
}

Piece& PiecesManager::getPieceAtCoordinates(const Coordinates& coordinates) const
{
    if (isPieceAtCoordinates(coordinates))
    {
        const auto iter = std::ranges::find_if(pieces_, [coordinates](const std::unique_ptr<Piece>& piece)
        {
            // Only return alive piece
            return piece->isAlive() && piece->getCoordinates() == coordinates; // TODO maybe go back to removing dead pieces?
        });

        return *iter->get();
    }

    throw std::runtime_error("Error, no (alive) piece at given coordinates");
}

void PiecesManager::killPieceAtCoordinates(const Coordinates& coordinates)
{
    const auto iter = std::ranges::find_if(pieces_, [coordinates](const auto& piece)
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
        return piece->getPlayer() == player && piece->isAlive();
    });
}

bool PiecesManager::didAnyPlayerRunOutOfPieces() const
{
    const size_t northPlayerPiecesCount = countPlayerPieces(Player::NORTH);
    const size_t southPlayerPiecesCount = countPlayerPieces(Player::SOUTH);

    qDebug() << "NORTH player has" << northPlayerPiecesCount << "pieces left";
    qDebug() << "SOUTH player has" << southPlayerPiecesCount << "pieces left";

    return northPlayerPiecesCount == 0 || southPlayerPiecesCount == 0;
}

Player PiecesManager::getPlayerWithNoPiecesLeft() const
{
    if (countPlayerPieces(Player::SOUTH) == 0)
    {
        return Player::SOUTH;
    }

    if (countPlayerPieces(Player::NORTH) == 0)
    {
        return Player::NORTH;
    }

    throw std::runtime_error("Error, both players have pieces left");
}
