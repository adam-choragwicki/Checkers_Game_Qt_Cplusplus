#include "game_window.h"

#include <QApplication>

int main(int argc, char* argv[])
{
    while(true)
    {
        QApplication application(argc, argv);
        GameWindow gameWindow;
        gameWindow.show();

        if(QApplication::exec() == static_cast<int>(Status::exit))
        {
            break;
        }
    }

    return 0;
}
