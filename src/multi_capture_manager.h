#pragma once

#include "piece.h"

class MultiCaptureManager
{
public:
    MultiCaptureManager() = default;

    void reset()
    {
        multiCapturingPiece_.reset();
    }

    bool isMultiCaptureInProgress() const
    {
        return multiCapturingPiece_.has_value();
    }

    void startMultiCapture(Piece& piece)
    {
        qDebug() << "Starting multi capture";
        multiCapturingPiece_ = piece;
    }

    void endMultiCapture()
    {
        qDebug() << "Ending multi capture";
        multiCapturingPiece_.reset();
    }

    [[nodiscard]] Piece& getMulticapturingPiece() const
    {
        if (!multiCapturingPiece_)
        {
            qFatal("Error, getMulticapturingPiece() called with no multi-capture in progress");
        }

        return multiCapturingPiece_->get();
    }

private:
    std::optional<std::reference_wrapper<Piece>> multiCapturingPiece_;
};
