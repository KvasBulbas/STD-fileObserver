#ifndef SIZECOUNTERADAPTER_H
#define SIZECOUNTERADAPTER_H
#include "SizeCounting.h"
#include "obsever.h"
#include "QDebug"

class SizeCounterAdapter : public ASubject
{
    Q_OBJECT
public:

    static SizeCounterAdapter& instanse()
    {
        static SizeCounterAdapter s;

        return s;
    }

    void setPath(const QString newPath)
    {
        qDebug() << "set path";
        dirPath = newPath;
    }

public slots:
    void count()
    {
        qDebug() << "cousdsnt";

        emit notify(counter->sortTable(counter->count(dirPath)));
    }

    void setStrategy(int index)
    {
        qDebug() << "set strategy";
        if(index < strategiesPtr.size())
        {
            if(counter)
                delete counter;
            counter = new SizeCounter(strategiesPtr[index]);
        }
    }



private:
    SizeCounterAdapter()
    {
        strategiesPtr.push_back(new Directory_SizeCounting);
        strategiesPtr.push_back(new Suffix_SizeCounting);
        counter = new SizeCounter(strategiesPtr[0]);
    }

    ~SizeCounterAdapter()
    {
        delete counter;
        for(int i = 0; i < strategiesPtr.size(); i++)
            delete strategiesPtr[i];
    }

    SizeCounterAdapter(SizeCounterAdapter const&);
    SizeCounterAdapter& operator=(SizeCounterAdapter const&);

    QVector<ISizeCounting*> strategiesPtr;
    SizeCounter* counter;
    QString dirPath = "";
    TableItem item;

};


#endif // SIZECOUNTERADAPTER_H
