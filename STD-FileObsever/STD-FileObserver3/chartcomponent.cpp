#include "chartcomponent.h"
#include <QFont>

void ChartComponentCreator::addVisualization(QChart* chart)
{
    QFont font = chart->legend()->font();
    font.setItalic(true);
    chart->legend()->setFont(font);

    chart->setTheme(QChart::ChartThemeHighContrast);
    chart->createDefaultAxes();
}

void PieChartCreator::drawChart(const QVector<TableItem>& table, QChart* chart)
{
    chart->removeAllSeries();

    QPieSeries *series = new QPieSeries();

    long long total = 0;
    for(int i = 0; i < table.size(); i++)
        total += table[i].itemSize;

    if(total)
    {
        double other = 0;
        for(int i = 0; i < table.size(); i++)
        {
            double percent = (double)table[i].itemSize/total*100;
            if(percent > 5)
                series->append(table[i].itemName, percent);
            else
                other += percent;
        }

        if(other)
            series->append("other", other);

    }
    else
        series->append("empty sizes", 0);
    chart->addSeries(series);
}



void BarChartCreator::drawChart(const QVector<TableItem>& table, QChart* chart)
{
    chart->removeAllSeries();

    QBarSeries *series = new QBarSeries();

    long long total = 0;
    for(int i = 0; i < table.size(); i++)
        total += table[i].itemSize;

    if(total)
    {
        double other = 0;
        for(int i = 0; i < table.size(); i++)
        {
            QBarSet* set = new QBarSet(table[i].itemName);

            double percent = (double)table[i].itemSize/total*100;
            if(percent > 5)
            {
                *set << percent;
                series->append(set);
            }
            else
                other += percent;
        }

        if(other)
        {
            QBarSet* set = new QBarSet("other");
            *set << other;
            series->append(set);
        }
    }
    else
    {
        QBarSet* set = new QBarSet("empty sizes");
        *set << 0;
        series->append(set);
    }

    chart->addSeries(series);

}
