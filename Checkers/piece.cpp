#include "piece.h"
#include <QPen>
#include <QGraphicsSceneMouseEvent>

Piece* Piece::m_CurrentlyChosenPiece = nullptr;

Piece::Piece(std::pair<int, int>& coordinates, Player player) : m_Player(player)
{
    QGraphicsEllipseItem::setRect((coordinates.second - 1) * Common::TILE_SIZE + PIECE_OFFSET_X,
                                  (coordinates.first - 1) * Common::TILE_SIZE + PIECE_OFFSET_Y,
                                  PIECE_SIZE,
                                  PIECE_SIZE);

    m_Row = coordinates.first;
    m_Column = coordinates.second;

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
        if(m_CurrentlyChosenPiece != nullptr)
        {
            m_CurrentlyChosenPiece->Unclicked();
        }
        m_CurrentlyChosenPiece = this;
        m_CurrentlyChosenPiece->Clicked();
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

void Piece::ResetCurrentlyChosenPiece()
{
    m_CurrentlyChosenPiece = nullptr;
}

void Piece::MoveToTile(int row, int column)
{
    qDebug("%s=(%d,%d)", __FUNCTION__, row, column);

    QGraphicsEllipseItem::setRect((column - 1) * Common::TILE_SIZE + PIECE_OFFSET_X,
                                  (row - 1) * Common::TILE_SIZE + PIECE_OFFSET_Y,
                                  PIECE_SIZE,
                                  PIECE_SIZE);

    Unclicked();
    ResetCurrentlyChosenPiece();
}
