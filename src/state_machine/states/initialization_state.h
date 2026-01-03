#pragma once

#include "../abstract_state.h"

class InitializationState : public AbstractState
{
public:
    explicit InitializationState(IStateActions& stateActions) : AbstractState("InitializationState", GameStateType::Initialization, stateActions)
    {}

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
