#pragma once

#include <QObject>
#include <QTimer>

class PieceMovementAnimationManager : public QObject
{
    Q_OBJECT

signals:
    void pieceMovementAnimationDurationChanged();

public:
    explicit PieceMovementAnimationManager(const int pieceMovementAnimationDurationMs) : basicPieceMovementAnimationDurationMs_(pieceMovementAnimationDurationMs), doublePieceMovementAnimationDurationMs_(2 * pieceMovementAnimationDurationMs)
    {
        pieceMovementAnimationTimer_.setSingleShot(true);
    }

    void reset()
    {
        pieceMovementAnimationTimer_.stop();
    }

    void disconnect() const
    {
        pieceMovementAnimationTimer_.disconnect();
    }

    [[nodiscard]] QTimer& getPieceMovementAnimationTimer() { return pieceMovementAnimationTimer_; }

    Q_PROPERTY(int pieceMovementAnimationDurationMs READ getPieceMovementAnimationDurationMs NOTIFY pieceMovementAnimationDurationChanged)
    [[nodiscard]] int getPieceMovementAnimationDurationMs() const { return pieceMovementAnimationDurationMs_; }

    void setBasicPieceMovementAnimationDuration()
    {
        qDebug() << "ANIMATION_MANAGER: Setting basic animation duration for normal move";
        pieceMovementAnimationDurationMs_ = basicPieceMovementAnimationDurationMs_;
        pieceMovementAnimationTimer_.setInterval(pieceMovementAnimationDurationMs_);
        emit pieceMovementAnimationDurationChanged();
    }

    void setDoublePieceMovementAnimationDuration()
    {
        qDebug() << "ANIMATION_MANAGER: Setting double animation duration for capture";
        pieceMovementAnimationDurationMs_ = doublePieceMovementAnimationDurationMs_;
        pieceMovementAnimationTimer_.setInterval(pieceMovementAnimationDurationMs_);
        emit pieceMovementAnimationDurationChanged();
    }

private:
    const int basicPieceMovementAnimationDurationMs_;
    const int doublePieceMovementAnimationDurationMs_;

    int pieceMovementAnimationDurationMs_{};

    QTimer pieceMovementAnimationTimer_;
};
