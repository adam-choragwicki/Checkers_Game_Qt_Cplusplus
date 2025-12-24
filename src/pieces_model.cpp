#include "pieces_model.h"

PiecesModel::PiecesModel(QObject* parent) : QAbstractListModel(parent)
{
}

void PiecesModel::refresh()
{
    beginResetModel();
    endResetModel();
}

int PiecesModel::rowCount(const QModelIndex&) const
{
    // return bricksManager_ ? static_cast <int>(bricksManager_->getBricks().size()) : 0;
}

QVariant PiecesModel::data(const QModelIndex& index, int role) const
{
    // const auto& brick = bricksManager_->getBricks().at(index.row());
    //
    // switch (role)
    // {
    //     case XRole: return brick.x();
    //     case YRole: return brick.y();
    //     case WidthRole: return brick.width();
    //     case HeightRole: return brick.height();
    //     case RadiusRole: return brick.radius();
    //     case ColorRole: return brick.color();
    //     case AliveRole: return brick.isAlive();
    // }
    //
    // return {};
}

QHash <int, QByteArray> PiecesModel::roleNames() const
{
    return {
            {XRole, "xRole"}, {YRole, "yRole"}, {AliveRole, "aliveRole"}
    };
}

void PiecesModel::brickChanged(const int index)
{
    QModelIndex idx = createIndex(index, 0);
    emit dataChanged(idx, idx, {AliveRole});
}
