#include "model.h"

Model::Model()
{
    reset();
}

void Model::reset()
{
    piecesPlacement_ = std::make_unique<PiecesPlacement>();
    piecesPlacement_->createPieces();
    multiCaptureManager_ = std::make_unique<MultiCaptureManager>();
    playerManager_ = std::make_unique<PlayerManager>();
    moveInProgress_ = false;
}
