#pragma once

#include "game_engine.h"
#include "common.h"

#include <QMainWindow>
#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class GameWindow;
}
QT_END_NAMESPACE

class GameWindow : public QMainWindow
{
Q_OBJECT

public:
    explicit GameWindow(GameEngine& gameEngine, QWidget* parent = nullptr);
    ~GameWindow() override;

private:
    void closeEvent(QCloseEvent*) override;

    void initializeGameplayAreaScene();
    void drawCheckerboard();
    void sceneUpdateSlot();

    Ui::GameWindow* ui_;
    QGraphicsScene scene_;
    GameEngine& gameEngine_;

private slots:
    void processNewGameButtonClickedSlot();
};
