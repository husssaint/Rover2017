#ifndef TESTCONNECTTHREAD_H
#define TESTCONNECTTHREAD_H

#include <QObject>
#include <QThread>
#include <QDebug>

class testConnectThread : public QThread
{
    Q_OBJECT
public:
    testConnectThread();
    void run();
    void stop();
private:
    void sendInt();
    bool t_stop;
};

#endif // TESTCONNECTTHREAD_H
