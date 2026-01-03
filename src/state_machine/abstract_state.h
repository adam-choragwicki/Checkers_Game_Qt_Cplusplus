#pragma once

#include "game_state_type.h"
#include "i_state_actions.h"

class AbstractState
{
public:
    explicit AbstractState(QString name, const GameStateType type, IStateActions& stateActions) : name_(std::move(name)), type_(type), stateActions_(stateActions) {}

    virtual ~AbstractState() = default;

    virtual void entered() {}
    virtual void exited() {}
    virtual void transitionTo(AbstractState* abstract_state) = 0;

    virtual void onKeyPress(int key) {}

    [[nodiscard]] GameStateType type() const { return type_; }
    [[nodiscard]] const QString& getName() const { return name_; }

protected:
    void printTransition(AbstractState* newState) const
    {
        if constexpr (constexpr bool ENABLE_LOG_STATE_TRANSITIONS = true; ENABLE_LOG_STATE_TRANSITIONS)
        {
            qInfo().noquote() << "State changed:" << name_ << "->" << newState->getName();
        }
    }

    [[noreturn]] void handleIllegalTransition(AbstractState* newState) const
    {
        qFatal().noquote() << "Illegal transition:" << name_ << "->" << newState->getName();
        throw std::runtime_error("Illegal transition: " + name_.toStdString() + " -> " + newState->getName().toStdString());
    }

    QString name_;
    GameStateType type_;
    IStateActions& stateActions_;
};
