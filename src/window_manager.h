#pragma once

#include <QQuickWindow>

class WindowManager
{
public:
    explicit WindowManager();

    void setWindow(QQuickWindow* window);

    [[nodiscard]] bool isStartInFullScreenEnabled() const { return startInFullScreenEnabled_; }

    void toggleFullScreen();

private:
    QWindow* window_{};

    const bool startInFullScreenEnabled_ = true;
};
