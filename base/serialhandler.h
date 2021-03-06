#ifndef SERIALHANDLER_H
#define SERIALHANDLER_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QSerialPort>
#include <QByteArray>

// http://stackoverflow.com/questions/15103599/qt-serial-port-reading-data-consistently


class SerialHandler : public QThread
{
    Q_OBJECT
public:
    explicit SerialHandler(QObject *parent = 0);
    ~SerialHandler();
    void setupPort(QString portName);
    bool isReady() const;
    void write(uint8_t *data, uint16_t count);
    void run();

signals:
    // TODO: fill these in
    void batteryVoltageChanged(uint16_t voltage);

protected:

private:
    void readData();
    QSerialPort port;
    void sendBuffer(QByteArray array);
    int state = 0;
    QString portName;
};

extern SerialHandler serial;

#endif // SERIALHANDLER_H
