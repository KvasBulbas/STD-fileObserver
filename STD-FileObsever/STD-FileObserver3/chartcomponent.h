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
    void createChart(const QVector<TableItem>& table, QChart* chart)
    {
        if(chart)
        {
            addVisualization(chart);
            drawChart(table, chart);
        }
    }

protected:

    virtual void drawChart(const QVector<TableItem>& table, QChart* chart) = 0;
    virtual void addVisualization(QChart* chart);
};

class PieChartCreator : public ChartComponentCreator
{
    void drawChart(const QVector<TableItem>& table, QChart* chart) override;
};

class BarChartCreator : public ChartComponentCreator
{
    void drawChart(const QVector<TableItem>& table, QChart* chart) override;
};


#endif // CHARTCOMPONENT_H
