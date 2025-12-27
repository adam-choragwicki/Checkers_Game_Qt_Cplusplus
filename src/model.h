#pragma once

#include "pieces_placement.h"
#include "multi_capture_manager.h"
#include <memory>

#include "checkerboard.h"
#include "game_config.h"
#include "pieces_manager.h"
#include "pieces_model.h"

class Model
{
public:
    Model(const GameConfig& gameConfig);
    void reset();

    // [[nodiscard]] const PiecesPlacement& getPiecesPlacement() const
    // {
    //     return *piecesPlacement_;
    // }
    //
    // PiecesPlacement& getPiecesPlacement()
    // {
    //     return *piecesPlacement_;
    // }

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

    PiecesManager& getPiecesManager() { return *piecesManager_; }

    Q_PROPERTY(QObject* piecesModel READ getPiecesModel CONSTANT)
    [[nodiscard]] PiecesModel& getPiecesModel() const { return *piecesModel_; }
    // [[nodiscard]] StandardPelletsManager& getStandardPelletsManager() const { return *standardPelletsManager_; }

    // Checkerboard& getCheckerboard() const { return *checkerboard_; } // TODO remove because it was part of frontend

private:
    // std::unique_ptr<Checkerboard> checkerboard_; // TODO remove because it was part of frontend

    // std::unique_ptr<PiecesPlacement> piecesPlacement_;
    std::unique_ptr<MultiCaptureManager> multiCaptureManager_;
    std::unique_ptr<PlayerManager> playerManager_;
    bool moveInProgress_{};
    bool gameBeforeFirstRun_ = true;

    std::unique_ptr<PiecesManager> piecesManager_;
    std::unique_ptr<PiecesModel> piecesModel_;
};
