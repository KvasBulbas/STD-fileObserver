#pragma once

#include "filebrowserdatamodel.h"

#include <QWidget>
#include <QMainWindow>
#include <QFileSystemModel>
#include <QTreeView>
#include <QTableView>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QMainWindow *parent = nullptr);
    ~MainWindow();

private:
    QFileSystemModel *dirModel;
    QTreeView *treeView;


};
