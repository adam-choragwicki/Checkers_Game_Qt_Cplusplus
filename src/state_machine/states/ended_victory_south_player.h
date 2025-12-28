#pragma once

#include "../abstract_state.h"
#include "game_result.h"

class EndedVictorySouthPlayerState : public AbstractState
{
public:
    EndedVictorySouthPlayerState() : AbstractState("EndedVictorySouthPlayerState", GameStateType::EndedVictorySouthPlayer)
    {}

    void entered() override
    {
        qDebug() << "Entered state: EndedVictorySouthPlayer";
        stateActions_->showEndGameOverlay(GameResult::SOUTH_PLAYER_VICTORY);
        stateActions_->stopGameLoop();
    }

    void exited() override
    {
        qDebug() << "Exited state: EndedVictorySouthPlayer";
        stateActions_->hideEndGameOverlay();
    }

    void transitionTo(AbstractState* newState) override
    {
        switch (newState->type())
        {
            case GameStateType::ReadyToStart:
                break;

            default:
                handleIllegalTransition(newState);
        }

        printTransition(newState);
    }
};
