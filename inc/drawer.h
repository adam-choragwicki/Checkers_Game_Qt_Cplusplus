#pragma once

#include "checkerboard.h"

#include <QGraphicsScene>

class Drawer
{
public:
    Drawer() = delete;
    Drawer(const Drawer&) = delete;
    Drawer& operator=(Drawer&) = delete;
    Drawer(const Drawer&&) = delete;
    Drawer& operator=(Drawer&&) = delete;

    static void setScene(QGraphicsScene* scene) {scene_ = scene;}
    static void drawCheckerboard(Checkerboard& checkerboard);
    static void sceneUpdate();

private:
    static QGraphicsScene* scene_;
};
