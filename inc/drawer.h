#pragma once

#include <QGraphicsScene>

class Drawer
{
public:
    Drawer() = delete;

    static void setScene(QGraphicsScene* scene) {scene_ = scene;}
    static void drawItem(QGraphicsItem* graphicsItem);
    static void eraseItem(QGraphicsItem* graphicsItem);

private:
    inline static QGraphicsScene* scene_ = nullptr;
};
