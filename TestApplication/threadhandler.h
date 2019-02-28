#ifndef THREADHANDLER_H
#define THREADHANDLER_H

#include <QObject>
#include <QDebug>

class ThreadHandler : public QObject
{
    Q_OBJECT
public:
    ThreadHandler();
    virtual ~ThreadHandler();

public slots:
     void process();
     static long long getValue();
     static int getCounter();
     void stopThread();

signals:
     void finished();
     void rounding();

private:
     static long long int m_value;
     static int m_counter;
};

#endif // THREADHANDLER_H
