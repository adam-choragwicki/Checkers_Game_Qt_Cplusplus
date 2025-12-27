#pragma once

#include "../abstract_state.h"

class ReadyToStartState : public AbstractState
{
public:
    ReadyToStartState() : AbstractState("ReadyToStartState", GameStateType::ReadyToStart)
    {}

    void entered() override
    {
        qDebug() << "Entered state: ReadyToStart";
        stateActions_->setGameState(GameStateType::Running); // TODO start game immediately, ready to start may not be needed in this game
    }

    void exited() override
    {
        qDebug() << "Exited state: ReadyToStart";
    }

    void transitionTo(AbstractState* newState) override
    {
        switch (newState->type())
        {
            case GameStateType::Running:
            case GameStateType::EscapeMenu:
                break;

            default:
                handleIllegalTransition(newState);
        }

        printTransition(newState);
    }

    void onKeyPress(const int key) override
    {
        constexpr bool logKeyPressed = false;

        if constexpr (logKeyPressed)
        {
            qDebug() << "ReadyToStartState::onKeyPress:" << key;
        }

        switch (key)
        {
            case Qt::Key_Space:
                if (logKeyPressed)
                    qDebug() << "Space pressed";
                stateActions_->setGameState(GameStateType::Running);
                break;

            case Qt::Key_Left:
            case Qt::Key_A:
                if (logKeyPressed)
                    qDebug() << "Left key pressed";
                stateActions_->setGameState(GameStateType::Running);
                // stateActions_->processPacmanDirectionKeyPress(Direction::LEFT);
                break;

            case Qt::Key_Right:
            case Qt::Key_D:
                if (logKeyPressed)
                    qDebug() << "Right key pressed";
                stateActions_->setGameState(GameStateType::Running);
                // stateActions_->processPacmanDirectionKeyPress(Direction::RIGHT);
                break;

            case Qt::Key_Up:
            case Qt::Key_W:
                if (logKeyPressed)
                    qDebug() << "Up key pressed";
                stateActions_->setGameState(GameStateType::Running);
                // stateActions_->processPacmanDirectionKeyPress(Direction::UP);
                break;

            case Qt::Key_Down:
            case Qt::Key_S:
                if (logKeyPressed)
                    qDebug() << "Down key pressed";
                stateActions_->setGameState(GameStateType::Running);
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
