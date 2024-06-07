#include "chartcomponent.h"

void PieChart::drawChart(QVector<TableItem> table, QChart* chart)
{
    chart->removeAllSeries();

    QPieSeries *series = new QPieSeries();

    for(int i = 0; i < table.size(); i++)
        series->append(table[i].itemName, table[i].itemSize);

    chart->addSeries(series);
}



void BarChart::drawChart(QVector<TableItem> table, QChart* chart)
{
    chart->removeAllSeries();

    QBarSeries *series = new QBarSeries();

    for(int i = 0; i < table.size(); i++)
    {
        QBarSet* set = new QBarSet(table[i].itemName);
        *set << 33;
        series->append(set);
    }

    chart->addSeries(series);
}
