#pragma once

#include "game_end_reason.h"
#include "coordinates.h"
#include "player_manager.h"
#include <set>

class CoordinatesDatabase
{
    class CoordinatesGenerator
    {
    public:
        static std::set<Coordinates> generatePlayableTilesCoordinates();
        static std::set<Coordinates> generateNonPlayableTilesCoordinates();
        static std::set<Coordinates> generateStartingPiecesCoordinates(Player player);
    };

public:
    static CoordinatesDatabase& getInstance()
    {
        static CoordinatesDatabase coordinatesDatabase;
        return coordinatesDatabase;
    }

    [[nodiscard]] const std::set<Coordinates>& getPlayableCoordinates() const
    { return playableCoordinates_; }

    [[nodiscard]] const std::set<Coordinates>& getNonPlayableCoordinates() const
    { return nonPlayableCoordinates_; }

    [[nodiscard]] const std::set<Coordinates>& getStartingPieceCoordinatesPlayerUpper() const
    { return startingPieceCoordinatesPlayerUp_; }

    [[nodiscard]] const std::set<Coordinates>& getStartingPieceCoordinatesPlayerLower() const
    { return startingPieceCoordinatesPlayerDown_; }

private:
    CoordinatesDatabase() :
            playableCoordinates_(CoordinatesGenerator::generatePlayableTilesCoordinates()),
            nonPlayableCoordinates_(CoordinatesGenerator::generateNonPlayableTilesCoordinates()),
            startingPieceCoordinatesPlayerUp_(CoordinatesGenerator::generateStartingPiecesCoordinates(Player::UPPER)),
            startingPieceCoordinatesPlayerDown_(CoordinatesGenerator::generateStartingPiecesCoordinates(Player::LOWER))
    {}

    const std::set<Coordinates> playableCoordinates_;
    const std::set<Coordinates> nonPlayableCoordinates_;
    const std::set<Coordinates> startingPieceCoordinatesPlayerUp_;
    const std::set<Coordinates> startingPieceCoordinatesPlayerDown_;
};
