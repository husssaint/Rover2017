#include "serialhandler.h"

SerialHandler::SerialHandler(QObject *parent) : QThread(parent)
{
    m_stop = false;
}

SerialHandler::~SerialHandler()
{
    //delete port;
}

void SerialHandler::run()
{

    if(!this->isReady()) {
        qDebug() << "Serial is not set up";
        stop();
    }
    else {
        readData();
    }
}

void SerialHandler::stop() {
    qDebug() << "Thread Stopped in Main: " << currentThreadId();
    QMutexLocker locker (&m_mutex);
    qDebug() << "Serial Handler stopped: " << currentThreadId();
    m_stop = true;
}

void SerialHandler::setupPort(QString name)
{
    this->portName = name;
    port.setPortName(this->portName);
    //ich:
    //setting port settings, and if they aren't set immediately just bounce out and return error report
    if(port.open(QIODevice::ReadOnly)) {
        if(!port.setBaudRate(QSerialPort::Baud57600)) {
            qDebug() << port.errorString();
            return;
        }
        if(!port.setDataBits(QSerialPort::Data8)) {
            qDebug() << port.errorString();
            return;
        }
        if(!port.setParity(QSerialPort::NoParity)) {
            qDebug() << port.errorString();
            return;
        }
        if(!port.setStopBits(QSerialPort::OneStop)) {
            qDebug() << port.errorString();
            return;
        }
        if(!port.setFlowControl(QSerialPort::NoFlowControl)) {
            qDebug() << port.errorString();
            return;
        }
    }
    else {
        qDebug() << port.errorString();
        return;
    }
    //ich:
    //used for isReady()
    this->state = 1;
}

//ich:
//use this to check if thread was set up correcctly
bool SerialHandler::isReady() const
{
    if(this->state > 0)
        return true;
    return false;
}

void SerialHandler::readData()
{
/*


    uint8_t *buffer = (uint8_t *)malloc(0);
    char curChar[1] = {0};
    size_t size = 0;
    if(!port.isReadable())
    {
        qDebug() << "The port is unreadable";
        return;
    }
    do
    {
        QMutexLocker locker (&m_mutex);
        //ich:
        //port puts next character coming from port into curChar
        //if there are no characters coming in just keep doing this if statement till get something
        if(!port.getChar(curChar))
            continue;
        size++;
        buffer = (uint8_t *)realloc(buffer, size);
        //ich:
        //
        if(*curChar == ESCAPE_BYTE) {
            this->port.getChar(curChar);
            buffer[size-1] = (uint8_t)*curChar;
            continue;
        }
        if(*curChar == STOP_BYTE) {
            size_t size = 0;

            //ich:
            //why are you freeing here? Don't you want to use buffer to activate signals like the battery voltage?:
            free(buffer);
            uint8_t *buffer = (uint8_t *)malloc(0);
            messageBuffer *packet = (messageBuffer *)malloc(sizeof(messageBuffer *));
            packet->buffer = buffer;
            packet->size = size;

            if(*packet->buffer == BATTERYVOLTAGE_TYPE)
            {
                //ich:
                //do these come from the py generated code?
                packets_BatteryVoltage p = decodeBatteryVoltage(packet);

                qDebug() << p.battery_voltage;
            }
            freeMessageBuffer(packet);
            //ich:
            //should this be continue? Don't you want to continue this infinite loop?
            return;
        }
        buffer[size-1] = (uint8_t)*curChar;
    }
    while(port.isReadable() && !m_stop);
*/
}

/*void SerialHandler::activateSignal(buffer) {
    messageBuffer *packet = (messageBuffer *)malloc(sizeof(messageBuffer *));
    packet->buffer = buffer;
    packet->size = size;

    if(*packet->buffer == BATTERYVOLTAGE_TYPE)
    {
        packets_BatteryVoltage p = decodeBatteryVoltage(packet);

        qDebug() << p.battery_voltage;
    }

    else if(*packet->buffer == MOTORVOLTAGE_TYPE)
    {
        packets_MotorVoltage p = decodeMotorVoltage(packet);

    }

    freeMessageBuffer(packet);

}*/

