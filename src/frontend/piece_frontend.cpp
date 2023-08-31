#include "piece_frontend.h"
#include "gui_config.h"
#include "drawer.h"
#include "piece_state_manager.h"
#include <QEventLoop>

PieceFrontend::PieceFrontend(Piece& piece) : piece_(piece)
{
    setRect(piece_.getCoordinates().getColumn() * GuiConfig::Tile::SIZE + GuiConfig::Piece::OFFSET_X, piece_.getCoordinates().getRow() * GuiConfig::Tile::SIZE + GuiConfig::Piece::OFFSET_Y, GuiConfig::Piece::SIZE, GuiConfig::Piece::SIZE);

    animation_ = std::make_unique<QPropertyAnimation>(this, "pos", this);

    if(piece_.isPromoted())
    {
        addCrown();
    }

    Drawer::drawItem(this);
}

PieceFrontend::~PieceFrontend()
{
    Drawer::eraseItem(this);
}

void PieceFrontend::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if(event->button() == Qt::MouseButton::LeftButton)
    {
        if(piece_.isActive())
        {
            PieceStateManager::selectPiece(piece_);
        }
    }
}

void PieceFrontend::animateMovementToNewCoordinates(const Coordinates& currentCoordinates, const Coordinates& newCoordinates)
{
    setZValue(1);

    const int rowDifference = newCoordinates.getRow() - currentCoordinates.getRow();
    const int columnDifference = newCoordinates.getColumn() - currentCoordinates.getColumn();

    if(abs(rowDifference) != abs(columnDifference))
    {
        throw std::runtime_error("Error, wrong movement row/column difference: [" + std::to_string(rowDifference) + "," + std::to_string(columnDifference) + "]");
    }

    const int coordinatesDifferenceFactor = abs(rowDifference);

    if(coordinatesDifferenceFactor == 1)
    {
        animation_->setDuration(GuiConfig::Timing::ANIMATION_DURATION_MS);
    }
    else if(coordinatesDifferenceFactor == 2)
    {
        animation_->setDuration(2 * GuiConfig::Timing::ANIMATION_DURATION_MS);
    }

    const QPointF startPosition = pos();
    const QPointF destinationPosition = startPosition + QPointF(columnDifference * GuiConfig::Tile::SIZE, rowDifference * GuiConfig::Tile::SIZE);

    animation_->setStartValue(startPosition);
    animation_->setEndValue(destinationPosition);

    animation_->start();

    QEventLoop loop;
    connect(animation_.get(), &QPropertyAnimation::finished, &loop, &QEventLoop::quit);
    loop.exec();

    setZValue(0);

    emit endMovement(newCoordinates);
}

void PieceFrontend::updateColours()
{
    QPen pen;
    pen.setWidth(GuiConfig::Piece::OUTLINE_WIDTH);

    if(piece_.isDisabled())
    {
        if(piece_.getPlayer() == Player::LOWER)
        {
            pen.setBrush(GuiConfig::Colors::DISABLED_BLACK_PIECE_OUTLINE);
        }
        else
        {
            pen.setBrush(GuiConfig::Colors::DISABLED_RED_PIECE_OUTLINE);
        }
    }
    else if(piece_.isActive())
    {
        pen.setBrush(GuiConfig::Colors::ACTIVE_PIECE_OUTLINE);
    }
    else if(piece_.isSelected())
    {
        pen.setBrush(GuiConfig::Colors::SELECTED_PIECE_OUTLINE);
    }
    else
    {
        throw std::runtime_error("Error, piece is in unsupported state");
    }

    if(piece_.getPlayer() == Player::LOWER)
    {
        setBrush(GuiConfig::Colors::BLACK_PIECE);
    }
    else
    {
        setBrush(GuiConfig::Colors::RED_PIECE);
    }

    setPen(pen);
}

void PieceFrontend::addCrown()
{
    crown_ = std::make_unique<Crown>(this);
}
