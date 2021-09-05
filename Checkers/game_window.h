#pragma once

#include "game_engine.h"
#include "common.h"

#include <QMainWindow>
#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
namespace Ui { class GameWindow; }
QT_END_NAMESPACE

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    GameWindow(QWidget* parent = nullptr);
    ~GameWindow();

private:
    void initializeGameplayAreaScene();
    void startNewGame();

    Ui::GameWindow* ui_;
    QGraphicsScene scene_;
    std::unique_ptr<GameEngine> gameEngine_;
};
