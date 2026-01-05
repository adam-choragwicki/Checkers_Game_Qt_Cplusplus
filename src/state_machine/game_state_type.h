#pragma once

#include <QDebug>

enum class GameStateType
{
    Initialization, // App just started — loading assets, creating checkerboard, pieces etc.
    ReadyToStart, // Everything ready, waiting for the player's input to start.
    Running, // Game loop active.
    EscapeMenu, // Escape menu overlay is displayed.
    EndedVictoryNorthPlayer, // Game stopped because win conditions have been satisfied for northern player. The end game overlay is displayed.
    EndedVictorySouthPlayer, // Game stopped because win conditions have been satisfied for southern player. The end game overlay is displayed.
};

inline QDebug operator<<(QDebug debug, GameStateType state)
{
    QDebugStateSaver saver(debug);
    debug.nospace();

    switch (state)
    {
        case GameStateType::Initialization: return debug << "Initialization";
        case GameStateType::ReadyToStart: return debug << "ReadyToStart";
        case GameStateType::Running: return debug << "Running";
        case GameStateType::EscapeMenu: return debug << "EscapeMenu";
        case GameStateType::EndedVictoryNorthPlayer: return debug << "EndedVictoryNorthPlayer";
        case GameStateType::EndedVictorySouthPlayer: return debug << "EndedVictorySouthPlayer";

        default:
            qFatal() << "Unknown game state";
    }
}
