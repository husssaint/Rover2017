#ifndef SERIALHANDLER_H
#define SERIALHANDLER_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QSerialPort>
#include <QWaitCondition>

// http://stackoverflow.com/questions/15103599/qt-serial-port-reading-data-consistently


class SerialHandler : public QThread
{
    Q_OBJECT
public:
    explicit SerialHandler(QObject *parent = 0);
    ~SerialHandler();
    void setupPort(QString portName);
    bool isReady() const;
    void run();
    void stop();
protected:
public slots:
private:
    bool t_stop;
    void readData();
    int state = 0;
    QSerialPort port;
    QString portName;
};

#endif // SERIALHANDLER_H
