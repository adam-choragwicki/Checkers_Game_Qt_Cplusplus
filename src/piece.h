#pragma once

#include "coordinates.h"
#include "player_manager.h"
#include <QObject>

class Piece : public QObject
{
    Q_OBJECT

    friend std::ostream& operator<<(std::ostream& os, const Piece& piece);

signals:
    void pieceChanged(int id);

public:
    Piece(const Coordinates& coordinates, Player player, bool promoted = false);
    void reset();

    [[nodiscard]] int getColumn() const { return coordinates_.getColumn(); }
    [[nodiscard]] int getRow() const { return coordinates_.getRow(); }

    [[nodiscard]] const Coordinates& getCoordinates() const { return coordinates_; }

    [[nodiscard]] Player getPlayer() const { return player_; }

    [[nodiscard]] int getPlayerAsInt() const // TODO fix
    {
        return static_cast<int>(player_);
    }

    [[nodiscard]] bool isPromoted() const { return promoted_; }

    void moveToCoordinates(const Coordinates& newCoordinates);
    void promote();

    [[nodiscard]] bool isDisabled() const;
    [[nodiscard]] bool isActive() const;
    [[nodiscard]] bool isSelected() const;

    void setDisabled();
    void setActive();
    void setSelected();

    [[nodiscard]] bool isAlive() const { return alive_; }
    void setAlive(bool alive);

    int getId() const { return id_; }

    enum class State // TODO expose to QML
    {
        DISABLED = 1, ACTIVE = 2, SELECTED = 3
    };

    int getStateAsInt() { return static_cast<int>(state_); } // TODO expose state to QML?
    void setState(State newState);

    [[nodiscard]] bool isAnimationEnabled() const { return animationEnabled_; }
    void setAnimationEnabled(bool enabled);

private:
    const Coordinates STARTING_COORDINATES_;
    Coordinates coordinates_;

    const Player player_;
    bool promoted_ = false;

    bool alive_ = true;

    inline static int instanceCounter_{};
    int id_{};

    bool animationEnabled_{}; // TODO should it be in backend?

    State state_{State::DISABLED};
};
