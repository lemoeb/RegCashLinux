#ifndef CHECKSHOP_H
#define CHECKSHOP_H

#include <QThread>
#include <QtNetwork>

class WorkerThread : public QThread
{
    Q_OBJECT

private:

public:
    explicit WorkerThread(QObject *parent = 0);


signals:


public slots:

};

#endif // CHECKSHOP_H
