#pragma once

#include "pieces_manager.h"
#include <QAbstractListModel>

class PiecesModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles { XRole = Qt::UserRole + 1, YRole, PlayerRole, AliveRole, IdRole, StateRole };

    explicit PiecesModel(const PiecesManager& piecesManager);

    // QAbstractItemModel interface
    int rowCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    void pieceChanged(int index);

    Q_INVOKABLE void pieceClicked(int pieceId);

private:
    const PiecesManager& piecesManager_;
};
