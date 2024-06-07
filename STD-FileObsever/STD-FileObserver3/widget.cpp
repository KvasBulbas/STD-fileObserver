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



    tableView = new QTableView(this);

    listAdapter = new TableAdapter(new FileBrowserDataModel);


    tableView->setModel(listAdapter->getModel());
    //tableView->setModel(listAdapter->getModel());



    pieView = new QChartView(this);
    barView = new QChartView(this);

    stackedView = new QStackedWidget(this);

    stackedView->addWidget(tableView);
    stackedView->addWidget(barView);
    stackedView->addWidget(pieView);

    SizeCounter counter = new SizeCounter(new Directory_SizeCounting);
    SizeCounter counter1 = new SizeCounter(new Suffix_SizeCounting);

    QChart* pieChart = pieChartCreator->createChart(counter.count("Z:/tests/EmptyCurDir"));
    QChart* barChart = barChartCreator->createChart(counter.count("Z:/tests/BigSizeDir"));



    pieView->setChart(pieChart);

    pieChartCreator->createChart(counter1.count("Z:/tests/EmptyCurDir"), pieChart);

    barView->setChart(barChart);






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

    counterAdapter.attach(listAdapter);

    //counterAdapter.detach(listAdapter);

    connect(treeView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &Widget::on_selectionChangedSlot);
    connect(calcButton, &QPushButton::pressed, &counterAdapter, &SizeCounterAdapter::count);
    connect(stratagyBox, qOverload<int>(&QComboBox::currentIndexChanged), &counterAdapter, &SizeCounterAdapter::setStrategy);
    connect(viewBox, qOverload<int>(&QComboBox::currentIndexChanged), stackedView, &QStackedWidget::setCurrentIndex);
}


Widget::~Widget()
{
    delete listAdapter;
    //delete pieChartCreator;
    //delete barChartCreator;
}



void Widget::on_selectionChangedSlot(const QItemSelection &selected, const QItemSelection &deselected)
{
    Q_UNUSED(selected);
    Q_UNUSED(deselected);
    QModelIndex index = treeView->selectionModel()->currentIndex();
    QString dirPath = dirModel->filePath(index);

    if(dirPath != "")
    {
        counterAdapter.setPath(dirPath);
    }

}

