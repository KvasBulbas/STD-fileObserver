#include "widget.h"

#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QString>
#include <QDirIterator>
#include <QList>


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



int procentSize(const QString dirPath)
{

//    QDir dir(DirPath);

//    QFileInfo tempFile(dir.absolutePath());
//    qDebug() <<dir.Size;
//    QStringList files = dir.entryList();

//    qDebug() << files;

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



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    const QString dirPath = "Z:/forSTD";

    procentSize(dirPath);

//    QDir dir(dirPath);

////    if(dir.mkpath(path))
////        qDebug() << "dir is create";



//    qDebug() << dir.count();
//    QStringList files = dir.entryList();

    //qDebug() << files;





    return a.exec();
}
