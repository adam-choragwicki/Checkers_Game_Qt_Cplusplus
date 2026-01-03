#include "overlay_manager.h"
#include "qml_helper.h"

OverlayManager::OverlayManager(QmlHelper& qml_helper) : qmlHelper_(qml_helper), escapeMenuOverlay_(qmlHelper_.getOverlay(QmlOverlay::EscapeMenuOverlay)), endGameOverlay_(qmlHelper_.getOverlay(QmlOverlay::EndGameOverlay))
{}

void OverlayManager::showEscapeMenuOverlay()
{
    // qDebug() << "OverlayManager::showEscapeMenuOverlay()";
    escapeMenuOverlay_->setProperty("visible", true);
}

void OverlayManager::hideEscapeMenuOverlay()
{
    // qDebug() << "OverlayManager::hideEscapeMenuOverlay()";
    escapeMenuOverlay_->setProperty("visible", false);
}

void OverlayManager::showEndGameOverlay(const GameResult gameResult)
{
    const bool northPlayerVictory = gameResult == GameResult::NORTH_PLAYER_VICTORY;

    endGameOverlay_->setProperty("visible", true);
    endGameOverlay_->setProperty("message", northPlayerVictory ? "NORTH PLAYER WINS!" : "SOUTH PLAYER WINS!");
}

void OverlayManager::hideEndGameOverlay()
{
    endGameOverlay_->setProperty("visible", false);
    endGameOverlay_->setProperty("message", "NULL");
}
