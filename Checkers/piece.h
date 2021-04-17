#pragma once

#include <QGraphicsEllipseItem>
#include "common.h"
#include "coordinates.h"

class Piece : public QGraphicsEllipseItem
{
public:
    Piece(Coordinates coordinates, Player player, QGraphicsItem* parent=nullptr, bool promoted=false);
    void MoveToTile(Coordinates coordinates);
    int Row() const {return m_Coordinates.Row();}
    int Column() const {return m_Coordinates.Column();}
    Coordinates& GetCoordinates() {return m_Coordinates;}
    Player GetPlayer() const {return m_Player;}
    bool IsMarkedActive() {return m_MarkedActive;}
    bool IsMarkedMoveAvailable() {return m_MarkedMoveAvailable;}
    void MarkValidMoveAvailable();
    void Unmark();
    void SetActive();
    void SetUnactive();
    void Promote();
    bool IsPromoted() const {return m_Promoted;}

    static Piece* GetActivePiece() {return m_ActivePiece;}
    static void MarkPiecesWhichCanMove(std::vector<Piece *> &pieces);

private:
    Coordinates m_Coordinates;
    QGraphicsPolygonItem* crownItem = nullptr;

    static Piece* m_ActivePiece;

    static const int PIECE_OFFSET_X = 15;
    static const int PIECE_OFFSET_Y = 15;
    static const int PIECE_SIZE = 50;
    static const int PIECE_OUTLINE_WIDTH = 5;

    static constexpr QColor BLACK_PIECE_COLOR{50, 50, 50};
    static constexpr QColor BLACK_PIECE_OUTLINE_COLOR{0, 0, 0};
    static constexpr QColor RED_PIECE_COLOR{220, 0, 0};
    static constexpr QColor RED_PIECE_OUTLINE_COLOR{170, 0, 0};
    static constexpr QColor ACTIVE_PIECE_OUTLINE_COLOR{255, 255, 255};
    static constexpr QColor MOVE_POSSIBLE_PIECE_OUTLINE_COLOR{255, 255, 0};

    const Player m_Player;
    bool m_MarkedActive = false;
    bool m_MarkedMoveAvailable = false;
    bool m_Promoted = false;

    void Clicked();
    void AnimateFromCurrentToNewCoordinates(Coordinates& currentCoordinates, Coordinates& newCoordinates);
    void UpdateColoursAccordingToState();
    void SetActivePiecePointer();
    void ClearActivePiecePointer();

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
};
