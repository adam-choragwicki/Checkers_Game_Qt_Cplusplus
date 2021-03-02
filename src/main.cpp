#include "game.h"
#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication application(argc, argv);
    Game game;

    return QApplication::exec();
}

//TODO add shadows showing possible movements
//TODO get rid of Drawer class
//TODO implement state pattern for Piece state
//TODO optimize multi-capture manager
//TODO optimize player manager
//TODO encapsulate Model's move in progress boolean

//TODO add complete logging and fix subtle movement bugs
