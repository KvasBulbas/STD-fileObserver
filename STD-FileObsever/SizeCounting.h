#ifndef SIZECOUNTING_H
#define SIZECOUNTING_H

#endif // SIZECOUNTING_H
#include <QMap>
#include <QString>
#include <QVector>
#include <QDirIterator>

class tableItem
{
public:

    QString itemName;
    double itemSize;

};

class ISizeCounting
{
public:
    virtual ~ISizeCounting(){}
    virtual const QVector<tableItem> count(const QString& dirPath) = 0;
};


class suffix_SizeCounting : public ISizeCounting
{
public:
    const QVector<tableItem> count(const QString& dirPath) override
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

//        qDebug() << total;

//        for(auto iter = suffixes.begin(); iter != suffixes.end(); iter++)
//        {
//            qDebug() << iter.key() << "size: " << *iter;
//        }

        QVector<tableItem> sortedTable;
        sortedTable.resize(suffixes.size());

        for(int i = 0; i < suffixes.size(); i++)
        {
            long long maxSize = -1;
            QString maxElementName = "zero";

            for(auto sizeIter = suffixes.begin(); sizeIter != suffixes.end(); sizeIter++)
            {
                bool keyExistens = false;

                for(int j = 0; j < i; j++)
                    if(sortedTable[j].itemName == sizeIter.key())
                    {
                        keyExistens = true;
                        break;
                    }

                if(!keyExistens && maxSize < *sizeIter)
                {
                    maxSize = *sizeIter;
                    maxElementName = sizeIter.key();
                }

            }
            sortedTable[i].itemName = maxElementName;
            sortedTable[i].itemSize = (double)maxSize/total *100;
        }


        return sortedTable;
    }


};



class SizeCounter : public ISizeCounting
{
public:
    SizeCounter(ISizeCounting* counter):counter(counter){}

    ~SizeCounter()
    {
        delete counter;
    }

    const QVector<tableItem> count(const QString& dirPath) override
    {
        return counter->count(dirPath);
    }

private:
    ISizeCounting* counter;
};

