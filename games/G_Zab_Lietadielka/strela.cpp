#include "strela.h"
#include "../../settings.h"
#include "enemy.h"
#include "boss.h"

Strela::Strela(qreal x,qreal y,QPixmap pa_pix,short hodnota,QGraphicsItem *parent) : hodnota(hodnota)
{
    Q_UNUSED(parent)
    setPos(x,y);
    setPixmap(pa_pix);
    setTransformOriginPoint(pixmap().rect().center());

    is_outOfScrean =false;
    moveTimer.setInterval(100);

    if(hodnota == 0){   // strela vzpustena hracom
        setRotation(-90);
        connect(&moveTimer,SIGNAL(timeout()),this,SLOT(s_moveUp()));
        moveTimer.start();

        check_colision_Timer.setInterval(300);
        connect(&check_colision_Timer,SIGNAL(timeout()),this,SLOT(s_colidingWithEnemy()));
        check_colision_Timer.start();
    } else { // strela od bosa
        setRotation(180);
        connect(&moveTimer,SIGNAL(timeout()),this,SLOT(s_moveDown()));
        moveTimer.start();
        //kolitiu overuje hrac
    }
}

void Strela::s_moveUp()
{
    if (GAME_renderStatus == ENEMY_FIGHT || GAME_renderStatus == BOSS_FIGHT) {
        if(this->y() < -10 && !is_outOfScrean) {//iba raz, nesmie yavola5 signal 2x
            is_outOfScrean = true;
            emit sig_is_outOfScrean(this,false);//inc score false
            emit sig_is_outOfScrean(this);      //pre bosove strely
        } else if(this->y() > -10)
            setY(this->y()-(2*SPEED));
    }
}

void Strela::s_moveDown()
{
    if (GAME_renderStatus == ENEMY_FIGHT || GAME_renderStatus == BOSS_FIGHT) {
        if(this->y() > HIGHT_SCREAN && !is_outOfScrean) {//iba raz, nesmie yavola5 signal 2x
            is_outOfScrean = true;
            emit sig_is_outOfScrean(this,false);//inc score false
        } else if(this->y() < HIGHT_SCREAN)
            setY(this->y()+(2*SPEED));
    }
}

void Strela::s_colidingWithEnemy()
{
    QList<QGraphicsItem *> colliding_items = this->collidingItems();
    for (int i = 0;i < colliding_items.size(); ++i){
        if (typeid(*(colliding_items[i])) == typeid(Enemy)){
            Enemy* it = dynamic_cast<Enemy*>(colliding_items.operator[](i));
            scene()->removeItem(it);
            delete it;
            //delete this
            emit (sig_is_outOfScrean(this,true));
        } else if (typeid(*(colliding_items[i])) == typeid(Boss)){
            Boss* it = dynamic_cast<Boss*>(colliding_items.operator[](i));

            //scene()->removeItem(it);
            //delete it;
            //delete this
            it->decrementHelth();
            emit (sig_is_outOfScrean(this,true));
        }
    }
}
