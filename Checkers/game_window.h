#pragma once

#include <QMainWindow>
#include <QGraphicsScene>
#include "common.h"
#include "checkerboard.h"

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
    Ui::GameWindow* ui;

    QGraphicsScene m_Scene;

    std::unique_ptr<Checkerboard> m_pCheckerboard;

    void CreateAndPopulateBoard();
    void StartNewGame();
};
