#include "hrac.h"
#include <QKeyEvent>
#include <QTimer>
#include <QList>
#include <qgraphicsitem.h>
#include <QDebug>
#include "games/Mario_coin/coin.h"
#include <QGraphicsScene>

Hrac::~Hrac()
{
    delete checkColision_timer;
    delete coinSpawnTimer;
}

Hrac::Hrac(QGraphicsItem *parent) : QGraphicsPixmapItem(parent) {
    score = 0;
    setPixmap(QPixmap(":/games/Mario_coin/textur/hrac.png"));

    checkColision_timer = new QTimer(this);
    connect(checkColision_timer,SIGNAL(timeout()),this,SLOT(check_colision()));

    coinSpawnTimer = new QTimer(this);
    connect(coinSpawnTimer,SIGNAL(timeout()),this,SLOT(spawn_new()));

    coinSpawnTimer->start(3000);

    // start the timer
    checkColision_timer->start(50);
}

void Hrac::keyPressEvent(QKeyEvent *event)    {
    if (event->key() == Qt::Key_Down)   {
        setPos(x(),y()+10);
    } else if (event->key() == Qt::Key_Up)   {
        setPos(x(),y()-10);
    } else if (event->key() == Qt::Key_Left)   {
        setPos(x()-10,y());
    } else if (event->key() == Qt::Key_Right)   {
        setPos(x()+10,y());
    }
}

void Hrac::spawn_new()
{
    Coin* newCoin = new Coin;
    scene()->addItem(newCoin);
}

void Hrac::check_colision()
{
    //qDebug() << "cek";
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i){
        if (typeid(*(colliding_items[i])) == typeid(Coin)){
            // increase the score
            score++;

            // remove them from the scene (still on the heap)
            scene()->removeItem(colliding_items[i]);
            qDebug()<<"inc score: " + QString::number(score);

            // delete them from the heap to save memory
            delete colliding_items[i];
        }
    }
}

