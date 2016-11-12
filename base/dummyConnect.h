#ifndef DUMMYCONNECT_H
#define DUMMYCONNECT_H

#include <QThread>

class dummyConnect : public QThread()
{
public:
    dummyConnect();
public slots:
    void dummy(int);
};

#endif // DUMMYCONNECT_H
