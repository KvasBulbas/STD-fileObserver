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

//    QDir dir(DirPath);

//    QFileInfo tempFile(dir.absolutePath());
//    qDebug() <<dir.Size;
//    QStringList files = dir.entryList();

//    qDebug() << files;

    QList<QString> elementName;

    QList<qint32> elementSize;

    QDirIterator it(dirPath);

    qint32 total = 0;
    while (it.hasNext()) {
        if(it.fileInfo().isFile())
        {
            total += it.fileInfo().size();
            qDebug() << "is file: " << it.fileName() << ' ' << it.fileInfo().size();

        }

        if(it.fileInfo().isDir() && it.fileName() != '.' && it.fileName() != "..")
        {
            qDebug() << "is dir:" << it.fileName();

            elementName.push_back(it.fileName());
            int tempSize = dirSize(dirPath + '/' + it.fileName());

            total+= tempSize;

            elementSize


        }
        it.next();
    }

    if(it.fileInfo().isFile())
    {
        total += it.fileInfo().size();
        qDebug() << "is file: " << it.fileName() << ' ' << it.fileInfo().size();

        elementName.push_back(it.fileName());
        elementSize.push_back(it.fileInfo().size());
    }

    if(it.fileInfo().isDir() && it.fileName() != '.' && it.fileName() != "..")
    {
        qDebug() << "is dir:" << it.fileName();
        elementName.push_back(it.fileName());
        dirSize(dirPath + '/' + it.fileName());
    }

    //tabelWIdget.resize(elementName.size());



    qDebug() << "size" << total;

    return total;



}



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    const QString dirPath = "Z:/forSTD";

    dirSize(dirPath);

//    QDir dir(dirPath);

////    if(dir.mkpath(path))
////        qDebug() << "dir is create";



//    qDebug() << dir.count();
//    QStringList files = dir.entryList();

    //qDebug() << files;





    return a.exec();
}
