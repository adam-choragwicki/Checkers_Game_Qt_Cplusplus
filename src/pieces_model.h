#pragma once

#include "pieces_manager.h"
#include <QAbstractListModel>

class PiecesModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles { XRole = Qt::UserRole + 1, YRole, PlayerRole, AliveRole, IdRole, StateRole };

    explicit PiecesModel(const PiecesManager& piecesManager);
    void refresh();

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
    virtual void brickChanged(int index); // TODO use as piece changed

    Q_INVOKABLE void pieceClicked(int pieceId);

private:
    const PiecesManager& piecesManager_;
};
