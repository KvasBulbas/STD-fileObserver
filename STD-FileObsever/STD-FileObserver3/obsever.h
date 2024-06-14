#ifndef OBSEVER_H
#define OBSEVER_H

#include "modeladapter.h"
#include <QVector>

class ASubject : public QObject
{
    Q_OBJECT

public:

    void attach(ModelObserver* model)
    {
        qDebug() << "attach";
        connect(this, &ASubject::notify, model, &ModelObserver::update);
    }

    void detach(ModelObserver* model)
    {
        qDebug() << "detach";
        disconnect(this, &ASubject::notify, model, &ModelObserver::update);
    }

signals:
    void notify(const QVector<TableItem>& table);

};

#endif // OBSEVER_H
