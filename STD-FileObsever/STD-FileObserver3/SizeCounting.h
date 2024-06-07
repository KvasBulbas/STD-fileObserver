#pragma once

#include <QMap>
#include <QString>
#include <QVector>
#include <QDirIterator>

class TableItem
{
public:

    QString itemName;
    long long itemSize;

};

class ISizeCounting
{    

public:
    virtual ~ISizeCounting(){}
    virtual const QVector<TableItem> count(const QString& dirPath) = 0;

    virtual const QVector<TableItem> sortTable(QVector<TableItem> table)
    {
        QVector<TableItem> sortedTable;

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


};


class Suffix_SizeCounting : public ISizeCounting
{
public:
    const QVector<TableItem> count(const QString& dirPath) override
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

        QVector<TableItem> table;
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
            TableItem empty;
            empty.itemName = "Directory is empty";
            empty.itemSize = 0;
            table.push_back(empty);
        }

        return table;
    }

};


class Directory_SizeCounting : public ISizeCounting
{
    const QVector<TableItem> count(const QString& dirPath) override
    {
        QVector<TableItem> table;

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

                TableItem tempTable;
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

            TableItem tempTable;
            tempTable.itemName = it.fileName();
            tempTable.itemSize = subDirSize;

            table.push_back(tempTable);
        }

        TableItem tempTable;
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
    }

    const QVector<TableItem> count(const QString& dirPath) override
    {
        return counter->count(dirPath);
    }

private:
    ISizeCounting* counter;
};
