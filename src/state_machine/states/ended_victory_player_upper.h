#pragma once

#include "../abstract_state.h"
#include "game_result.h"

class EndedVictoryPlayerUpperState : public AbstractState
{
public:
    EndedVictoryPlayerUpperState() : AbstractState("EndedVictoryPlayerUpperState", GameStateType::EndedVictoryPlayerUpper)
    {}

    void entered() override
    {
        qDebug() << "Entered state: EndedVictoryPlayerUpper";
        stateActions_->showEndGameOverlay(GameResult::UPPER_PLAYER_VICTORY);
        stateActions_->stopGameLoop();
    }

    void exited() override
    {
        qDebug() << "Exited state: EndedVictoryPlayerUpper";
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
