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

int dirSize(const QString dirPath)
{
    QDirIterator it(dirPath, QDirIterator::Subdirectories);
    qint64 total = 0;

    while (it.hasNext()) {
        total += it.fileInfo().size();
        it.next();
    }

    total += it.fileInfo().size();


    return total;
}



int procentSizeByDir(const QString dirPath)
{
    QList<QString> elementName;
    QList<qint64> elementSize;

    QDirIterator it(dirPath);

    qint64 total = 0;

    qint64 curDirSize = 0;

    while (it.hasNext()) {
        if(it.fileInfo().isFile())
        {
            total += it.fileInfo().size();
            curDirSize += it.fileInfo().size();
            //qDebug() << "is file: " << it.fileName() << ' ' << it.fileInfo().size();

        }

        if(it.fileInfo().isDir() && it.fileName() != '.' && it.fileName() != "..")
        {
            //qDebug() << "is dir:" << it.fileName();

            qint64 subDirSize = dirSize(dirPath + '/' + it.fileName());
            total += subDirSize;

            elementName.push_back(it.fileName());
            elementSize.push_back(subDirSize);
        }
        it.next();
    }

    if(it.fileInfo().isFile())
    {
        total += it.fileInfo().size();
        curDirSize += it.fileInfo().size();
        //qDebug() << "is file: " << it.fileName() << ' ' << it.fileInfo().size();
    }

    if(it.fileInfo().isDir() && it.fileName() != '.' && it.fileName() != "..")
    {
        //qDebug() << "is dir:" << it.fileName();

        qint64 subDirSize = dirSize(dirPath + '/' + it.fileName());
        total += subDirSize;

        elementName.push_back(it.fileName());
        elementSize.push_back(subDirSize);
    }

    //tabelWIdget.resize(elementName.size());


    auto sizeIter = elementSize.begin();

    for(auto nameIter = elementName.begin() ; nameIter != elementName.end(); nameIter++, sizeIter++)
    {
        qDebug() << *nameIter << "dir size:" << *sizeIter << "procent dir size" << (double)*sizeIter/total;
    }

    qDebug() << "total dir size:" << total << "curent dir size" << curDirSize << " procent curent dir size" << (double)curDirSize/total;
    return total;
}

void procentSizeBySuf(const QString dirPath)
{
    QMap<QString, long long> suffixes;

    long long total = 0;

    QDirIterator it(dirPath, QDirIterator::Subdirectories);

    while (it.hasNext()) {
        if(it.fileInfo().isFile())
        {
            total += it.fileInfo().size();
            suffixes.insert(it.fileInfo().suffix(), suffixes[it.fileInfo().suffix()] + it.fileInfo().size());

        }
        it.next();
    }
    if(it.fileInfo().isFile())
    {
        total += it.fileInfo().size();
        suffixes.insert(it.fileInfo().suffix(), suffixes[it.fileInfo().suffix()] + it.fileInfo().size());

    }
    it.next();

//    qDebug() << total;


//    for(auto iter = suffixes.begin(); iter != suffixes.end(); iter++)
//    {
//        qDebug() << iter.key() << "size: " << *iter;
//    }


    QList<QString> elementName;
    //QList<long long> elementSize;

    QList<double> elementSize;

    for(int i = 0; i < suffixes.size(); i++)
    {
        long long maxSize = -1;
        QString maxElementName = "zero";

        for(auto sizeIter = suffixes.begin(); sizeIter != suffixes.end(); sizeIter++)
        {

            bool keyExistens = false;

            for(auto nameIter = elementName.begin() ; nameIter != elementName.end(); nameIter++)
            {
                if(*nameIter == sizeIter.key())
                {
                    keyExistens = true;
                    break;
                }

            }

            if(!keyExistens && maxSize < *sizeIter)
            {
                maxSize = *sizeIter;
                maxElementName = sizeIter.key();
            }
        }

        elementName.push_back(maxElementName);
        //elementSize.push_back(maxSize);
        elementSize.push_back((double)maxSize/total *100);

    }


    auto sizeIter = elementSize.begin();

    qDebug() << "sorted";
    double totalProcent = 0;

    for(auto nameIter = elementName.begin() ; nameIter != elementName.end(); nameIter++, sizeIter++)
    {
        qDebug() << *nameIter << "dir size:" << *sizeIter << '%';

        totalProcent += *sizeIter;
    }

    qDebug() << "total procent:" << totalProcent << '%';

}



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    Widget w;
//    w.show();

    const QString dirPath = "Z:";

    SizeCounter* counter = new SizeCounter(new suffix_SizeCounting);

    const QVector<tableItem> table = counter->count(dirPath);

    double totalProcent = 0;
    for(int i = 0; i < table.size(); i++)
    {
        qDebug() << table[i].itemName << "size:" << table[i].itemSize;
        totalProcent += table[i].itemSize;
    }

    qDebug() << "total procentage" << totalProcent;

    delete counter;

    //procentSizeByDir(dirPath);
    //procentSizeBySuf(dirPath);


//    QMap<QString, int> suffixes;

//    suffixes.insert("txt", 3);

//    suffixes.insert("jpeg", 5);


//    qDebug() << suffixes["tt"];




    return a.exec();
}
