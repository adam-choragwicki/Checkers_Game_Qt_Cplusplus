#pragma once

#include "../model/model.h"
#include "../common.h"
#include "tile.h"
#include "checkerboard.h"
#include "piece_frontend.h"
#include <QMainWindow>
#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
Q_OBJECT

signals:
    void newGameRequest();
    void applicationTerminationRequest();

public slots:
    void sceneUpdateSlot();

public:
    explicit MainWindow(const Model& model);
    ~MainWindow() override;

    void reset();

    [[nodiscard]] std::vector<PlayableTile*> getPlayableTiles() const;
    [[nodiscard]] std::vector<PieceFrontend*> getPiecesFrontends() const;

    void updatePiecesFrontends();
    void removePieceFrontendAtCoordinates(const Coordinates& coordinates);

    void showEndGameDialog(Player losingPlayer, GameEndReason gameEndReason);

private:
    void closeEvent(QCloseEvent*) override;

    void initializeGameplayAreaScene();
    void centerOnScreen(QScreen* screen);
    void centerOnPrimaryScreen();

    Ui::MainWindow* ui_;
    QGraphicsScene scene_;
    std::unique_ptr<Checkerboard> checkerboard_;

    std::vector<std::unique_ptr<PieceFrontend>> piecesFrontends_;

    const Model& model_;
};
