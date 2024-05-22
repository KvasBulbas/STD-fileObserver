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
            //qDebug() << it.fileInfo().suffix();
            total += it.fileInfo().size();

            suffixes.insert(it.fileInfo().suffix(), suffixes[it.fileInfo().suffix()] + it.fileInfo().size());

        }
        it.next();
    }
    if(it.fileInfo().isFile())
    {
        //qDebug() << it.fileInfo().suffix();

        total += it.fileInfo().size();
        suffixes.insert(it.fileInfo().suffix(), suffixes[it.fileInfo().suffix()] + it.fileInfo().size());

    }
    it.next();

    qDebug() << total;


    for(auto iter = suffixes.begin(); iter != suffixes.end(); iter++)
    {
        qDebug() << iter.key() << "size: " << (double)*iter/total;
    }

}



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    const QString dirPath = "Z:";

    //procentSizeByDir(dirPath);
    procentSizeBySuf(dirPath);


//    QMap<QString, int> suffixes;

//    suffixes.insert("txt", 3);

//    suffixes.insert("jpeg", 5);


//    qDebug() << suffixes["tt"];




    return a.exec();
}
