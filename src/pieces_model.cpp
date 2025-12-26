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
        default: qFatal("Unknown role");
    }
}

QHash<int, QByteArray> PiecesModel::roleNames() const
{
    return {
        {XRole, "xRole"}, {YRole, "yRole"}, {PlayerRole, "playerRole"}, {AliveRole, "aliveRole"}, {IdRole, "idRole"}, {StateRole, "stateRole"}
    };
}

void PiecesModel::brickChanged(const int index) // TODO use as piece changed
{
    const QModelIndex idx = createIndex(index, 0);
    emit dataChanged(idx, idx, {AliveRole});
}

void PiecesModel::pieceClicked(const int pieceId)
{
    if (auto* piece = piecesManager_.findPieceById(pieceId))
    {
        Q_ASSERT(pieceId == piece->getId());

        qDebug() << "C++: Piece" << pieceId << "clicked";

        if (piece->isActive())
        {
            qDebug() << "C++: Setting piece" << pieceId << "as selected";
            piece->setState(Piece::State::SELECTED);
        }
    }

    refresh(); // TODO this is quick hack ?, model should not be fully updated when only one piece is updated, or should it?
}
