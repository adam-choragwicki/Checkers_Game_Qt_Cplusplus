#include "pieces_manager.h"
#include "coordinates_database.h"
#include "piece_state_manager.h"

PiecesManager::PiecesManager()
{
    // TODO eventually the PiecesManager cannot create pieces in constructor (tests require piece manager to be empty)

    // Movement and capture testing
    // createPiece(Coordinates{6, 3}, SOUTH_PLAYER);
    // createPiece(Coordinates{4, 5}, NORTH_PLAYER);

    // Promotion testing
    // createPiece(Coordinates{2, 5}, SOUTH_PLAYER);
    // createPiece(Coordinates{7, 6}, NORTH_PLAYER);

    // Multi pieces testing 2 vs 2
    // createPiece(Coordinates{6, 3}, SOUTH_PLAYER);
    // createPiece(Coordinates{6, 5}, SOUTH_PLAYER);
    // createPiece(Coordinates{4, 3}, NORTH_PLAYER);
    // createPiece(Coordinates{4, 5}, NORTH_PLAYER);

    // Multi pieces testing 4 vs 4
    // createPiece(Coordinates{6, 1}, SOUTH_PLAYER);
    // createPiece(Coordinates{6, 3}, SOUTH_PLAYER);
    // createPiece(Coordinates{6, 5}, SOUTH_PLAYER);
    // createPiece(Coordinates{6, 7}, SOUTH_PLAYER);
    // createPiece(Coordinates{4, 1}, NORTH_PLAYER);
    // createPiece(Coordinates{4, 3}, NORTH_PLAYER);
    // createPiece(Coordinates{4, 5}, NORTH_PLAYER);
    // createPiece(Coordinates{4, 7}, NORTH_PLAYER);

    // Multi capture testing
    // createPiece(Coordinates{6, 3}, SOUTH_PLAYER);
    // createPiece(Coordinates{3, 4}, NORTH_PLAYER);
    // createPiece(Coordinates{5, 4}, NORTH_PLAYER);

    // End game testing 1 vs 1
    createPiece(Coordinates{5, 4}, SOUTH_PLAYER);
    createPiece(Coordinates{4, 5}, NORTH_PLAYER);
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

void PiecesManager::createPiece(const Coordinates& coordinates, const Player& player)
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

void PiecesManager::killPiece(Piece& piece)
{
    qDebug() << "Killing piece" << piece.getId() << "at" << piece.getCoordinates();
    piece.setAlive(false);
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

    placePieces(southPlayerStartingPiecesCoordinates, SOUTH_PLAYER);
    placePieces(northPlayerStartingPiecesCoordinates, NORTH_PLAYER);

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

size_t PiecesManager::countPlayerPieces(const Player& player) const
{
    return std::ranges::count_if(pieces_, [&player](const auto& piece)
    {
        return piece->getPlayer() == player && piece->isAlive();
    });
}

bool PiecesManager::didAnyPlayerRunOutOfPieces() const
{
    const size_t northPlayerPiecesCount = countPlayerPieces(NORTH_PLAYER);
    const size_t southPlayerPiecesCount = countPlayerPieces(SOUTH_PLAYER);

    qDebug() << NORTH_PLAYER.toString() << "has" << northPlayerPiecesCount << "pieces left";
    qDebug() << "SOUTH player has" << southPlayerPiecesCount << "pieces left";

    return northPlayerPiecesCount == 0 || southPlayerPiecesCount == 0;
}

const Player& PiecesManager::getPlayerWithNoPiecesLeft() const
{
    if (countPlayerPieces(SOUTH_PLAYER) == 0)
    {
        return SOUTH_PLAYER;
    }

    if (countPlayerPieces(NORTH_PLAYER) == 0)
    {
        return NORTH_PLAYER;
    }

    throw std::runtime_error("Error, both players have pieces left");
}
