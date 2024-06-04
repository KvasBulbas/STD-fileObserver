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
    tablemodel = new FileBrowserDataModel(this);
    tableView->setModel(tablemodel);

    QHBoxLayout *hbox1 = new QHBoxLayout();
    if(hbox1)
    {
        hbox1->addWidget(treeView);
        hbox1->addWidget(tableView);
    }

    topFrame = new QFrame(this);
    topFrame->setFrameShadow(QFrame::Raised);

    stratagyBox = new QComboBox(this);
    stratagyBox->addItems({"Directory sizes", "Suffix sizes"});

    calcButton = new QPushButton("Get sizes");

    QHBoxLayout *hbox2 = new QHBoxLayout(topFrame);
    if(hbox2)
    {
        hbox2->addWidget(calcButton);
        hbox2->addWidget(stratagyBox);
    }

    QVBoxLayout *vbox = new QVBoxLayout(this);
    if(vbox)
    {
        vbox->addWidget(topFrame);
        vbox->addLayout(hbox1);
    }

    connect(treeView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &Widget::on_selectionChangedSlot);
    connect(stratagyBox, qOverload<int>(&QComboBox::currentIndexChanged), tablemodel, &FileBrowserDataModel::setStrategy);
    connect(calcButton, &QPushButton::pressed, tablemodel, &FileBrowserDataModel::updateData);
}

Widget::~Widget()
{
}



void Widget::on_selectionChangedSlot(const QItemSelection &selected, const QItemSelection &deselected)
{
    Q_UNUSED(selected);
    Q_UNUSED(deselected);
    QModelIndex index = treeView->selectionModel()->currentIndex();
    QString dirPath = dirModel->filePath(index);

    if(dirPath != "")
    {
        tablemodel->setPath(dirPath);
    }

}
