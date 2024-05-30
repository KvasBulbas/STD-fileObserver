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


MainWindow::MainWindow(QMainWindow *parent)
    : QMainWindow(parent)
{
    this->setGeometry(100, 100, 1500, 500);
//    this->setStatusBar(new QStatusBar(this));
//    this->statusBar()->showMessage("Choosen Path: ");

    QString homePath = QDir::homePath();
    dirModel =  new QFileSystemModel(this);
    dirModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    dirModel->setRootPath(homePath);

    treeView = new QTreeView();
    treeView->setModel(dirModel);

    QSplitter *splitter = new QSplitter(parent);
    splitter->addWidget(treeView);
    setCentralWidget(splitter);

}

MainWindow::~MainWindow()
{
}

