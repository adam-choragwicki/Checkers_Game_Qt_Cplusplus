#pragma once

#include "game_state_type.h"

class IStateActions
{
public:
    virtual ~IStateActions() = default;

    // Piece
    virtual void enablePiecesAnimation() = 0;
    virtual void disablePiecesAnimation() = 0;
    // Overlays
    virtual void showEscapeMenuOverlay() = 0;
    virtual void hideEscapeMenuOverlay() = 0;
    virtual void showEndGameOverlay() = 0;
    virtual void hideEndGameOverlay() = 0;

    // State transitions
    virtual void setGameState(GameStateType newType) = 0;
    virtual void restorePreviousState() = 0;
};
