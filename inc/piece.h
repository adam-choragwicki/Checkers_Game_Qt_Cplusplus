#pragma once

#include "coordinates.h"
#include "player_manager.h"

#include <QGraphicsEllipseItem>

class Piece : public QGraphicsEllipseItem
{
    friend std::ostream& operator<<(std::ostream& os, const Piece* piece);

public:
    Piece(const Coordinates& coordinates, Player player, bool promoted=false);
    ~Piece() override;

    [[nodiscard]] int getColumn() const {return coordinates_.getColumn();}
    [[nodiscard]] int getRow() const {return coordinates_.getRow();}
    [[nodiscard]] const Coordinates& getCoordinates() const {return coordinates_;}
    [[nodiscard]] Player getPlayer() const {return player_;}
    [[nodiscard]] bool isMarkedActive() const {return markedActive_;}
    [[nodiscard]] bool isMarkedMoveAvailable() const {return markedMoveAvailable_;}
    [[nodiscard]] bool isPromoted() const {return promoted_;}

    void setActiveState(bool isActive);

    void markValidMoveAvailable();
    void moveToTile(const Coordinates& coordinates);
    void promote();
    void unmark();

private:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

    void clicked();
    void animateFromCurrentToNewCoordinates(const Coordinates& currentCoordinates, const Coordinates& newCoordinates);
    void updateColoursAccordingToState();



    Coordinates coordinates_;
    std::unique_ptr<QGraphicsPolygonItem> crownGraphicsItem_;

    const int pieceOffsetX_ = 15;
    const int pieceOffsetY_ = 15;
    const int pieceSize_ = 50;
    const int pieceOutlineWidth_ = 5;

    const Player player_;
    bool markedActive_ = false;
    bool markedMoveAvailable_ = false;
    bool promoted_ = false;
};
