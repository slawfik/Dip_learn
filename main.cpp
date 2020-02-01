#include "learn_soft.h"
#include <QApplication>
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Learn_soft w;
    w.show();

    return a.exec();
}
