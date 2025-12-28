#pragma once

#include "../abstract_state.h"

class RunningState : public AbstractState
{
public:
    RunningState() : AbstractState("RunningState", GameStateType::Running)
    {}

    void entered() override
    {
        stateActions_->enablePiecesAnimation();
        stateActions_->startGameLoop();

        qInfo() << "=========================Game started=========================";
    }

    void exited() override
    {
        stateActions_->disablePiecesAnimation();
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
                // stateActions_->processPacmanDirectionKeyPress(Direction::LEFT);
                break;

            case Qt::Key_Right:
            case Qt::Key_D:
                // stateActions_->processPacmanDirectionKeyPress(Direction::RIGHT);
                break;

            case Qt::Key_Up:
            case Qt::Key_W:
                // stateActions_->processPacmanDirectionKeyPress(Direction::UP);
                break;

            case Qt::Key_Down:
            case Qt::Key_S:
                // stateActions_->processPacmanDirectionKeyPress(Direction::DOWN);
                break;

            case Qt::Key_Escape:
                stateActions_->setGameState(GameStateType::EscapeMenu);
                break;

            default:
                break;
        }
    }
};
