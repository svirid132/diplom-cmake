#include "n-model.h"

#include <QDebug>

NModel::NModel(QObject *parent)
    : QStringListModel{parent}
{

}


QVariant NModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::TextAlignmentRole) {
        return Qt::AlignHCenter;
    } else if (role == Qt::DisplayRole) {
        return QStringListModel::data(index, role);
    }

    return QVariant();
}

QVariant NModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Vertical) {
        return QVariant("");
    }

    if (role == Qt::TextAlignmentRole) {
        return Qt::AlignHCenter;
    } else if (role == Qt::DisplayRole) {
        return QVariant("N");
    }

    return QVariant();
}


Qt::ItemFlags NModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags itemFlags = QStringListModel::flags(index).setFlag(Qt::ItemIsEditable, false);
    itemFlags.setFlag(Qt::ItemIsSelectable, false);
    return itemFlags;
}
