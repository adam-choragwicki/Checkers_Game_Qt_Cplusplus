#include "piece.h"
#include "active_piece_manager.h"
#include "common.h"
#include "starting_coordinates_generator.h"
#include "drawer.h"

#include <QPen>
#include <QGraphicsSceneMouseEvent>
#include <QApplication>
#include <chrono>
#include <thread>

Piece::Piece(const Coordinates& coordinates, Player player, bool promoted) : coordinates_(coordinates), player_(player)
{
    QGraphicsEllipseItem::setRect(coordinates.getColumn() * GameParameters::tileSize + pieceOffsetX_,
                                  coordinates.getRow() * GameParameters::tileSize + pieceOffsetY_,
                                  pieceSize_,
                                  pieceSize_);

    QVector<Coordinates> playableTileCoordinates = StartingCoordinatesGenerator::generatePlayableTilesCoordinates();

    if(!playableTileCoordinates.contains(coordinates))
    {
        throw std::runtime_error("Trying to put piece on non-playable tile");
    }

    updateColoursAccordingToState();

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
        this->clicked();
    }
}

void Piece::clicked()
{
    if(markedMoveAvailable_)
    {
        /*Activate piece only if no other piece was active before AND it is current player's piece*/
        if(ActivePieceManager::getActivePiece() == nullptr && getPlayer() == PlayerManager::getActivePlayer())
        {
            setActiveState(true);
        }
        /*Activate piece if some other piece was active before AND it is current player's piece AND it is not the same piece*/
        else if(ActivePieceManager::getActivePiece() && getPlayer() == PlayerManager::getActivePlayer() && this != ActivePieceManager::getActivePiece())
        {
            ActivePieceManager::getActivePiece()->markValidMoveAvailable();
            ActivePieceManager::getActivePiece()->setActiveState(false);
            setActiveState(true);
        }
    }
}

void Piece::markValidMoveAvailable()
{
    markedMoveAvailable_ = true;
    updateColoursAccordingToState();
}

void Piece::unmark()
{
    markedActive_ = false;
    markedMoveAvailable_ = false;
    updateColoursAccordingToState();
}

void Piece::setActiveState(bool isActive)
{
    markedActive_ = isActive;

    if(isActive)
    {
        ActivePieceManager::setActivePiece(this);
    }
    else
    {
        ActivePieceManager::resetActivePiece();
    }

    updateColoursAccordingToState();
}

void Piece::moveToTile(const Coordinates& newCoordinates)
{
    /*Increase Z value so that piece is drawn over captured piece*/
    setZValue(1);

    animateFromCurrentToNewCoordinates(coordinates_, newCoordinates);

    /*Reset Z value*/
    setZValue(0);
}

void Piece::updateColoursAccordingToState()
{
    if(player_ == Player::down)
    {
        if(!markedActive_ && !markedMoveAvailable_)
        {
            setBrush(GameParameters::blackPieceColor_);
            setPen(QPen(QBrush(GameParameters::blackPieceOutlineColor_), pieceOutlineWidth_));
        }
        else if(markedActive_)
        {
            setPen(QPen(QBrush(GameParameters::activePieceOutlineColor_), pieceOutlineWidth_));
        }
        else if(markedMoveAvailable_)
        {
            setBrush(GameParameters::blackPieceColor_);
            setPen(QPen(QBrush(GameParameters::movePossiblePieceOutlineColor_), pieceOutlineWidth_));
        }
        else
        {
            throw std::runtime_error("Piece is in undefined state");
        }
    }
    else if(player_ == Player::up)
    {
        if(!markedActive_ && !markedMoveAvailable_)
        {
            setBrush(GameParameters::redPieceColor_);
            setPen(QPen(QBrush(GameParameters::redPieceOutlineColor_), pieceOutlineWidth_));
        }
        else if(markedActive_)
        {
            setPen(QPen(QBrush(GameParameters::activePieceOutlineColor_), pieceOutlineWidth_));
        }
        else if(markedMoveAvailable_)
        {
            setBrush(GameParameters::redPieceColor_);
            setPen(QPen(QBrush(GameParameters::movePossiblePieceOutlineColor_), pieceOutlineWidth_));
        }
        else
        {
            throw std::runtime_error("Piece is in undefined state");
        }
    }
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

    const QList<QPoint> crownPolygonShapeVerticesCoordinates = {QPoint(0, 0), QPoint(6, 8), QPoint(12, 0), QPoint(18, 8), QPoint(23, 0),
                                                                QPoint(29, 8), QPoint(34, 0), QPoint(33, 20), QPoint(2, 20)};

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
