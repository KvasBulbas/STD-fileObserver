#include "widget.h"

#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QString>
#include <QDirIterator>
#include <QList>
#include <QMap>
#include <SizeCounting.h>



void printTable(const QVector<tableItem> table)
{
    double totalProcent = 0;
    for(int i = 0; i < table.size(); i++)
    {
        qDebug() << table[i].itemName << "size:" << table[i].itemSize << "%";
        totalProcent += table[i].itemSize;
    }

    qDebug() << "total procentage" << totalProcent << "%";
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    Widget w;
//    w.show();

    const QString dirPath = "Z:";

    SizeCounter* dirCounter = new SizeCounter(new Directory_SizeCounting);
    SizeCounter* sufCounter = new SizeCounter(new Suffix_SizeCounting);

    const QVector<tableItem> dirTable = dirCounter->count(dirPath);
    const QVector<tableItem> sufTable = sufCounter->count(dirPath);

    qDebug() << "dirTable:";
    printTable(dirTable);

    qDebug() << "sufTable:";
    printTable(sufTable);

    delete dirCounter;
    delete sufCounter;

    return a.exec();
}
