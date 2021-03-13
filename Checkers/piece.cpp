#include "piece.h"
#include <QPen>
#include <QGraphicsSceneMouseEvent>

Piece* Piece::m_PieceCurrentlyChosen = nullptr;

Piece::Piece(std::pair<int, int>& coordinates, Player player) : m_Player(player)
{
    QGraphicsEllipseItem::setRect((coordinates.second - 1) * Common::TILE_SIZE + PIECE_OFFSET_X,
                                  (coordinates.first - 1) * Common::TILE_SIZE + PIECE_OFFSET_Y,
                                  PIECE_SIZE,
                                  PIECE_SIZE);

    row = coordinates.first;
    column = coordinates.second;

    if(m_Player == Player::Down)
    {
        setBrush(BLACK_PIECE_COLOR);
        setPen(QPen(QBrush(BLACK_PIECE_OUTLINE_COLOR), PIECE_OUTLINE_WIDTH));
    }
    else if(m_Player == Player::Up)
    {
        setBrush(RED_PIECE_COLOR);
        setPen(QPen(QBrush(RED_PIECE_OUTLINE_COLOR), PIECE_OUTLINE_WIDTH));
    }
}

void Piece::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if(event->button() == Qt::MouseButton::LeftButton)
    {
        if(m_PieceCurrentlyChosen != nullptr)
        {
            m_PieceCurrentlyChosen->Unclicked();
        }
        m_PieceCurrentlyChosen = this;
        m_PieceCurrentlyChosen->Clicked();
    }
}

void Piece::Clicked()
{
    setPen(QPen(QBrush(PIECE_CHOSEN_OUTLINE_COLOR), PIECE_OUTLINE_WIDTH));
}

void Piece::Unclicked()
{
    if(m_Player == Player::Down)
    {
        setBrush(BLACK_PIECE_COLOR);
        setPen(QPen(QBrush(BLACK_PIECE_OUTLINE_COLOR), PIECE_OUTLINE_WIDTH));
    }
    else if(m_Player == Player::Up)
    {
        setBrush(RED_PIECE_COLOR);
        setPen(QPen(QBrush(RED_PIECE_OUTLINE_COLOR), PIECE_OUTLINE_WIDTH));
    }
}
