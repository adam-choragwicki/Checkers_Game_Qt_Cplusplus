#include "model.h"

Model::Model(const GameConfig& gameConfig)
{
    checkerboard_ = std::make_unique<Checkerboard>();

    piecesManager_ = std::make_unique<PiecesManager>();
    piecesModel_ = std::make_unique<PiecesModel>(*piecesManager_);

    piecesPlacement_ = std::make_unique<PiecesPlacement>();
    piecesPlacement_->createPieces();
    multiCaptureManager_ = std::make_unique<MultiCaptureManager>();
    playerManager_ = std::make_unique<PlayerManager>();
    moveInProgress_ = false;
}

void Model::reset()
{
    piecesPlacement_ = std::make_unique<PiecesPlacement>();
    piecesPlacement_->createPieces();
    multiCaptureManager_ = std::make_unique<MultiCaptureManager>();
    playerManager_ = std::make_unique<PlayerManager>();
    moveInProgress_ = false;
}
