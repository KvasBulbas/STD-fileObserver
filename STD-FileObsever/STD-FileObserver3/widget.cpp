#include "widget.h"

#include <QSplitter>
#include <QListView>
#include <QTreeView>
#include <QTextEdit>
#include <QFileSystemModel>
#include <QItemSelectionModel>
#include <QVBoxLayout>
#include <QTableView>
#include <QHeaderView>
#include <QStatusBar>
#include <QDebug>
#include <QHBoxLayout>
#include <QVBoxLayout>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

    dirModel =  new QFileSystemModel(this);
    dirModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    dirModel->setRootPath(QDir::homePath());

    treeView = new QTreeView(this);
    treeView->setModel(dirModel);

    tableModel = new FileBrowserDataModel(this);
    tableAdapter = new TableAdapter(tableModel);

    tableView = new QTableView(this);
    tableView->setModel(tableAdapter->getModel());

    pieChart = new QChart;
    pieAdapter = new PieChartAdapter(pieChart);

    pieView = new QChartView(this);
    pieView->setChart(pieAdapter->getModel());

    barChart = new QChart;
    barAdapter = new BarChartAdapter(barChart);

    barView = new QChartView(this);
    barView->setChart(barAdapter->getModel());

    stackedView = new QStackedWidget(this);
    if(stackedView)
    {
        stackedView->addWidget(tableView);
        stackedView->addWidget(barView);
        stackedView->addWidget(pieView);
    }

    QHBoxLayout *hbox1 = new QHBoxLayout();
    if(hbox1)
    {
        hbox1->addWidget(treeView);
        hbox1->addWidget(stackedView);
    }

    topFrame = new QFrame(this);
    topFrame->setFrameShadow(QFrame::Raised);

    stratagyBox = new QComboBox(this);
    stratagyBox->addItems({"Directory sizes", "Suffix sizes"});

    viewBox = new QComboBox(this);
    viewBox->addItems({"Table", "Bar", "Pie"});

    calcButton = new QPushButton("Get sizes");

    QHBoxLayout *hbox2 = new QHBoxLayout(topFrame);
    if(hbox2)
    {
        hbox2->addWidget(calcButton);
        hbox2->addWidget(viewBox);
        hbox2->addWidget(stratagyBox);
    }

    QVBoxLayout *vbox = new QVBoxLayout(this);
    if(vbox)
    {
        vbox->addWidget(topFrame);
        vbox->addLayout(hbox1);
    }

    counterStorage.attach(tableAdapter);
    counterStorage.attach(pieAdapter);
    counterStorage.attach(barAdapter);
    //counterAdapter.detach(listAdapter);

    connect(treeView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &Widget::on_selectionChangedSlot);
    connect(calcButton, &QPushButton::pressed, &counterStorage, &SizeCounterStorage::count);
    connect(stratagyBox, qOverload<int>(&QComboBox::currentIndexChanged), &counterStorage, &SizeCounterStorage::setStrategy);
    connect(viewBox, qOverload<int>(&QComboBox::currentIndexChanged), stackedView, &QStackedWidget::setCurrentIndex);
}

Widget::~Widget()
{
    delete tableAdapter;
    delete pieAdapter;
    delete barAdapter;
    delete pieChart;
    delete barChart;
}

void Widget::on_selectionChangedSlot(const QItemSelection &selected, const QItemSelection &deselected)
{
    Q_UNUSED(selected);
    Q_UNUSED(deselected);
    QModelIndex index = treeView->selectionModel()->currentIndex();
    QString dirPath = dirModel->filePath(index);

    if(dirPath != "")
    {
        counterStorage.setPath(dirPath);
    }

}

