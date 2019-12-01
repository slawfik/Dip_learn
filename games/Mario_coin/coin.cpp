#include "coin.h"
#include <QImage>
#include <QPixmap>
#include <QTimer>
#include <QDebug>
#include <stdlib.h>
#include "../../settings.h"

Coin::~Coin()
{
    delete timer;
    qDebug() << "delete timer";

}

Coin::Coin(QGraphicsItem *parent)   {
    Q_UNUSED(parent)
    int spawn_poz_x = rand() % WIDTH_SCREAN-100;
    int spawn_poz_y = rand() % HIGHT_SCREAN-100;
    smer_pohybu = true;

    setPos(spawn_poz_x,spawn_poz_y);
    setPixmap(QPixmap(":/games/Mario_coin/textur/coin.png"));

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    // start the timer
    timer->start(50);
}

void Coin::move()
{
    if(smer_pohybu){
        setY(y()+5);
        smer_pohybu = false;
    } else {
        setY(y()-5);
        smer_pohybu = true;
    }

}

