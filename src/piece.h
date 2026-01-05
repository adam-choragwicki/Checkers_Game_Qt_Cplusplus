#pragma once

#include "coordinates.h"
#include "player_manager.h"
#include <QMetaEnum>

class Piece : public QObject
{
    Q_OBJECT

    friend std::ostream& operator<<(std::ostream& os, const Piece& piece);

signals:
    void pieceChanged(int id);

public:
    Piece(const Coordinates& coordinates, const Player& player, bool promoted = false);
    void reset();

    [[nodiscard]] int getColumn() const { return coordinates_.getColumn(); }
    [[nodiscard]] int getRow() const { return coordinates_.getRow(); }

    [[nodiscard]] const Coordinates& getCoordinates() const { return coordinates_; }

    [[nodiscard]] const Player& getPlayer() const { return player_; }

    [[nodiscard]] int getPlayerAsInt() const { return player_.toInt(); }

    [[nodiscard]] bool isPromoted() const { return promoted_; }

    void moveToCoordinates(const Coordinates& newCoordinates);
    void promote();

    [[nodiscard]] bool isAlive() const { return alive_; }
    void setAlive(bool alive);

    int getId() const { return id_; }

    enum class State
    {
        DISABLED = 1, ACTIVE = 2, SELECTED = 3
    };

    Q_ENUM(State) // enables logging the state as string

    State getState() const { return state_; }
    void setState(State newState);

    [[nodiscard]] bool isAnimationEnabled() const { return animationEnabled_; }
    void setAnimationEnabled(bool enabled);

    bool operator==(const Piece& other) const;

private:
    const Coordinates STARTING_COORDINATES_;
    Coordinates coordinates_;

    const Player player_;
    bool promoted_ = false;

    bool alive_ = true;

    inline static int instanceCounter_{};
    int id_{};

    bool animationEnabled_{};

    State state_{State::DISABLED};
};
