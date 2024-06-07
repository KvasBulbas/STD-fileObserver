#ifndef SIZECOUNTERADAPTER_H
#define SIZECOUNTERADAPTER_H
#include "SizeCounting.h"
#include "obsever.h"
#include "QDebug"

class SizeCounterStorage : public ASubject
{
    Q_OBJECT
public:

    static SizeCounterStorage& instanse()
    {
        static SizeCounterStorage s;
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
        qDebug() << "count";
        if(dirPath != "")
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
    SizeCounterStorage()
    {
        strategiesPtr.push_back(new Directory_SizeCounting);
        strategiesPtr.push_back(new Suffix_SizeCounting);
        counter = new SizeCounter(strategiesPtr[0]);
    }

    ~SizeCounterStorage()
    {
        delete counter;
        for(int i = 0; i < strategiesPtr.size(); i++)
            delete strategiesPtr[i];
    }

    SizeCounterStorage(SizeCounterStorage const&);
    SizeCounterStorage& operator=(SizeCounterStorage const&);

    QVector<ISizeCounting*> strategiesPtr;
    SizeCounter* counter;
    QString dirPath = "";
};


#endif // SIZECOUNTERADAPTER_H
