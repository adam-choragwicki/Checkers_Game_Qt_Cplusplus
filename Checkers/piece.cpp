#include "piece.h"
#include <QPen>
#include <QGraphicsSceneMouseEvent>

Piece* Piece::m_ActivePiece = nullptr;

Piece::Piece(Coordinates coordinates, Player player) : m_Coordinates(coordinates.Row(), coordinates.Column()), m_Player(player)
{
    QGraphicsEllipseItem::setRect((coordinates.Column() - 1) * Common::TILE_SIZE + PIECE_OFFSET_X,
                                  (coordinates.Row() - 1) * Common::TILE_SIZE + PIECE_OFFSET_Y,
                                  PIECE_SIZE,
                                  PIECE_SIZE);

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
        if(m_ActivePiece != nullptr)
        {
            m_ActivePiece->Unclicked();
        }
        m_ActivePiece = this;
        m_ActivePiece->Clicked();
    }
}

void Piece::Clicked()
{
    qDebug("%s piece on (%d,%d)", __FUNCTION__, m_Coordinates.Row(), m_Coordinates.Column());
    setPen(QPen(QBrush(ACTIVE_PIECE_OUTLINE_COLOR), PIECE_OUTLINE_WIDTH));
}

void Piece::Unclicked()
{
    qDebug("%s piece on (%d,%d)", __FUNCTION__, m_Coordinates.Row(), m_Coordinates.Column());

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

void Piece::ResetActivePiecePointer()
{
    qDebug("Clearing active piece pointer");
    m_ActivePiece = nullptr;
}

void Piece::Mark()
{
    if(m_Player == Player::Down)
    {
        setBrush(BLACK_PIECE_COLOR);
        setPen(QPen(QBrush(MOVE_POSSIBLE_PIECE_OUTLINE_COLOR), PIECE_OUTLINE_WIDTH));
    }
    else if(m_Player == Player::Up)
    {
        setBrush(RED_PIECE_COLOR);
        setPen(QPen(QBrush(MOVE_POSSIBLE_PIECE_OUTLINE_COLOR), PIECE_OUTLINE_WIDTH));
    }
}

void Piece::Unmark()
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

void Piece::MoveToTile(int row, int column)
{
    qDebug("%s=(%d,%d)", __FUNCTION__, row, column);

    m_Coordinates.Modify(row, column);

    QGraphicsEllipseItem::setRect((column - 1) * Common::TILE_SIZE + PIECE_OFFSET_X,
                                  (row - 1) * Common::TILE_SIZE + PIECE_OFFSET_Y,
                                  PIECE_SIZE,
                                  PIECE_SIZE);

    Unclicked();
    ResetActivePiecePointer();
}
