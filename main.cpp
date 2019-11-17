#include "learn_soft.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Learn_soft w;
    w.show();
    /*Mario_coin *game = new Mario_coin();
    game->show();/*/

    return a.exec();
}
