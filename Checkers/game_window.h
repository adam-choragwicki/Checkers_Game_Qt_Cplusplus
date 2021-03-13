#pragma once

#include <QMainWindow>
#include <QGraphicsScene>
#include "common.h"
#include "board.h"

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

    Board* m_pBoard = nullptr;

    void CreateAndPopulateBoard(QGraphicsScene& scene);
};
