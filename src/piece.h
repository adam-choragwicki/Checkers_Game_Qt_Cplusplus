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

    void moveToTile(const Coordinates& coordinates);
    void promote();

    [[nodiscard]] bool isDisabled() const;
    [[nodiscard]] bool isActive() const;
    [[nodiscard]] bool isSelected() const;

    void setDisabled();
    void setActive();
    void setSelected();

    int x() const
    {
        return coordinates_.getColumn(); // TODO row or column?
    }

    int y() const
    {
        return coordinates_.getRow(); // TODO row or column?
    }

    [[nodiscard]] bool isAlive() const
    {
        return alive_;
    }

    int getId() const { return id_; }

private:
    enum class State
    {
        UNINITIALIZED, DISABLED, ACTIVE, SELECTED
    } state_ = State::UNINITIALIZED;

    void setState(State state);

    Coordinates coordinates_;

    const Player player_;
    bool promoted_ = false;

    bool alive_ = true;

    inline static int counter_{};
    int id_{};
};
