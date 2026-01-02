#pragma once

#include "piece.h"

class MultiCaptureManager
{
public:
    MultiCaptureManager() = default;

    bool isMultiCaptureInProgress() const { return multiCapturingPiece_.has_value(); }
    void startMultiCapture(Piece& piece) { multiCapturingPiece_ = piece; }
    void endMultiCapture() { multiCapturingPiece_.reset(); }

    Piece& getMulticapturingPiece() const
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
