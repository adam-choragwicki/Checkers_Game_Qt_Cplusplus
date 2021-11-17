#include "drawer.h"

QGraphicsScene* Drawer::scene_ = nullptr;

void Drawer::drawCheckerboard(Checkerboard& checkerboard)
{
    scene_->addItem(&checkerboard);
}

void Drawer::sceneUpdate()
{
    scene_->update();
}
