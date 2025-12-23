#pragma once

#include "piece.h"

class MultiCaptureManager
{
public:
    MultiCaptureManager() = default;
    bool isMultiCaptureInProgress() {return multiCapturingPiece_ != nullptr;}
    void startMultiCapture(Piece& piece) {multiCapturingPiece_ = &piece;}
    void endMultiCapture() {multiCapturingPiece_ = nullptr;}
    Piece* getMulticapturingPiece() {return multiCapturingPiece_;}

private:
    Piece* multiCapturingPiece_ = nullptr;
};
