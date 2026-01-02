#pragma once

#include "pieces_placement.h"
#include "multi_capture_manager.h"
#include <memory>

#include "game_config.h"
#include "pieces_manager.h"
#include "pieces_model.h"

class Model : public QObject
{
    Q_OBJECT

signals:
    void gameEndReasonTextChanged();

public:
    explicit Model(const GameConfig& gameConfig);
    void reset();

    [[nodiscard]] MultiCaptureManager& getMultiCaptureManager() const { return *multiCaptureManager_; }

    [[nodiscard]] PlayerManager& getPlayerManager() const { return *playerManager_; }

    [[nodiscard]] bool isMoveInProgress() const { return moveInProgress_; }
    void setMoveInProgress(const bool moveInProgress) { moveInProgress_ = moveInProgress; }

    PiecesManager& getPiecesManager() const { return *piecesManager_; }

    Q_PROPERTY(QObject* piecesModel READ getPiecesModel CONSTANT)
    [[nodiscard]] QObject* getPiecesModel() const { return piecesModel_.get(); }

    void setGameEndReason(const QString& gameEndReasonText);

    Q_PROPERTY(QString gameEndReasonText READ getGameEndReasonText NOTIFY gameEndReasonTextChanged)
    QString getGameEndReasonText() const;

private:
    void clearGameEndReason();

    std::unique_ptr<MultiCaptureManager> multiCaptureManager_;
    std::unique_ptr<PlayerManager> playerManager_;
    bool moveInProgress_{};

    std::unique_ptr<PiecesManager> piecesManager_;
    std::unique_ptr<PiecesModel> piecesModel_;

    std::optional<QString> gameEndReasonText_;
};
