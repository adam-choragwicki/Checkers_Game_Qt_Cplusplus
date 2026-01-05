#include "pieces_manager.h"
#include "coordinates_database.h"
#include "piece_managers/piece_state_manager.h"

PiecesManager::PiecesManager(PieceStateManager& pieceStateManager) : pieceStateManager_(pieceStateManager)
{}

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
        // qDebug() << "Piece created at coordinates: " << coordinates;
    }
    else
    {
        qFatal() << "Error, piece is already present on given coordinates";
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
        pieceStateManager_.disablePiece(*piece);
    }
}

void PiecesManager::disableAllButOnePiece(const Piece& pieceToOmit)
{
    for (const auto& piece: pieces_)
    {
        if (piece.get() != &pieceToOmit)
        {
            pieceStateManager_.disablePiece(*piece);
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
                qFatal() << "Error, cannot place piece on non-playable tile";
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
        pieceStateManager_.activatePiece(*piece);
    }
}

bool PiecesManager::isPieceAtCoordinates(const Coordinates& coordinates) const
{
    return std::ranges::find_if(pieces_, [&coordinates](const auto& piece)
    {
        // Consider a piece present at coordinates only if it is alive
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
            return piece->isAlive() && piece->getCoordinates() == coordinates;
        });

        return *iter->get();
    }

    qFatal() << "Error, no (alive) piece at given coordinates";
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

    qFatal() << "Error, both players have pieces left";
}

void PiecesManager::loadVisualTestScenario()
{
    // Movement and capture testing 1 vs 1
    // createPiece(Coordinates{6, 3}, SOUTH_PLAYER);
    // createPiece(Coordinates{4, 5}, NORTH_PLAYER);

    // Movement and capture testing 2 vs 2
    // createPiece(Coordinates{6, 3}, SOUTH_PLAYER);
    // createPiece(Coordinates{6, 5}, SOUTH_PLAYER);
    // createPiece(Coordinates{4, 3}, NORTH_PLAYER);
    // createPiece(Coordinates{4, 5}, NORTH_PLAYER);

    // Animation testing
    // createPiece(Coordinates{6, 3}, SOUTH_PLAYER);
    // createPiece(Coordinates{6, 5}, SOUTH_PLAYER);
    // createPiece(Coordinates{4, 3}, NORTH_PLAYER);
    // createPiece(Coordinates{4, 5}, NORTH_PLAYER);

    // Z-position testing
    // createPiece(Coordinates{6, 3}, SOUTH_PLAYER);
    // createPiece(Coordinates{5, 4}, NORTH_PLAYER);
    // createPiece(Coordinates{3, 6}, NORTH_PLAYER);
    // createPiece(Coordinates{2, 7}, NORTH_PLAYER);

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
    // createPiece(Coordinates{8, 1}, SOUTH_PLAYER);
    // createPiece(Coordinates{7, 2}, NORTH_PLAYER);
    // createPiece(Coordinates{5, 4}, NORTH_PLAYER);
    // createPiece(Coordinates{3, 4}, NORTH_PLAYER);
    // createPiece(Coordinates{1, 8}, NORTH_PLAYER);

    // Multi capture + end game testing
    // createPiece(Coordinates{8, 1}, SOUTH_PLAYER);
    //
    // createPiece(Coordinates{7, 2}, NORTH_PLAYER);
    // createPiece(Coordinates{5, 4}, NORTH_PLAYER);
    // createPiece(Coordinates{3, 4}, NORTH_PLAYER);

    // End game testing 1 vs 1
    // createPiece(Coordinates{5, 4}, SOUTH_PLAYER);
    // createPiece(Coordinates{4, 5}, NORTH_PLAYER);

    // Backward capture is not allowed testing
    // createPiece(Coordinates{4, 5}, SOUTH_PLAYER);
    // createPiece(Coordinates{5, 4}, NORTH_PLAYER);
}
