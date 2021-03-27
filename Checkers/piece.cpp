#include "piece.h"
#include <QPen>
#include <QGraphicsSceneMouseEvent>
#include <QApplication>
#include <chrono>
#include <thread>

Piece* Piece::m_ActivePiece = nullptr;

Piece::Piece(Coordinates coordinates, Player player, QGraphicsItem* parent) : QGraphicsEllipseItem(parent), m_Coordinates(coordinates.Row(), coordinates.Column()), m_Player(player)
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
    else
    {
        assert(false);
    }
}

void Piece::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if(event->button() == Qt::MouseButton::LeftButton)
    {
        //Allow selecting only marked pieces which have valid moves available
        if(m_Marked)
        {
            if(this->GetPlayer() == Common::GetActivePlayer())
            {
                if(m_ActivePiece != nullptr)
                {
                    m_ActivePiece->Unclicked();
                }
                this->SetActivePiecePointer();
                m_ActivePiece->Clicked();
            }
        }
    }
}

void Piece::Clicked()
{
    //qDebug("%s piece on (%d,%d)", __FUNCTION__, m_Coordinates.Row(), m_Coordinates.Column());
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

void Piece::SetActivePiecePointer()
{
    qDebug("%s", __FUNCTION__);
    m_ActivePiece = this;
}

void Piece::Promote()
{
    m_Promoted = true;

    const QList<QPoint> crownPolygonShapeCoordinates = {QPoint(0 , 0),
                                                        QPoint(6 , 8),
                                                        QPoint(12, 0),
                                                        QPoint(18, 8),
                                                        QPoint(23, 0),
                                                        QPoint(29, 8),
                                                        QPoint(34, 0),
                                                        QPoint(33, 20),
                                                        QPoint(2 , 20)};


    const int CROWN_OFFSET_X = 8;
    const int CROWN_OFFSET_Y = 15;

    QPolygon crown;

    for(int i = 0; i <= 8; i++)
    {
        crown << QPoint((m_Coordinates.Column() - 1) * Common::TILE_SIZE + PIECE_OFFSET_X + crownPolygonShapeCoordinates.at(i).x() + CROWN_OFFSET_X,
                        (m_Coordinates.Row() - 1) * Common::TILE_SIZE + PIECE_OFFSET_Y + crownPolygonShapeCoordinates.at(i).y() + CROWN_OFFSET_Y);
    }

    const QColor CROWN_COLOR(150, 150, 150);
    crownItem = new QGraphicsPolygonItem(crown, this);
    crownItem->setBrush(CROWN_COLOR);

    qDebug("Drawing crown on (%d,%d)", m_Coordinates.Row(), m_Coordinates.Column());
}

void Piece::ResetActivePiecePointer()
{
    qDebug("%s", __FUNCTION__);
    m_ActivePiece = nullptr;
}

void Piece::MarkActive()
{
    Clicked();
}

void Piece::MarkValidMoveAvailable()
{
    m_Marked = true;

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
    else
    {
        assert(false);
    }
}

void Piece::Unmark()
{
    m_Marked = false;

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
    else
    {
        assert(false);
    }
}

void Piece::MoveToTile(int row, int column)
{
    qDebug("%s=(%d,%d)", __FUNCTION__, row, column);

    /*Increase Z value so that piece is drawn over captured piece*/
    setZValue(1);

    Coordinates currentCoordinates(m_Coordinates.Row(), m_Coordinates.Column());
    Coordinates newCoordinates(row, column);

    AnimateFromCurrentToNewCoordinates(currentCoordinates, newCoordinates);

    Unclicked();
    ResetActivePiecePointer();

    /*Reset Z value*/
    setZValue(0);
}

void Piece::AnimateFromCurrentToNewCoordinates(Coordinates& currentCoordinates, Coordinates& newCoordinates)
{
    //qDebug("Before=(%.0f,%.0f)", this->rect().x(), this->rect().y());

    int rowDifference = (newCoordinates.Row() - currentCoordinates.Row());
    int columnDifference = (newCoordinates.Column() - currentCoordinates.Column());

    //double rowPixelDifference = (newCoordinates.Row() - currentCoordinates.Row()) * Common::TILE_SIZE;
    //double columnPixelDifference = (newCoordinates.Column() - currentCoordinates.Column()) * Common::TILE_SIZE;

    assert(abs(rowDifference) == abs(columnDifference));

    //qDebug("Row/Column difference=(%d,%d)", rowDifference, columnDifference);
    //qDebug("Row/Column pixel difference=(%.0f,%.0f)", rowPixelDifference, columnPixelDifference);

    double stepRow = 0;
    double stepColumn = 0;

    if(rowDifference < 0)
    {
        stepRow = -1;
    }
    else
    {
        stepRow = +1;
    }

    if(columnDifference < 0)
    {
        stepColumn = -1;
    }
    else
    {
        stepColumn = +1;
    }

    using namespace std::chrono_literals;

    const double factor = 5;

    const int limit = (abs(rowDifference) * Common::TILE_SIZE) / factor;

    for(int i = 0; i < limit; i++)
    {
        const QRectF newRect(QPointF(rect().topLeft().x() + factor * stepColumn, rect().topLeft().y() + factor * stepRow), rect().size());
        setRect(newRect);

        if(crownItem)
        {
            crownItem->moveBy(factor * stepColumn, factor * stepRow);
        }

        QApplication::processEvents();
        std::this_thread::sleep_for(1ms);
    }

    m_Coordinates.Modify(newCoordinates.Row(), newCoordinates.Column());

    //qDebug("After=(%.0f,%.0f)", this->rect().x(), this->rect().y());
}
