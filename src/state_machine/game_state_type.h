#pragma once

#include <QDebug>

enum class GameStateType
{
    Initialization, // App just started — loading assets, creating checkerboard, pieces etc.
    ReadyToStart, // Everything ready, waiting for the player's input to start.
    Running, // Main game loop active.
    EscapeMenu, // Escape menu overlay is displayed.
    EndedVictoryPlayerUpper, // Game stopped because win conditions have been satisfied for player upper. The end game overlay is displayed.
    EndedVictoryPlayerLower, // Game stopped because win conditions have been satisfied for player lower. The end game overlay is displayed.
    PausedForDebug, // Game loop stopped; only for debug.
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
        case GameStateType::EndedVictoryPlayerUpper: return debug << "EndedVictoryPlayerUpper";
        case GameStateType::EndedVictoryPlayerLower: return debug << "EndedVictoryPlayerLower";
        case GameStateType::PausedForDebug: return debug << "Paused (debug)";

        default:
            throw std::runtime_error("Unknown game state");
    }
}

// | From               | Action/Event                  | To                 | Notes                           | // TODO update this
// | :---------------   | :--------------------------   | :---------------   | :------------------------------ |
// | **Initialization** | load complete                 | **ReadyToStart**   | Checkerboard and pieces ready.  |
// | **ReadyToStart**   | Player presses arrow/WSAD key | **Running**        | Begin game loop.                |
// | **Running**        | Player presses *Esc*          | **EscapeMenu**     | Open escape menu.               |
// | **EscapeMenu**     | Select “RESUME”               | **Running**        | Return to play.                 |
// | **EscapeMenu**     | Select “QUIT”                 | **Exiting**        | Exit the game.                  |
// | **Running**        | Pacman ate all pellets        | **EndedVictory**   | Show end game overlay.          |
// | **Running**        | Pacman collided with ghost    | **EndedDefeat**    | Show end game overlay.          |
// | **Stopped**        | Player presses “PLAY AGAIN”   | **ReadyToStart**   | Restart game                    |
