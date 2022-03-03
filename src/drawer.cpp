#include "drawer.h"

void Drawer::drawCheckerboard(Checkerboard& checkerboard)
{
    scene_->addItem(&checkerboard);
}

void Drawer::sceneUpdate()
{
    scene_->update();
}
