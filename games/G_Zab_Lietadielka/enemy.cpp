#include "enemy.h"
#include "../../settings.h"

Enemy::Enemy(QString pixMapPath,QSize velkost,qreal x,qreal y,QGraphicsItem *parent)
{
    setParentItem(parent);
    a = new QPixmap(pixMapPath);
    setPixmap(a->scaled(velkost));

    setPos(x,y);

}

Enemy::~Enemy()
{
    if(updateMovment_Timer_UpDown)
        delete updateMovment_Timer_UpDown;
    if(updateMovment_Timer_LeftRight)
        delete updateMovment_Timer_LeftRight;
    delete a;
}

void Enemy::startMovment_downUp(bool onlyDown)
{
    updateMovment_Timer_UpDown = new QTimer();
    updateMovment_Timer_UpDown->setInterval(30);

    if(onlyDown)
        connect(updateMovment_Timer_UpDown,SIGNAL(timeout()),this,SLOT(s_update_movment_down()));
     else
        connect(updateMovment_Timer_UpDown,SIGNAL(timeout()),this,SLOT(s_update_movment_up()));
    updateMovment_Timer_UpDown->start();
}

void Enemy::startMovment_leftRight(bool onlyLeft)
{

}

void Enemy::s_update_movment_down()
{
    if (GAME_renderStatus == ENEMY_FIGHT || GAME_renderStatus == BOSS_FIGHT) {
        if(this->y() > HIGHT_SCREAN && !is_outOfScrean) {//iba raz, nesmie yavola5 signal 2x
            is_outOfScrean = true;
            emit sig_is_outOfScrean(this);
        } else if(this->y() < HIGHT_SCREAN)
            setY(this->y()+SPEED);
    }
}
void Enemy::s_update_movment_up()
{
    if (GAME_renderStatus == ENEMY_FIGHT || GAME_renderStatus == BOSS_FIGHT) {
        if(this->y() < HIGHT_SCREAN && !is_outOfScrean) { //iba raz
            is_outOfScrean = true;
            emit sig_is_outOfScrean(this);
        } else if(this->y() > 0)
            setY(this->y()-SPEED);
    }
}
void Enemy::s_update_movment_left()
{
    if (GAME_renderStatus == ENEMY_FIGHT || GAME_renderStatus == BOSS_FIGHT) {

    }
}
void Enemy::s_update_movment_right()
{
    if (GAME_renderStatus == ENEMY_FIGHT || GAME_renderStatus == BOSS_FIGHT) {

    }
}

