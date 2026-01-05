#pragma once

#include <QObject>
#include <QTimer>

class PieceMovementAnimationManager : public QObject
{
    Q_OBJECT

signals:
    void pieceMovementAnimationDurationMsChanged();

public:
    explicit PieceMovementAnimationManager(const int pieceMovementAnimationDurationMs) : basicPieceMovementAnimationDurationMs_(pieceMovementAnimationDurationMs), doublePieceMovementAnimationDurationMs_(2 * pieceMovementAnimationDurationMs),
                                                                                         pieceMovementAnimationDurationMs_(pieceMovementAnimationDurationMs)
    {
        pieceMovementAnimationTimer_.setSingleShot(true);
        pieceMovementAnimationTimer_.setInterval(pieceMovementAnimationDurationMs_);
    }

    void reset()
    {
        if (animationFinishedConnection_)
        {
            disconnect(animationFinishedConnection_);
        }

        pieceMovementAnimationTimer_.stop();
    }

    void start(std::function<void()> onFinished)
    {
        disconnect(animationFinishedConnection_);
        animationFinishedConnection_ = connect(&pieceMovementAnimationTimer_, &QTimer::timeout, this, std::move(onFinished));
        pieceMovementAnimationTimer_.start();
    }

    Q_PROPERTY(int pieceMovementAnimationDurationMs READ getPieceMovementAnimationDurationMs NOTIFY pieceMovementAnimationDurationMsChanged)
    [[nodiscard]] int getPieceMovementAnimationDurationMs() const { return pieceMovementAnimationDurationMs_; }

    void setBasicPieceMovementAnimationDuration()
    {
        qDebug() << "ANIMATION_MANAGER: Setting basic animation duration for normal move";
        pieceMovementAnimationDurationMs_ = basicPieceMovementAnimationDurationMs_;
        pieceMovementAnimationTimer_.setInterval(pieceMovementAnimationDurationMs_);
        emit pieceMovementAnimationDurationMsChanged();
    }

    void setDoublePieceMovementAnimationDuration()
    {
        qDebug() << "ANIMATION_MANAGER: Setting double animation duration for capture";
        pieceMovementAnimationDurationMs_ = doublePieceMovementAnimationDurationMs_;
        pieceMovementAnimationTimer_.setInterval(pieceMovementAnimationDurationMs_);
        emit pieceMovementAnimationDurationMsChanged();
    }

private:
    const int basicPieceMovementAnimationDurationMs_;
    const int doublePieceMovementAnimationDurationMs_;

    int pieceMovementAnimationDurationMs_;

    QMetaObject::Connection animationFinishedConnection_;
    QTimer pieceMovementAnimationTimer_;
};
