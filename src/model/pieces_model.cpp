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
        qFatal() << "Invalid index";
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
        case StateRole: return static_cast<int>(piece->getState());
        case AnimationEnabledRole: return piece->isAnimationEnabled();
        case PromotedRole: return piece->isPromoted();
        default: qFatal("Unknown role");
    }
}

QHash<int, QByteArray> PiecesModel::roleNames() const
{
    return {{XRole, "xRole"}, {YRole, "yRole"}, {PlayerRole, "playerRole"}, {AliveRole, "aliveRole"}, {IdRole, "idRole"}, {StateRole, "stateRole"}, {AnimationEnabledRole, "animationEnabledRole"}, {PromotedRole, "promotedRole"}};
}

void PiecesModel::pieceChanged(const int id)
{
    const auto& pieces = piecesManager_.getPieces();
    auto it = std::find_if(pieces.begin(), pieces.end(), [id](const std::unique_ptr<Piece>& p)
    {
        return p->getId() == id;
    });

    if (it == pieces.end())
    {
        qFatal() << "PiecesModel::pieceChanged: no piece with id" << id << "found";
    }

    const int row = static_cast<int>(std::distance(pieces.begin(), it));
    const QModelIndex idx = createIndex(row, 0);
    emit dataChanged(idx, idx);
}
