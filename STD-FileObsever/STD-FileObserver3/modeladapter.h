#ifndef MODELADAPTER_H
#define MODELADAPTER_H
#include "filebrowserdatamodel.h"
#include <QDebug>

class ModelObserver : public QObject
{
    Q_OBJECT
public slots:
    virtual void update(QVector<TableItem> table) = 0;
    virtual FileBrowserDataModel* getModel() = 0;

};


class ListAdapter: public ModelObserver
{
    Q_OBJECT


public:
    ListAdapter(FileBrowserDataModel* listModel) : listModel(listModel)
    {
        //listModel = new FileBrowserDataModel();
    }

//    ListAdapter(const ListAdapter& listAdapter)
//    {
//        return listAdapter.listModel;
//    }

    FileBrowserDataModel* getModel() override
    {
        return listModel;
    }

    ~ListAdapter()
    {
        //delete listModel;
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


#endif // MODELADAPTER_H
