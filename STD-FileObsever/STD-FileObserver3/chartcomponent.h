#ifndef CHARTCOMPONENT_H
#define CHARTCOMPONENT_H

#include <QtCharts>
#include <QChart>
#include <QPieSeries>
#include <QChartView>
#include <QStackedBarSeries>
#include <SizeCounting.h>

class ChartComponentCreator
{
public:
    void createChart(QVector<TableItem> table, QChart* chart)
    {
        allocateChart(&chart);
        addVisualization(chart);
        drawChart(table, chart);
    }

protected:
    void allocateChart(QChart** chart)
    {
        if(!(*chart))
        {
            *chart = new QChart;
        }
    }

    virtual void drawChart(QVector<TableItem> table, QChart* chart) = 0;
    virtual void addVisualization(QChart* chart);
};

class PieChartCreator : public ChartComponentCreator
{
    void drawChart(QVector<TableItem> table, QChart* chart) override;
};

class BarChartCreator : public ChartComponentCreator
{
    void drawChart(QVector<TableItem> table, QChart* chart) override;
};


#endif // CHARTCOMPONENT_H
