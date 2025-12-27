// #include "tile.h"
// #include "drawer.h"
// #include "gui_config.h"
// #include <QGraphicsSceneMouseEvent>
//
// Tile::Tile(const Coordinates& coordinates) : coordinates_(coordinates)
// {
//     setRect(coordinates_.getColumn() * GuiConfig::Tile::SIZE, coordinates_.getRow() * GuiConfig::Tile::SIZE, GuiConfig::Tile::SIZE, GuiConfig::Tile::SIZE);
//     setAcceptHoverEvents(true);
//
//     Drawer::drawItem(this);
// }
//
// Tile::~Tile()
// {
//     Drawer::eraseItem(this);
// }
//
// void Tile::hoverMoveEvent(QGraphicsSceneHoverEvent* event)
// {
//     setToolTip(QString::number(coordinates_.getRow()) + "," + QString::number(coordinates_.getColumn()));
// }
//
// NonPlayableTile::NonPlayableTile(const Coordinates& coordinates) : Tile(coordinates)
// {
//     setBrush(QBrush(GuiConfig::Colors::NON_PLAYABLE_TILE_COLOR));
//     setPen(QPen(brush().color()));
// }
//
// PlayableTile::PlayableTile(const Coordinates& coordinates) : Tile(coordinates)
// {
//     setBrush(QBrush(GuiConfig::Colors::PLAYABLE_TILE_COLOR));
//     setPen(QPen(brush().color()));
// }
//
// void PlayableTile::mousePressEvent(QGraphicsSceneMouseEvent* event)
// {
//     if(event->button() == Qt::MouseButton::LeftButton)
//     {
//         emit clickedSignal(coordinates_);
//     }
// }
