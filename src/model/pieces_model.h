#pragma once

#include "../pieces_manager.h"
#include <QAbstractListModel>

class PiecesModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles { XRole = Qt::UserRole + 1, YRole, PlayerRole, AliveRole, IdRole, StateRole, AnimationEnabledRole, PromotedRole };

    explicit PiecesModel(const PiecesManager& piecesManager);

    // QAbstractItemModel interface
    [[nodiscard]] int rowCount(const QModelIndex& parent) const override;
    [[nodiscard]] QVariant data(const QModelIndex& index, int role) const override;
    [[nodiscard]] QHash<int, QByteArray> roleNames() const override;

    void pieceChanged(int index);

private:
    const PiecesManager& piecesManager_;
};
