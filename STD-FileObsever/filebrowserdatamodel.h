#pragma once

#include <QAbstractTableModel>
#include "SizeCounting.h"

class FileBrowserDataModel : public QAbstractTableModel
{
    Q_OBJECT


public:
    FileBrowserDataModel(QObject *parent = nullptr, QVector<TableItem> dt = QVector<TableItem>());
    ~FileBrowserDataModel();

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;


public slots:
    void updateData(const QVector<TableItem>& newData);

private:
    enum NameColumn {
        NAME = 0,
        SIZE,
        PERCENT
    };

    QVector<TableItem> dataModel;
};
