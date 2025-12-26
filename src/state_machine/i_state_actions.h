#pragma once

#include "game_state_type.h"

class IStateActions
{
public:
    virtual ~IStateActions() = default;

    // Game loop control
    virtual void startGameLoop() = 0;
    virtual void stopGameLoop() = 0;

    // Pacman
    // virtual void processPacmanDirectionKeyPress(const Direction& nextDirection) = 0;

    // Overlays
    virtual void showEscapeMenuOverlay() = 0;
    virtual void hideEscapeMenuOverlay() = 0;
    virtual void showEndGameOverlay(GameResult gameResult) = 0;
    virtual void hideEndGameOverlay() = 0;

    // State transitions
    virtual void setGameState(GameStateType newType) = 0;
    virtual void restorePreviousState() = 0;
};
