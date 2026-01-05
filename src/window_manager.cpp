#include "window_manager.h"
#include <QWindow>
#include <QDebug>

WindowManager::WindowManager()
{}

void WindowManager::setWindow(QQuickWindow* window)
{
    if (window)
    {
        window_ = window;
        // qDebug() << "WindowManager attached to QQuickWindow";
    }
    else
    {
        qFatal() << "WindowManager::setWindow() called with nullptr";
    }
}

void WindowManager::toggleFullScreen()
{
    if (window_)
    {
        const bool isCurrentlyFullscreen = window_->windowState() & Qt::WindowFullScreen;

        if (isCurrentlyFullscreen)
        {
            window_->showNormal();
            // qDebug() << "Exited fullscreen mode";
        }
        else
        {
            window_->showFullScreen();
            // qDebug() << "Entered fullscreen mode";
        }
    }
    else
    {
        qFatal() << "WindowManager::toggleFullScreen() called before window was set";
    }
}
