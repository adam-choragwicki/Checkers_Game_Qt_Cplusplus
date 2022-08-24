#include "piece.h"
#include "selected_piece_manager.h"
#include "common.h"
#include "drawer.h"

#include <QPen>
#include <QGraphicsSceneMouseEvent>
#include <QApplication>
#include <chrono>
#include <thread>

Piece::Piece(const Coordinates& coordinates, Player player, bool promoted) : coordinates_(coordinates), player_(player)
{
    QGraphicsEllipseItem::setRect(coordinates.getColumn() * GameParameters::tileSize + pieceOffsetX_, coordinates.getRow() * GameParameters::tileSize + pieceOffsetY_, pieceSize_, pieceSize_);

    setState(State::Disabled);

    if(promoted)
    {
        promote();
    }

    Drawer::drawItem(this);
}

Piece::~Piece()
{
    Drawer::eraseItem(this);
}

void Piece::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if(event->button() == Qt::MouseButton::LeftButton)
    {
        if(state_ == State::Active)
        {
            select();
        }
    }
}

void Piece::markValidMovePossible()
{
    setState(State::Active);
}

void Piece::disable()
{
    setState(State::Disabled);
}

void Piece::setState(State newState)
{
    if(state_ == State::Uninitialized)
    {
        if(newState == State::Disabled)
        {
            /* Piece initialization */
        }
        else
        {
            throw std::runtime_error("Unsupported piece state transition");
        }
    }
    else if(state_ == State::Disabled)
    {
        if(newState == State::Active)
        {
            /* New turn */
        }
        else if(newState == State::Disabled)
        {
            /* Do nothing */
        }
        else
        {
            throw std::runtime_error("Unsupported piece state transition");
        }
    }
    else if(state_ == State::Active)
    {
        if(newState == State::Selected)
        {
            SelectedPieceManager::switchSelectedPiece(this);
        }
        else if(newState == State::Disabled)
        {
            /* End turn */
        }
        else if(state_ == State::Active)
        {
            /* Do nothing */
        }
        else
        {
            throw std::runtime_error("Unsupported piece state transition");
        }
    }
    else if(state_ == State::Selected)
    {
        if(newState == State::Active)
        {
            /* Active piece clicked */
        }
        else if(newState == State::Disabled)
        {
            /* End turn */
            SelectedPieceManager::resetSelectedPiece();
        }
        else
        {
            throw std::runtime_error("Unsupported piece state transition");
        }
    }
    else
    {
        throw std::runtime_error("Piece is in unsupported state");
    }

    state_ = newState;
    updateColours();
}

void Piece::moveToTile(const Coordinates& newCoordinates)
{
    /*Increase Z value so that piece is drawn over captured piece*/
    setZValue(1);

    animateFromCurrentToNewCoordinates(coordinates_, newCoordinates);

    /*Reset Z value*/
    setZValue(0);
}

void Piece::updateColours()
{
    QPen pen;
    pen.setWidth(pieceOutlineWidth_);

    if(state_ == State::Disabled)
    {
        if(player_ == Player::down)
        {
            pen.setBrush(GameParameters::disabledBlackPieceOutlineColor_);
        }
        else
        {
            pen.setBrush(GameParameters::disabledRedPieceOutlineColor_);
        }
    }
    else if(state_ == State::Active)
    {
        pen.setBrush(GameParameters::activePieceOutlineColor_);
    }
    else if(state_ == State::Selected)
    {
        pen.setBrush(GameParameters::selectedPieceOutlineColor_);
    }
    else
    {
        throw std::runtime_error("Piece is in unsupported state");
    }

    if(player_ == Player::down)
    {
        setBrush(GameParameters::blackPieceColor_);
    }
    else
    {
        setBrush(GameParameters::redPieceColor_);
    }

    setPen(pen);
}

void Piece::animateFromCurrentToNewCoordinates(const Coordinates& currentCoordinates, const Coordinates& newCoordinates)
{
    int rowDifference = (newCoordinates.getRow() - currentCoordinates.getRow());
    int columnDifference = (newCoordinates.getColumn() - currentCoordinates.getColumn());

    double stepRow = rowDifference < 0 ? -1 : +1;
    double stepColumn = columnDifference < 0 ? -1 : +1;

    using namespace std::chrono_literals;

    const double factor = 5;

    const int limit = static_cast<int>((abs(rowDifference) * GameParameters::tileSize) / factor);

    for(int i = 0; i < limit; i++)
    {
        const QRectF newRect(QPointF(rect().topLeft().x() + factor * stepColumn, rect().topLeft().y() + factor * stepRow), rect().size());
        setRect(newRect);

        if(crownGraphicsItem_)
        {
            crownGraphicsItem_->moveBy(factor * stepColumn, factor * stepRow);
        }

        QApplication::processEvents();
        std::this_thread::sleep_for(10ms);
    }

    coordinates_ = newCoordinates;
}

void Piece::promote()
{
    promoted_ = true;

    const QList<QPoint> crownPolygonShapeVerticesCoordinates = {QPoint(0, 0), QPoint(6, 8), QPoint(12, 0), QPoint(18, 8), QPoint(23, 0), QPoint(29, 8), QPoint(34, 0), QPoint(33, 20), QPoint(2, 20)};

    const int crownOffsetX = 8;
    const int crownOffsetY = 15;

    QPolygon crown;

    for(const auto& crownPolygonVertex : crownPolygonShapeVerticesCoordinates)
    {
        crown.push_back({coordinates_.getColumn() * GameParameters::tileSize + pieceOffsetX_ + crownPolygonVertex.x() + crownOffsetX,
                         coordinates_.getRow() * GameParameters::tileSize + pieceOffsetY_ + crownPolygonVertex.y() + crownOffsetY});
    }

    crownGraphicsItem_ = std::make_unique<QGraphicsPolygonItem>(crown, this);
    crownGraphicsItem_->setBrush(GameParameters::crownColor);
}

std::ostream& operator<<(std::ostream& os, const Piece* piece)
{
    os << "(" << piece->getRow() << "," << piece->getColumn() << ")";
    return os;
}

void Piece::select()
{
    setState(State::Selected);
}

void Piece::deselect()
{
    setState(State::Active);
}
