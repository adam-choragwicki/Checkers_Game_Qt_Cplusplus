#include "model.h"

Model::Model(const GameConfig& gameConfig) : pieceMovementAnimationManager_(gameConfig.PIECE_MOVEMENT_ANIMATION_DURATION_MS)
{
    piecesManager_ = std::make_unique<PiecesManager>(pieceStateManager_);
    piecesManager_->createPieces();

    piecesModel_ = std::make_unique<PiecesModel>(*piecesManager_);

    multiCaptureManager_ = std::make_unique<MultiCaptureManager>();
    playerManager_ = std::make_unique<PlayerManager>();
    moveInProgress_ = false;
}

void Model::reset()
{
    piecesManager_->reset();

    multiCaptureManager_->reset();
    playerManager_->reset();
    moveInProgress_ = false;

    pieceMovementAnimationManager_.reset();

    pieceStateManager_.reset();

    clearGameResultInfo();
}

QString Model::getWinningPlayerText() const
{
    if (gameResultInfo_)
    {
        return gameResultInfo_->winningPlayerText_;
    }

    return QString("NULL"); // safe default value. This is bound in QML property and cannot be just an empty optional
}

QString Model::getGameEndReasonText() const
{
    if (gameResultInfo_)
    {
        return gameResultInfo_->gameEndReasonText_;
    }

    return QString("NULL"); // safe default value. This is bound in QML property and cannot be just an empty optional
}

void Model::setGameResultInfo(const Player& winningPlayer, const QString& gameEndReasonText)
{
    const QString winningPlayerText = QStringLiteral("%1 PLAYER WINS!").arg(winningPlayer.getColor().toUpper());

    gameResultInfo_ = GameResultInfo{winningPlayerText, gameEndReasonText};

    emit gameResultInfoChanged();
}

void Model::clearGameResultInfo()
{
    gameResultInfo_.reset();
}
