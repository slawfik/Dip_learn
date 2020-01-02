#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

class Dialog : public QDialog
{
    Q_OBJECT
public:    
    Dialog(QWidget *parent = nullptr);

    QString getSerialPort() const;

private slots:
    void startCom();

private:
    QString serialPort;
    QLabel m_serialPortLabel;
    QLabel m_popis1;
    QLabel m_popis2;
    QPushButton *startButton;
    QComboBox *m_serialComboBox;
};

#endif // DIALOG_H
