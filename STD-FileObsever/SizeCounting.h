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

    virtual const QVector<tableItem> sortTable(QVector<tableItem> table)
    {
        QVector<tableItem> sortedTable;

        sortedTable.resize(table.size());

        for(int i = 0; i < sortedTable.size(); i++)
        {
            long long maxSize = -1;
            QString maxElementName = "zero";

            for(auto tableIter = table.begin(); tableIter  != table.end(); tableIter ++)
            {
                bool keyExistens = false;

                for(int j = 0; j < i; j++)
                    if(sortedTable[j].itemName == tableIter->itemName)
                    {
                        keyExistens = true;
                        break;
                    }

                if(!keyExistens && maxSize < tableIter->itemSize)
                {
                    maxSize = tableIter->itemSize;
                    maxElementName = tableIter->itemName;
                }
            }
            sortedTable[i].itemName = maxElementName;
            sortedTable[i].itemSize = maxSize;
        }

        return sortedTable;
    }


    virtual const QVector<tableItem> getProcentage(QVector<tableItem> table)
    {
        long long total = 0;

        for(int i = 0; i < table.size(); i++)
            total += table[i].itemSize;

        for(int i = 0; i < table.size(); i++)
            table[i].itemSize = table[i].itemSize / total * 100;

        return table;
    }
};


class Suffix_SizeCounting : public ISizeCounting
{
public:
    const QVector<tableItem> count(const QString& dirPath) override
    {
        QMap<QString, long long> suffixes;
        QDirIterator it(dirPath, QDirIterator::Subdirectories);

        while (it.hasNext()) {
            if(it.fileInfo().isFile())
                suffixes.insert(it.fileInfo().suffix(), suffixes[it.fileInfo().suffix()] + it.fileInfo().size());
            it.next();
        }
        if(it.fileInfo().isFile())
            suffixes.insert(it.fileInfo().suffix(), suffixes[it.fileInfo().suffix()] + it.fileInfo().size());

        QVector<tableItem> table;
        if(suffixes.size())
        {
            table.resize(suffixes.size());
            auto sufIter = suffixes.begin();

            for(int i = 0; i < table.size(); i++, sufIter++)
            {
                table[i].itemName = sufIter.key();
                table[i].itemSize = *sufIter;
            }
        }
        else
        {
            tableItem empty;
            empty.itemName = "Directory is empty";
            empty.itemSize = 0;
            table.push_back(empty);
        }

        return table;
    }

};


class Directory_SizeCounting : public ISizeCounting
{
    const QVector<tableItem> count(const QString& dirPath) override
    {
        QList<QString> elementName;
        QList<qint64> elementSize;

        QVector<tableItem> table;

        QDirIterator it(dirPath);

        qint64 curDirSize = 0;

        while (it.hasNext()) {
            if(it.fileInfo().isFile())
                curDirSize += it.fileInfo().size();

            if(it.fileInfo().isDir() && it.fileName() != '.' && it.fileName() != "..")
            {
                QDirIterator subIt(dirPath + '/' + it.fileName(), QDirIterator::Subdirectories);
                qint64 subDirSize  = 0;

                while (subIt.hasNext()) {
                    subDirSize  += subIt.fileInfo().size();
                    subIt.next();
                }
                subDirSize  += it.fileInfo().size();

                tableItem tempTable;
                tempTable.itemName = it.fileName();
                tempTable.itemSize = subDirSize;

                table.push_back(tempTable);
            }
            it.next();
        }

        if(it.fileInfo().isFile())
            curDirSize += it.fileInfo().size();

        if(it.fileInfo().isDir() && it.fileName() != '.' && it.fileName() != "..")
        {
            QDirIterator subIt(dirPath + '/' + it.fileName(), QDirIterator::Subdirectories);
            qint64 subDirSize  = 0;

            while (subIt.hasNext()) {
                subDirSize  += subIt.fileInfo().size();
                subIt.next();
            }
            subDirSize  += it.fileInfo().size();

            tableItem tempTable;
            tempTable.itemName = it.fileName();
            tempTable.itemSize = subDirSize;

            table.push_back(tempTable);
        }

        tableItem tempTable;
        tempTable.itemName = "current";
        tempTable.itemSize = curDirSize;

        table.push_back(tempTable);

        return table;
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

