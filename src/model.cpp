#include "model.h"

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

    multiCaptureManager_ = std::make_unique<MultiCaptureManager>();
    playerManager_ = std::make_unique<PlayerManager>();
    moveInProgress_ = false;

    clearGameEndReason();
}

void Model::setGameEndReason(const QString& gameEndReasonText)
{
    gameEndReasonText_ = gameEndReasonText;
    emit gameEndReasonTextChanged();
}

void Model::clearGameEndReason()
{
    gameEndReasonText_.reset();
}

QString Model::getGameEndReasonText() const
{
    if (gameEndReasonText_)
    {
        return *gameEndReasonText_;
    }

    return QString("NULL"); // safe default value. This is bound in QML property and cannot be just an empty optional
}
