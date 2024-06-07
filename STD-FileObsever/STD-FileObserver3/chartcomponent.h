#ifndef CHARTCOMPONENT_H
#define CHARTCOMPONENT_H

#include <QtCharts>
#include <QChart>
#include <QPieSeries>
#include <QChartView>
#include <QStackedBarSeries>
#include <SizeCounting.h>

class ChartComponent
{
public:
    QChart* createChart(QVector<TableItem> table, QChart* chart = nullptr){
        allocateChart(&chart);
        drawChart(table, chart);
        drawLegend();
        if(chart)
            qDebug() << "chart not empty";
        return chart;
    }

protected:
    void allocateChart(QChart** chart)
    {
        qDebug() <<  "allocate";
        if(!(*chart))
        {
            qDebug() << "newChart";
            *chart = new QChart;
        }
    }

    virtual void drawChart(QVector<TableItem> table, QChart* chart) = 0;
    virtual void drawLegend(){}
};

class PieChart : public ChartComponent
{
    void drawChart(QVector<TableItem> table, QChart* chart) override;
};

class BarChart : public ChartComponent
{
    void drawChart(QVector<TableItem> table, QChart* chart) override;
};


#endif // CHARTCOMPONENT_H
