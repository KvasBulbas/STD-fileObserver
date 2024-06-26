#include "filebrowserdatamodel.h"
#include <QDebug>


FileBrowserDataModel::FileBrowserDataModel(QObject *parent, QVector<TableItem> dt)
    : QAbstractTableModel(parent)
{
    dataModel = dt;
}

FileBrowserDataModel::~FileBrowserDataModel()
{

}

int FileBrowserDataModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return dataModel.count();
}

int FileBrowserDataModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return PERCENT + 1;
}

QVariant FileBrowserDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{

    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    if (orientation == Qt::Vertical) {
        return section;
    }

    switch (section) {
    case NAME:
        return ("Name");
    case SIZE:
        return ("Size");
    case PERCENT:
        return ("Percent");
    }

    return QVariant();
}

QVariant FileBrowserDataModel::data(const QModelIndex &index, int role) const
{

    if (!index.isValid() || dataModel.count() <= index.row() || (role != Qt::DisplayRole && role != Qt::EditRole))
    {
        return QVariant();
    }


    if (index.column() == 0) {
        return dataModel[index.row()].itemName;
    } else if (index.column() == 1) {
        return dataModel[index.row()].itemSize;
    }else if (index.column() == 2) {

        long long total = 0;

        for(int i = 0; i < dataModel.size(); i++)
            total += dataModel[i].itemSize;

        return QString::number((double)dataModel[index.row()].itemSize/total*100) + "%";
    }

    return QVariant();
}

void FileBrowserDataModel::updateData(const QVector<TableItem>& newData)
{
    dataModel = newData;
    layoutChanged();
}






