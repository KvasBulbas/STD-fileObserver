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

};


class TableAdapter: public ModelObserver
{
    Q_OBJECT


public:
    TableAdapter(FileBrowserDataModel* tableModel) : tableModel(tableModel){}

    FileBrowserDataModel* getModel()
    {
        return  tableModel;
    }

    ~TableAdapter()
    {
        delete tableModel;
    }

public slots:
    void update(QVector<TableItem> table) override
    {
        qDebug() << "table adapter update";
        tableModel->updateData(table);
    }

private:
    FileBrowserDataModel* tableModel;
};


class PieChartAdapter: public ModelObserver
{
    Q_OBJECT
public:
    PieChartAdapter(QChart* chart):chart(chart){}

    ~PieChartAdapter()
    {
        delete chart;
    }

    QChart* getModel()
    {
        return  chart;
    }

public slots:
    void update(QVector<TableItem> table) override
    {
        qDebug() << "pie chart adapter update";

        PieChartCreator pieCreator;
        pieCreator.createChart(table, chart);
    }

private:
    QChart* chart;

};

class BarChartAdapter: public ModelObserver
{
    Q_OBJECT
public:
    BarChartAdapter(QChart* chart):chart(chart){}

    ~BarChartAdapter()
    {
        delete chart;
    }

    QChart* getModel()
    {
        return  chart;
    }

public slots:
    void update(QVector<TableItem> table) override
    {
        qDebug() << "bar chart adapter update";

        BarChartCreator barCreator;
        barCreator.createChart(table, chart);
    }

private:
    QChart* chart;

};






#endif // MODELADAPTER_H
