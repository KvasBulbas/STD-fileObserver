#ifndef MODELADAPTER_H
#define MODELADAPTER_H
#include "filebrowserdatamodel.h"
#include "chartcomponent.h"
#include <QDebug>
#include <QAbstractTableModel>

class ModelObserver : public QObject
{
    Q_OBJECT
public slots:
    virtual void update(QVector<TableItem> table) = 0;
    virtual FileBrowserDataModel* getModel() = 0;

};


class TableAdapter: public ModelObserver
{
    Q_OBJECT


public:
    TableAdapter(FileBrowserDataModel* listModel) : listModel(listModel){}

    FileBrowserDataModel* getModel() override
    {
        return listModel;
    }

    ~TableAdapter()
    {
        delete listModel;
    }

    operator FileBrowserDataModel*()
    {
        return listModel;
    }

public slots:
    void update(QVector<TableItem> table) override
    {
        qDebug() << "uprdate";
        listModel->updateData(table);
    }

private:
    FileBrowserDataModel* listModel;
};


class PieChartAdapter: public ModelObserver
{


private:
    FileBrowserDataModel* listModel;
};


#endif // MODELADAPTER_H
