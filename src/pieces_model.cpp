#include "pieces_model.h"

PiecesModel::PiecesModel(const PiecesManager& piecesManager) : piecesManager_(piecesManager) {}

void PiecesModel::refresh()
{
    beginResetModel();
    endResetModel();
}

int PiecesModel::rowCount(const QModelIndex&) const
{
    return static_cast<int>(piecesManager_.getPieces().size());
}

QVariant PiecesModel::data(const QModelIndex& index, int role) const
{
    const auto& piece = piecesManager_.getPieces().at(index.row());

    switch (role)
    {
        case XRole: return piece->x();
        case YRole: return piece->getRow();
        case PlayerRole: return piece->getPlayerAsInt();
        case AliveRole: return piece->isAlive();
        case IdRole: return piece->getId();
        case StateRole: return piece->getState();
    }

    return {};
}

QHash<int, QByteArray> PiecesModel::roleNames() const
{
    return {
        {XRole, "xRole"}, {YRole, "yRole"}, {PlayerRole, "playerRole"}, {AliveRole, "aliveRole"}, {IdRole, "idRole"}, {StateRole, "stateRole"}
    };
}

void PiecesModel::brickChanged(const int index)
{
    QModelIndex idx = createIndex(index, 0);
    emit dataChanged(idx, idx, {AliveRole});
}
