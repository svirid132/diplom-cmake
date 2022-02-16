#ifndef NMODEL_H
#define NMODEL_H

#include <QStringListModel>

class NModel : public QStringListModel
{
public:
    explicit NModel(QObject *parent = nullptr);

    // QAbstractItemModel interface
public:
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    // QAbstractItemModel interface
public:
    Qt::ItemFlags flags(const QModelIndex &index) const;
};

#endif // NMODEL_H
