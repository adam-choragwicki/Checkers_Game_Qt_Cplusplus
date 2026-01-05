#pragma once

#include <QQmlApplicationEngine>
#include <QQuickWindow>

enum class QmlOverlay
{
    EndGameOverlay,
    EscapeMenuOverlay,
};

inline QString toString(const QmlOverlay overlay)
{
    switch (overlay)
    {
        case QmlOverlay::EndGameOverlay: return "endGameOverlay";
        case QmlOverlay::EscapeMenuOverlay: return "escapeMenuOverlay";
    }
    Q_UNREACHABLE();
}

class QmlHelper
{
public:
    explicit QmlHelper(QQmlApplicationEngine& view) : view_(view)
    {}

    QObject* getOverlay(QmlOverlay overlayEnum) const
    {
        QObject* root = getRootObject();

        auto overlay = root->findChild<QObject*>(toString(overlayEnum));
        if (!overlay)
        {
            qFatal() << QString("Overlay '%1' not found. It might not be defined in QML").arg(toString(overlayEnum));
        }

        return overlay;
    }

    QQuickWindow* getMainWindow() const
    {
        QObject* root = getRootObject();

        auto window = qobject_cast<QQuickWindow*>(root);

        if (!window)
        {
            qFatal() << "Root object is not a QQuickWindow";
        }

        return window;
    }

    QObject* getGameInput() const
    {
        QObject* root = getRootObject();

        auto gameInput = root->findChild<QObject*>("gameInput");

        if (!gameInput)
        {
            qFatal("gameInput not found");
        }

        return gameInput;
    }

private:
    QQmlApplicationEngine& view_;

    QObject* getRootObject() const
    {
        if (view_.rootObjects().isEmpty())
        {
            qFatal() << "Root object not found";
        }

        QObject* root = view_.rootObjects().first();
        if (!root)
        {
            qFatal() << "Root object is nullptr";
        }

        return root;
    }
};
