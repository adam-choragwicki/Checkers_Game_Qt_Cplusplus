#pragma once

#include "game_result.h"
#include "qml_helper.h"

class OverlayManager
{
public:
    explicit OverlayManager(QmlHelper& qml_helper);

    void showEscapeMenuOverlay();
    void hideEscapeMenuOverlay();

    void showEndGameOverlay(GameResult gameResult);
    void hideEndGameOverlay();

private:
    QmlHelper& qmlHelper_;

    QObject* escapeMenuOverlay_{};
    QObject* endGameOverlay_{};
};
