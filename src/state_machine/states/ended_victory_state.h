#pragma once

#include "../abstract_state.h"
#include "game_result.h"

class EndedVictoryState : public AbstractState
{
public:
    EndedVictoryState() : AbstractState("EndedVictoryState", GameStateType::EndedVictory)
    {}

    void entered() override
    {
        qDebug() << "Entered state: EndedVictory";
        stateActions_->showEndGameOverlay(GameResult::VICTORY);
        stateActions_->stopGameLoop();
    }

    void exited() override
    {
        qDebug() << "Exited state: EndedVictory";
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
