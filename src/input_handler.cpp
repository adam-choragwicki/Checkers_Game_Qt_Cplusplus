#include "input_handler.h"
#include "controller.h"
#include "window_manager.h"

InputHandler::InputHandler(Controller& controller, WindowManager& windowManager) : controller_(controller), windowManager_(windowManager)
{}

void InputHandler::processKeyPress(const int key)
{
    constexpr bool logKeyPressed = false;

    if (logKeyPressed)
    {
        qDebug() << "InputHandler::onKeyPress:" << key;
    }

    switch (key)
    {
        case Qt::Key_Space:
            if (logKeyPressed) qDebug() << "Space pressed";
            controller_.getStateManager().handleKeyPress(key);
            break;

        case Qt::Key_Left:
        case Qt::Key_A:
            if (logKeyPressed) qDebug() << "Left key pressed";
            controller_.getStateManager().handleKeyPress(key);
            break;

        case Qt::Key_Right:
        case Qt::Key_D:
            if (logKeyPressed) qDebug() << "Right key pressed";
            controller_.getStateManager().handleKeyPress(key);
            break;

        case Qt::Key_Up:
        case Qt::Key_W:
            if (logKeyPressed) qDebug() << "Up key pressed";
            controller_.getStateManager().handleKeyPress(key);
            break;

        case Qt::Key_Down:
        case Qt::Key_S:
            if (logKeyPressed) qDebug() << "Down key pressed";
            controller_.getStateManager().handleKeyPress(key);
            break;

        case Qt::Key_Escape:
            if (logKeyPressed) qDebug() << "Escape key pressed";
            controller_.getStateManager().handleKeyPress(key);
            break;

        case Qt::Key_F11:
            if (logKeyPressed) qDebug() << "F11 key pressed";
            windowManager_.toggleFullScreen();
            break;

        default:
            if (logKeyPressed) qDebug() << "Unsupported key pressed";
            break;
    }
}
