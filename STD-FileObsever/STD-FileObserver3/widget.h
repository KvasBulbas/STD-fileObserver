#pragma once

#include <sizecounteradapter.h>

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

    TableAdapter* tableAdapter = nullptr;
    QTableView *tableView = nullptr;
    FileBrowserDataModel *tableModel = nullptr;

    PieChartAdapter* pieAdapter = nullptr;
    QChartView* pieView = nullptr;
    QChart* pieChart = nullptr;

    BarChartAdapter* barAdapter = nullptr;
    QChartView* barView = nullptr;
    QChart* barChart = nullptr;

    QComboBox *stratagyBox = nullptr;
    QComboBox *viewBox = nullptr;
    QFrame *topFrame = nullptr;
    QPushButton *calcButton = nullptr;
    QStackedWidget* stackedView;

    SizeCounterStorage &counterStorage = SizeCounterStorage::instanse();


};
