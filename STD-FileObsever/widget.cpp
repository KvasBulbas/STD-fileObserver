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
    QString homePath = QDir::homePath();
    dirModel =  new QFileSystemModel();
    dirModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    dirModel->setRootPath(homePath);

    treeView = new QTreeView();
    treeView->setModel(dirModel);

    tableView = new QTableView();

    QHBoxLayout *hbox1 = new QHBoxLayout();
    hbox1->addWidget(treeView);
    hbox1->addWidget(tableView);

    topFrame = new QFrame();
    topFrame->setFrameShadow(QFrame::Raised);

    stratagyBox = new QComboBox();
    stratagyBox->addItems({"Directory sizes", "Suffix sizes"});

    QHBoxLayout *hbox2 = new QHBoxLayout();
    hbox2->addStretch();
    hbox2->addWidget(stratagyBox);

    QVBoxLayout *vbox = new QVBoxLayout(this);
    vbox->addLayout(hbox2);
    vbox->addLayout(hbox1);



    connect(treeView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &Widget::on_selectionChangedSlot);
    connect(stratagyBox, qOverload<int>(&QComboBox::currentIndexChanged), this, &Widget::on_selectionChangedStrategy);
}

Widget::~Widget()
{
}

void Widget::on_selectionChangedStrategy(int index)
{
    Q_UNUSED(index);

    on_selectionChangedSlot();
}

void Widget::on_selectionChangedSlot(const QItemSelection &selected, const QItemSelection &deselected)
{
    Q_UNUSED(selected);
    Q_UNUSED(deselected);
    QModelIndex index = treeView->selectionModel()->currentIndex();
    QString dirPath = dirModel->filePath(index);

    qDebug() << dirPath;

    qDebug() << stratagyBox->currentIndex();

    if(dirPath != "")
    {
        if(tablemodel != nullptr)
            delete tablemodel;

        tablemodel = new FileBrowserDataModel(dirPath, stratagyBox->currentIndex(),nullptr);

        tableView->setModel(tablemodel);
    }


}

