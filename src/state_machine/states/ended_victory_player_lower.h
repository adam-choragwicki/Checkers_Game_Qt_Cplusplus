#pragma once

#include "../abstract_state.h"
#include "game_result.h"

class EndedVictoryPlayerLowerState : public AbstractState
{
public:
    EndedVictoryPlayerLowerState() : AbstractState("EndedVictoryPlayerLowerState", GameStateType::EndedVictoryPlayerLower)
    {}

    void entered() override
    {
        qDebug() << "Entered state: EndedVictoryPlayerLower";
        stateActions_->showEndGameOverlay(GameResult::LOWER_PLAYER_VICTORY);
        stateActions_->stopGameLoop();
    }

    void exited() override
    {
        qDebug() << "Exited state: EndedVictoryPlayerLower";
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
