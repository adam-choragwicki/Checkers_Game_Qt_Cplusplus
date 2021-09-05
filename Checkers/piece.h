#pragma once

#include "coordinates.h"
#include "player_manager.h"

#include <QGraphicsEllipseItem>

class Piece : public QGraphicsEllipseItem
{
    friend std::ostream& operator<<(std::ostream& os, const Piece* piece);

public:
    Piece(const Coordinates& coordinates, Player player, QGraphicsItem* parent=nullptr, bool promoted=false);

    int getColumn() const {return coordinates_.getColumn();}
    int getRow() const {return coordinates_.getRow();}
    const Coordinates& getCoordinates() const {return coordinates_;}
    Player getPlayer() const {return player_;}
    bool isMarkedActive() const {return markedActive_;}
    bool isMarkedMoveAvailable() const {return markedMoveAvailable_;}
    bool isPromoted() const {return promoted_;}

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

    static constexpr QColor blackPieceColor_{50, 50, 50};
    static constexpr QColor blackPieceOutlineColor_{0, 0, 0};
    static constexpr QColor redPieceColor_{220, 0, 0};
    static constexpr QColor redPieceOutlineColor_{170, 0, 0};
    static constexpr QColor activePieceOutlineColor_{255, 255, 255};
    static constexpr QColor movePossiblePieceOutlineColor_{255, 255, 0};

    Coordinates coordinates_;
    QGraphicsPolygonItem* crownGraphicsItem_ = nullptr;

    const int pieceOffsetX_ = 15;
    const int pieceOffsetY_ = 15;
    const int pieceSize_ = 50;
    const int pieceOutlineWidth_ = 5;

    const Player player_;
    bool markedActive_ = false;
    bool markedMoveAvailable_ = false;
    bool promoted_ = false;
};
