#include "model.h"
#include "game.h"

Model::Model(const GameConfig& gameConfig)
{
    piecesManager_ = std::make_unique<PiecesManager>();
    // piecesManager_->createPieces(); // TODO eventually restore this

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
