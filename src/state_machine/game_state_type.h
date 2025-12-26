#pragma once

#include <QDebug>

enum class GameStateType
{
    Initialization, // App just started — loading assets, creating an arena, pacman, ghosts, pellets, etc.
    ReadyToStart, // Everything ready, waiting for the player's input to start. The text overlay is displayed.
    Running, // Main game loop active.
    EscapeMenu, // Escape menu overlay is displayed.
    EndedVictory, // Game stopped because pacman ate all standard pellets. The end game overlay is displayed.
    EndedDefeat, // Game stopped because pacman collided with any ghost. The end game overlay is displayed.

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
        case GameStateType::EndedVictory: return debug << "EndedVictory";
        case GameStateType::EndedDefeat: return debug << "EndedDefeat";
        case GameStateType::PausedForDebug: return debug << "Paused (debug)";

        default:
            throw std::runtime_error("Unknown game state");
    }
}

// | From               | Action/Event                  | To                 | Notes                           |
// | :---------------   | :--------------------------   | :---------------   | :------------------------------ |
// | **Initialization** | load complete                 | **ReadyToStart**   | Start screen ready.             |
// | **ReadyToStart**   | Player presses arrow/WSAD key | **Running**        | Begin game loop.                |
// | **Running**        | Player presses *Esc*          | **EscapeMenu**     | Open escape menu.               |
// | **EscapeMenu**     | Select “RESUME”               | **Running**        | Return to play.                 |
// | **EscapeMenu**     | Select “QUIT”                 | **Exiting**        | Exit the game.                  |
// | **Running**        | Pacman ate all pellets        | **EndedVictory**   | Show end game overlay.          |
// | **Running**        | Pacman collided with ghost    | **EndedDefeat**    | Show end game overlay.          |
// | **Stopped**        | Player presses “PLAY AGAIN”   | **ReadyToStart**   | Restart game                    |
