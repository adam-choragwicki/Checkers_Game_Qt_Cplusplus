#pragma once

#include "../abstract_state.h"

class EndedVictoryNorthPlayerState : public AbstractState
{
public:
    explicit EndedVictoryNorthPlayerState(IStateActions& stateActions) : AbstractState("EndedVictoryNorthPlayerState", GameStateType::EndedVictoryNorthPlayer, stateActions)
    {}

    void entered() override
    {
        qDebug() << "Entered state: EndedVictoryNorthPlayer";
        stateActions_.showEndGameOverlay();
    }

    void exited() override
    {
        qDebug() << "Exited state: EndedVictoryNorthPlayer";
        stateActions_.hideEndGameOverlay();
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
