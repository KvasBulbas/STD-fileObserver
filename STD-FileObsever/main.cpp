#include "widget.h"
#include <QApplication>
#include <QDebug>
#include <SizeCounting.h>



void printTable(const QVector<tableItem> table)
{
    for(int i = 0; i < table.size(); i++)
    {
        qDebug() << table[i].itemName << "size:" << table[i].itemSize;
    }

    qDebug() << " ";
}


void algTest(const QString dirPath)
{
    SizeCounter* sufCounter = new SizeCounter(new Suffix_SizeCounting);

    const QVector<tableItem> sufTable = sufCounter->count(dirPath);

    qDebug() << "sufTable:";
    printTable(sufTable);

    const QVector<tableItem> sufSorted= sufCounter->sortTable(sufTable);

    qDebug() << "suf sorted";
    printTable(sufSorted);

    qDebug() << "suf procntage";
    printTable(sufCounter->getProcentage(sufSorted));

    qDebug() << "---------------------------------------------------------------------------";

    SizeCounter* dirCounter = new SizeCounter(new Directory_SizeCounting);

    const QVector<tableItem> dirTable = dirCounter->count(dirPath);

    qDebug() << "dirTable:";
    printTable(dirTable);

    const QVector<tableItem> dirSorted = dirCounter->sortTable(dirTable);

    qDebug() << "dir sorted";
    printTable(dirSorted);

    qDebug() << "dir procntage";
    printTable(dirCounter->getProcentage(dirSorted));

    qDebug() << "---------------------------------------------------------------------------";

    delete dirCounter;
    delete sufCounter;

}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    qDebug() << "empty directory";

    algTest("Z:/tests/EmptyDir");

    qDebug() << "only empty subdirectory";

    algTest("Z:/tests/OnlyEmptySubdir");

    qDebug() << "empty subdirectory";

    algTest("Z:/tests/EmptySubdir");

    qDebug() << "empty current directory";

    algTest("Z:/tests/EmptyCurDir");

    qDebug() << "big size directory";

    algTest("Z:/tests/BigSizeDir");


    return a.exec();
}
