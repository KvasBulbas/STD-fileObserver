#pragma once

#include "filebrowserdatamodel.h"
#include <sizecounteradapter.h>
#include "chartcomponent.h"

#include <QWidget>
#include <QMainWindow>
#include <QFileSystemModel>
#include <QTreeView>
#include <QTableView>
#include <QComboBox>
#include<QFrame>
#include <QPushButton>
#include <QStackedWidget>

class Widget : public QWidget
{
    Q_OBJECT

private slots:

    void on_selectionChangedSlot(const QItemSelection &selected = QItemSelection(), const QItemSelection &deselected = QItemSelection());


public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QFileSystemModel *dirModel = nullptr;
    QTreeView *treeView = nullptr;
    FileBrowserDataModel *tablemodel = nullptr;
    QTableView *tableView = nullptr;
    QComboBox *stratagyBox = nullptr;
    QComboBox *viewBox;
    QFrame *topFrame = nullptr;
    QPushButton *calcButton = nullptr;
    SizeCounterAdapter &counterAdapter = SizeCounterAdapter::instanse();
    TableAdapter* listAdapter = nullptr;

    QChartView* pieView;
    QChartView* barView;

    QStackedWidget* stackedView;

    ChartComponent* pieChartCreator = new PieChart();
    ChartComponent* barChartCreator = new BarChart();

};
