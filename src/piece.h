#pragma once

#include "coordinates.h"
#include "player_manager.h"
#include <QObject>

class Piece : public QObject
{
    Q_OBJECT

    friend std::ostream& operator<<(std::ostream& os, const Piece& piece);

signals:
    void stateChanged();
    void startAnimatedMovement(const Coordinates& currentCoordinates, const Coordinates& newCoordinates);
    void promoted();

    void pieceChanged(int id);

public slots:
    void processEndMovement(const Coordinates& newCoordinates);

public:
    Piece(const Coordinates& coordinates, Player player, bool promoted = false);

    [[nodiscard]] int getColumn() const { return coordinates_.getColumn(); }

    [[nodiscard]] int getRow() const { return coordinates_.getRow(); }

    [[nodiscard]] const Coordinates& getCoordinates() const { return coordinates_; }

    [[nodiscard]] Player getPlayer() const { return player_; }

    [[nodiscard]] int getPlayerAsInt() const // TODO fix
    {
        return static_cast<int>(player_);
    }

    [[nodiscard]] bool isPromoted() const { return promoted_; }

    void moveToTile(const Coordinates& newCoordinates);
    void promote();

    [[nodiscard]] bool isDisabled() const;
    [[nodiscard]] bool isActive() const;
    [[nodiscard]] bool isSelected() const;

    void setDisabled();
    void setActive();
    void setSelected();

    [[nodiscard]] bool isAlive() const { return alive_; }
    void setAlive(const bool alive) { alive_ = alive; }

    int getId() const { return id_; }

    int getState() { return static_cast<int>(state_); }

    enum class State // TODO expose to QML
    {
        DISABLED = 1, ACTIVE = 2, SELECTED = 3
    } state_ = State::DISABLED;

    void setState(State newState);

private:
    Coordinates coordinates_;

    const Player player_;
    bool promoted_ = false;

    bool alive_ = true;

    inline static int counter_{};
    int id_{};
};
