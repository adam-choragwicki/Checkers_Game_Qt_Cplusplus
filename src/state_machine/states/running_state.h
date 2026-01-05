#pragma once

#include "../abstract_state.h"

class RunningState : public AbstractState
{
public:
    explicit RunningState(IStateActions& stateActions) : AbstractState("RunningState", GameStateType::Running, stateActions)
    {}

    void entered() override
    {
        stateActions_.enablePiecesAnimation();
    }

    void exited() override
    {
        stateActions_.disablePiecesAnimation();
    }

    void transitionTo(AbstractState* newState) override
    {
        switch (newState->type())
        {
            case GameStateType::EscapeMenu:
            case GameStateType::EndedVictoryNorthPlayer:
            case GameStateType::EndedVictorySouthPlayer:
                break;

            default:
                handleIllegalTransition(newState);
        }

        printTransition(newState);
    }

    void onKeyPress(const int key) override
    {
        switch (key)
        {
            case Qt::Key_Left:
            case Qt::Key_A:
                break;

            case Qt::Key_Right:
            case Qt::Key_D:
                break;

            case Qt::Key_Up:
            case Qt::Key_W:
                break;

            case Qt::Key_Down:
            case Qt::Key_S:
                break;

            case Qt::Key_Escape:
                stateActions_.setGameState(GameStateType::EscapeMenu);
                break;

            default:
                break;
        }
    }
};
