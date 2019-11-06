#include "learn_soft.h"
#include "ui_learn_soft.h"
#include <QDebug>
#include <QResizeEvent>

void Learn_soft::resizeEvent(QResizeEvent *event)
{

}

Learn_soft::Learn_soft(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Learn_soft)
{
    ui->setupUi(this);
}

Learn_soft::~Learn_soft()
{
    delete ui;
}

