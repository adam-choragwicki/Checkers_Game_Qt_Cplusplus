#pragma once

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
        static std::set<Coordinates> generateStartingPiecesCoordinates(const Player& player);
    };

public:
    static CoordinatesDatabase& getInstance()
    {
        static CoordinatesDatabase coordinatesDatabase;
        return coordinatesDatabase;
    }

    [[nodiscard]] const std::set<Coordinates>& getPlayableCoordinates() const { return playableCoordinates_; }
    [[nodiscard]] const std::set<Coordinates>& getNonPlayableCoordinates() const { return nonPlayableCoordinates_; }

    [[nodiscard]] const std::set<Coordinates>& getStartingPieceCoordinatesOfNorthPlayer() const { return startingPieceCoordinatesNorthPlayer_; }
    [[nodiscard]] const std::set<Coordinates>& getStartingPieceCoordinatesOfSouthPlayer() const { return startingPieceCoordinatesSouthPlayer_; }

private:
    CoordinatesDatabase() : playableCoordinates_(CoordinatesGenerator::generatePlayableTilesCoordinates()),
                            nonPlayableCoordinates_(CoordinatesGenerator::generateNonPlayableTilesCoordinates()),
                            startingPieceCoordinatesNorthPlayer_(CoordinatesGenerator::generateStartingPiecesCoordinates(NORTH_PLAYER)),
                            startingPieceCoordinatesSouthPlayer_(CoordinatesGenerator::generateStartingPiecesCoordinates(SOUTH_PLAYER))
    {}

    const std::set<Coordinates> playableCoordinates_;
    const std::set<Coordinates> nonPlayableCoordinates_;
    const std::set<Coordinates> startingPieceCoordinatesNorthPlayer_;
    const std::set<Coordinates> startingPieceCoordinatesSouthPlayer_;
};
