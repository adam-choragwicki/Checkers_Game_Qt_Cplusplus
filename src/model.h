#pragma once

#include "multi_capture_manager.h"
#include "game_config.h"
#include "pieces_manager.h"
#include "pieces_model.h"
#include "game_result_info.h"
#include <memory>

class Model : public QObject
{
    Q_OBJECT

signals:
    void gameResultInfoChanged();

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

    void setGameResultInfo(const Player& winningPlayer, const QString& gameEndReasonText);

    Q_PROPERTY(QString winningPlayerText READ getWinningPlayerText NOTIFY gameResultInfoChanged)
    QString getWinningPlayerText() const;

    Q_PROPERTY(QString gameEndReasonText READ getGameEndReasonText NOTIFY gameResultInfoChanged)
    QString getGameEndReasonText() const;

private:
    void clearGameResultInfo();

    std::unique_ptr<MultiCaptureManager> multiCaptureManager_;
    std::unique_ptr<PlayerManager> playerManager_;
    bool moveInProgress_{};

    std::unique_ptr<PiecesManager> piecesManager_;
    std::unique_ptr<PiecesModel> piecesModel_;

    std::optional<GameResultInfo> gameResultInfo_;
};
