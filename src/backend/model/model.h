#pragma once

#include "pieces_placement.h"
#include "multi_capture_manager.h"
#include <memory>

class Model
{
public:
    Model();
    void reset();

    [[nodiscard]] const PiecesPlacement& getPiecesPlacement() const
    {
        return *piecesPlacement_;
    }

    PiecesPlacement& getPiecesPlacement()
    {
        return *piecesPlacement_;
    }

    [[nodiscard]] MultiCaptureManager& getMultiCaptureManager()
    {
        return *multiCaptureManager_;
    }

    [[nodiscard]] PlayerManager& getPlayerManager()
    {
        return *playerManager_;
    }

    [[nodiscard]] bool isMoveInProgress() const
    {
        return moveInProgress_;
    }

    void setMoveInProgress(bool moveInProgress)
    {
        moveInProgress_ = moveInProgress;
    }

    [[nodiscard]] bool isGameBeforeFirstRun() const
    {
        return gameBeforeFirstRun_;
    }

    void setGameBeforeFirstRun(bool beforeFirstRun)
    {
        gameBeforeFirstRun_ = beforeFirstRun;
    }

private:
    std::unique_ptr<PiecesPlacement> piecesPlacement_;
    std::unique_ptr<MultiCaptureManager> multiCaptureManager_;
    std::unique_ptr<PlayerManager> playerManager_;
    bool moveInProgress_{};
    bool gameBeforeFirstRun_ = true;
};
