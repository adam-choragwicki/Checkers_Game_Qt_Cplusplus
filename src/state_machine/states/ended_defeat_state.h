#pragma once

#include "../abstract_state.h"

class EndedDefeatState : public AbstractState
{
public:
    EndedDefeatState() : AbstractState("EndedDefeatState", GameStateType::EndedDefeat)
    {}

    void entered() override
    {
        qDebug() << "Entered state: EndedDefeat";
        stateActions_->showEndGameOverlay(GameResult::DEFEAT);
        stateActions_->stopGameLoop();
    }

    void exited() override
    {
        qDebug() << "Exited state: EndedDefeat";
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
