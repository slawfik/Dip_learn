#ifndef SERIALTHREAD_H
#define SERIALTHREAD_H

#include <QThread>
#include <QWaitCondition>
#include <QtSerialPort>

class serialThread : public QThread
{
    Q_OBJECT
public:
    void set_run(QString portName,qint32 baudRate);
    explicit serialThread(QObject *parent = nullptr);
    ~serialThread();

signals:
    void request(const QString &s);
    void error(const QString &s);
    void timeout(const QString &s);

private:
    void run() override;

    QString m_portName;
    bool m_quit = false;
    qint32 m_baudrate;
};

#endif // SERIALTHREAD_H
