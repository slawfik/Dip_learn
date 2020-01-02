
#include "serial_thread.h"
serialThread::serialThread(QObject *parent) :QThread(parent)
{
}

serialThread::~serialThread()
{
    m_quit = true;
    wait();
}

void serialThread::set_run(QString portName, qint32 baudRate)
{
    m_portName = portName;
    m_baudrate = baudRate;

    if (!isRunning())
        start();
}

void serialThread::run()
{
    QSerialPort my_port;
    my_port.setPortName(m_portName);
    my_port.setBaudRate(m_baudrate);

    if (!my_port.open(QIODevice::ReadWrite)) {
        emit(error(tr("Can't open %1, error code %2")
                   .arg(m_portName).arg(my_port.error())));
        return;
    }
    while (!m_quit) {
        if (my_port.waitForReadyRead(10000)) {
            // read request
            QByteArray requestData = my_port.readAll();

            //qDebug() << "read data: " << QString(requestData);
            emit(this->request(QString(requestData)));
        }
    }
    my_port.close();
}
