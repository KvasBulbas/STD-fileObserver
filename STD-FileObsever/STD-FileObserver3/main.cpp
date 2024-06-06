#include <QApplication>
#include <QDebug>

#include "widget.h"
#include "SizeCounting.h"
#include <shared_mutex>

void printTable(const QVector<TableItem> table)
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

    const QVector<TableItem> sufTable = sufCounter->count(dirPath);

    qDebug() << "sufTable:";
    printTable(sufTable);

    const QVector<TableItem> sufSorted= sufCounter->sortTable(sufTable);

    qDebug() << "suf sorted";
    printTable(sufSorted);

//    qDebug() << "suf procntage";
//    printTable(sufCounter->getProcentage(sufSorted));

    qDebug() << "---------------------------------------------------------------------------";

    SizeCounter* dirCounter = new SizeCounter(new Directory_SizeCounting);

    const QVector<TableItem> dirTable = dirCounter->count(dirPath);

    qDebug() << "dirTable:";
    printTable(dirTable);

    const QVector<TableItem> dirSorted = dirCounter->sortTable(dirTable);

    qDebug() << "dir sorted";
    printTable(dirSorted);

//    qDebug() << "dir procntage";
//    printTable(dirCounter->getProcentage(dirSorted));

    qDebug() << "---------------------------------------------------------------------------";

    delete dirCounter;
    delete sufCounter;

}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    std::make_shared<Suffix_SizeCounting> suf;
//    std::shared_ptr<Directory_SizeCounting> dir;


//    Suffix_SizeCounting* suf = new Suffix_SizeCounting;
//    Directory_SizeCounting* dir = new Directory_SizeCounting;


//    SizeCounter* counter1 = new SizeCounter(suf);
//    SizeCounter* counter2 = new SizeCounter(dir);

//    const QVector<TableItem> sufTable = counter1->count("Z:/tests/BigSizeDir");

//    const QVector<TableItem> dirTable = counter2->count("Z:/tests/BigSizeDir");

//    printTable(sufTable);
//    printTable(dirTable);


//    delete suf;
//    delete dir;

//    delete counter1;
//    delete counter2;
    Widget w;
    w.show();



    //SizeCounter* sufCounter = new SizeCounter(new (ISizeCounting::types::Suffix_SizeCounting));



//    qDebug() << "empty directory";

//    algTest("Z:/tests/EmptyDir");

//    qDebug() << "only empty subdirectory";

//    algTest("Z:/tests/OnlyEmptySubdir");

//    qDebug() << "empty subdirectory";

//    algTest("Z:/tests/EmptySubdir");

//    qDebug() << "empty current directory";

//    algTest("Z:/tests/EmptyCurDir");

//    qDebug() << "big size directory";

//    algTest("Z:/tests/BigSizeDir");


    return a.exec();
}
