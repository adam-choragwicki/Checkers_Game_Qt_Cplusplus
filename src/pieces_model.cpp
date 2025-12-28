#include "pieces_model.h"

PiecesModel::PiecesModel(const PiecesManager& piecesManager) : piecesManager_(piecesManager)
{
    for (const auto& piece: piecesManager_.getPieces())
    {
        connect(piece.get(), &Piece::pieceChanged, this, &PiecesModel::pieceChanged);
    }
}

int PiecesModel::rowCount(const QModelIndex&) const
{
    return static_cast<int>(piecesManager_.getPieces().size());
}

QVariant PiecesModel::data(const QModelIndex& index, const int role) const
{
    if (!index.isValid())
    {
        throw std::runtime_error("Invalid index");
    }

    // qDebug() << "C++: data called with model row" << index.row() << "and role" << role;

    const auto& piece = piecesManager_.getPieces().at(index.row());

    // qDebug() << "C++: piece" << piece->getId() << "at model row" << index.row();

    switch (role)
    {
        case XRole: return piece->getColumn();
        case YRole: return piece->getRow();
        case PlayerRole: return piece->getPlayerAsInt();
        case AliveRole: return piece->isAlive();
        case IdRole: return piece->getId();
        case StateRole: return piece->getStateAsInt();
        case AnimationEnabledRole: return piece->isAnimationEnabled();
        case PromotedRole: return piece->isPromoted();
        default: qFatal("Unknown role");
    }
}

QHash<int, QByteArray> PiecesModel::roleNames() const
{
    return {{XRole, "xRole"}, {YRole, "yRole"}, {PlayerRole, "playerRole"}, {AliveRole, "aliveRole"}, {IdRole, "idRole"}, {StateRole, "stateRole"}, {AnimationEnabledRole, "animationEnabledRole"}, {PromotedRole, "promotedRole"}};
}

void PiecesModel::pieceChanged(const int index)
{
    // qDebug() << "C++: Processing piece changed for piece: " << index;
    // qDebug() << "C++: Emitting dataChanged for piece: " << index;

    const QModelIndex idx = createIndex(index, 0);
    emit dataChanged(idx, idx);
}
