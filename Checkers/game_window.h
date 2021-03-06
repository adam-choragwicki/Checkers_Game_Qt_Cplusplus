#pragma once

#include <QMainWindow>
#include <QGraphicsScene>
#include "common.h"

QT_BEGIN_NAMESPACE
namespace Ui { class GameWindow; }
QT_END_NAMESPACE

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

private:
    Ui::GameWindow *ui;

    QGraphicsScene m_Scene;
    QGraphicsRectItem* m_pBoard = nullptr;

    void DrawBoard();
    void PopulateBoard();
    std::vector<std::pair<int, int> > GenerateAllValidGameTilesCoordinates();
    std::vector<std::pair<int, int> > GenerateStartingPiecesCoordinates(PLAYER player);
};
