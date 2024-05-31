#include "filebrowserdatamodel.h"
#include <QDebug>


FileBrowserDataModel::FileBrowserDataModel(QObject *parent, QVector<TableItem> dt)
    : QAbstractTableModel(parent)
{
    dataModel = dt;
}

FileBrowserDataModel::FileBrowserDataModel(QString dirPath, int strategy, QObject *parent) : QAbstractTableModel(parent)
{
    SizeCounter* counter = nullptr;
    switch (strategy) {
    case DIR_COUNTING:
        counter = new SizeCounter(new Directory_SizeCounting);
        break;
    case SUF_COUNTING:
        counter = new SizeCounter(new Suffix_SizeCounting);
        break;
    }

    if(counter)
    {
        dataModel = counter->sortTable(counter->count(dirPath));
        delete counter;
    }
}


int FileBrowserDataModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    //qDebug() << "rowCount";

    return dataModel.count();
}

int FileBrowserDataModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    //qDebug() << "columnCount";

    return PERCENT + 1;
}

QVariant FileBrowserDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    //qDebug() << "headerData1";

    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    //qDebug() << "headerData2";
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
    //qDebug() << "headerData3";

    return QVariant();
}

QVariant FileBrowserDataModel::data(const QModelIndex &index, int role) const
{
    //qDebug() << "data1";

    if (!index.isValid() || dataModel.count() <= index.row() || (role != Qt::DisplayRole && role != Qt::EditRole))
    {
        return QVariant();
    }

    //qDebug() << "data2";

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

