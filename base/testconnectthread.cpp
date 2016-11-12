#include "testconnectthread.h"

testConnectThread::testConnectThread()
{
    t_stop = false;
    //what if want to call with object, not class? What does that look like.
    connect(SerialHandler, SIGNAL(valueChanged(int)), dummyConnect, SLOT(dummy(int)));
}

void testconnectthread::run()
{
    sendInt();
}

void testconnectthread::stop()
{
    t_stop = true;
}

void testconnectthread::sendInt()
{
    while (!t_stop)
        emit valueChanged(5);
        sleep(1);
}
