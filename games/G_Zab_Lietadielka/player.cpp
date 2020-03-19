#include "player.h"
#include "../../settings.h"

Player::Player(qreal x,qreal y,QPixmap pixmap,QGraphicsItem *parent)
{
    Q_UNUSED(parent)
    setPos(x,y);
    setPixmap(pixmap);
    redy_bulletTimer.setInterval(1200);
    redy_bulletTimer.setSingleShot(true);
    connect(&redy_bulletTimer,SIGNAL(timeout()),this,SLOT(s_setRedyBullet()));
}

Player::~Player()
{

}

void Player::goDown()
{
    if (GAME_renderStatus == ENEMY_FIGHT || GAME_renderStatus == BOSS_FIGHT) {
        if(this->y()+SPEED < HIGHT_SCREAN)
            this->setY(this->y()+SPEED+SPEED);
    }
}

void Player::goUp()
{
    if (GAME_renderStatus == ENEMY_FIGHT || GAME_renderStatus == BOSS_FIGHT) {
        if(this->y()-SPEED > 0)
            this->setY(this->y()-SPEED-SPEED);
    }
}

void Player::goLeft()
{
    if (GAME_renderStatus == ENEMY_FIGHT || GAME_renderStatus == BOSS_FIGHT) {
        if(this->x()-SPEED > 0)
            this->setX(this->x()-SPEED-SPEED);
    }
}

void Player::goRight()
{
    if (GAME_renderStatus == ENEMY_FIGHT || GAME_renderStatus == BOSS_FIGHT) {
        if(this->x()+SPEED < WIDTH_SCREAN)
            this->setX(this->x()+SPEED+SPEED);
    }
}

Strela* Player::bullet(bool left)
{
    if (GAME_renderStatus == ENEMY_FIGHT || GAME_renderStatus == BOSS_FIGHT) {
        if(redy_bullet){
            if(!left)   {
                redy_bulletTimer.start();
                return new Strela(this->x()+84,this->y()-26,QPixmap(":/game/lietadla/games/G_Zab_Lietadielka/textur/strela_blue.png").scaled(35,15),0);
            } else {
                return new Strela(this->x()-16,this->y()-26,QPixmap(":/game/lietadla/games/G_Zab_Lietadielka/textur/strela_blue.png").scaled(35,15),0);

            }
        } else {
            return nullptr;
        }
    } else
        return nullptr;
}

void Player::s_setRedyBullet()
{
    redy_bullet = true;
}
