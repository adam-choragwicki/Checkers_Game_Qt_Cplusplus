#include "crown.h"
#include "gui_config.h"
#include <QBrush>

Crown::Crown(QGraphicsItem* parent) : QGraphicsPolygonItem(parent)
{
    QPolygon crownPolygon;

    for(const auto& crownPolygonVertex : GuiConfig::Crown::POLYGON_SHAPE_VERTICES_COORDINATES)
    {
        crownPolygon.push_back(crownPolygonVertex);
    }

    setX(parentItem()->boundingRect().x() + GuiConfig::Crown::CROWN_OFFSET_X);
    setY(parentItem()->boundingRect().y() + GuiConfig::Crown::CROWN_OFFSET_Y);

    setPolygon(crownPolygon);
    setBrush(GuiConfig::Colors::CROWN);
}
