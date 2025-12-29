#include "model.h"

Model::Model(const GameConfig& gameConfig)
{
    piecesManager_ = std::make_unique<PiecesManager>();
    piecesManager_->createPieces();

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
}
