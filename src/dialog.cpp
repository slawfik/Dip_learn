#include "dialog.h"
#include <QSerialPortInfo>
#include "qgridlayout.h"
#include <QSpacerItem>
#include <qdebug.h>

Dialog::Dialog(QWidget *parent) : QDialog(parent) ,m_serialComboBox(new QComboBox)
{
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos)
        m_serialComboBox->addItem(info.portName());

    this->setBaseSize(400,400);
    startButton = new QPushButton("Start connecting");
    m_serialPortLabel.setText("Vyber správny sériový port:");

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(&m_serialPortLabel, 0, 0);
    mainLayout->addWidget(m_serialComboBox, 0, 1);
    mainLayout->addWidget(startButton, 0, 2,2, 1);
    //mainLayout->addWidget()

    connect(startButton, &QPushButton::clicked, this, &Dialog::startCom);

    setLayout(mainLayout);
}

void Dialog::startCom()
{
    qDebug() << "dialog event";
    serialPort = m_serialComboBox->currentText();
    this->done(1);
}

QString Dialog::getSerialPort() const
{
    return serialPort;
}
