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
        throw std::runtime_error("WindowManager::setWindow() called with nullptr");
    }
}

void WindowManager::toggleFullScreen()
{
    if (!window_)
    {
        throw std::runtime_error("WindowManager::toggleFullScreen() called before window was set");
    }

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
