#include "boss.h"
#include "strela.h"
#include "../../settings.h"
#include "../utils/my_button.h"
#include <QtMath>
#include <QDebug>
Boss::Boss(QPixmap* pixMap,QSize velkost,qreal x,qreal y,QGraphicsItem *parent)
{
    setParentItem(parent);
    setPixmap(pixMap->scaled(velkost));

    setPos(x,y);

    timerStrelby.setInterval(2500);
    timerStrelby.setSingleShot(true);
    connect(&timerStrelby,SIGNAL(timeout()),this,SLOT(s_Strielaj()));
    timerStrelby.start();
}

Boss::~Boss()
{

}

void Boss::decrementHelth()
{
    helth--;
    if(!helth)  {
        emit sig_destroy_boss();
    }
    healt->setPlainText(QString::number(helth));
    if(helth <= 0)
        bar[7]->hide();
    else if(helth < 10)
        bar[6]->hide();
    else if(helth < 20)
        bar[5]->hide();
    else if(helth < 30)
        bar[4]->hide();
    else if(helth < 40)
        bar[3]->hide();
    else if(helth < 50)
        bar[2]->hide();
    else if(helth < 60)
        bar[1]->hide();
    else if(helth < 70)
        bar[0]->hide();
    else if(helth < 80)
        bar[9]->hide();
    else if(helth < 90)
        bar[8]->hide();



}

void Boss::add_HealthBar()
{
    healt = My_button::show_own_TitleText(QString::number(helth),QPoint(30,HIGHT_SCREAN-70),FONT_GAME_SIZE2,false);
    scene()->addItem(healt);

    QGraphicsRectItem* rect;
    for (int i = 0;i<10;++i){
        //qDebug() << QString("x= ") + QString::number((qCos((i / 10.0) * 6.28) * 30)+60) + QString("__y= ") + QString::number((qSin((i / 10.0) * 6.28) * 30)+100);
        rect = new QGraphicsRectItem((qCos((i / 10.0) * 6.28) * 30)+50,(qSin((i / 10.0) * 6.28) * 30)+HIGHT_SCREAN-50,10,10);
        rect->setBrush(QBrush(Qt::red));
        rect->setTransformOriginPoint(rect->rect().center());
        switch(i){
            case 9:
                rect->setRotation(-15);
                break;
            case 8:
                rect->setRotation(-35);
                break;
            case 1:
                rect->setRotation(45);
                break;
            case 2:
                rect->setRotation(-55);
                break;
            case 4:
                rect->setRotation(-25);
                break;
            case 5:
                rect->setRotation(-75);
                break;
            case 6:
                rect->setRotation(-60);
                break;
            case 7:
                rect->setRotation(-35);
                break;
            default:
                break;
        }

        scene()->addItem(rect);
        bar[i] = rect;
        //QPointF p(qCos((i / 10.0) * 6.28) * 50,qSin((i / 10.0) * 6.28) * 50);
    }
}

void Boss::s_Strielaj()
{
    if(GAME_renderStatus != GAME_OWER) {
        Strela* shoot = new Strela(this->x()-100,20,QPixmap(":/game/lietadla/games/G_Zab_Lietadielka/textur/strela_red.png").scaled(15,40),1);
        connect(shoot,SIGNAL(sig_is_outOfScrean(Strela *)),this,SLOT(s_deleteStrelu(Strela *)));
        scene()->addItem(shoot);

        shoot = new Strela(this->x()-17,30,QPixmap(":/game/lietadla/games/G_Zab_Lietadielka/textur/strela_red.png").scaled(15,40),1);
        connect(shoot,SIGNAL(sig_is_outOfScrean(Strela *)),this,SLOT(s_deleteStrelu(Strela *)));
        scene()->addItem(shoot);

        shoot = new Strela(this->x()+65,40,QPixmap(":/game/lietadla/games/G_Zab_Lietadielka/textur/strela_red.png").scaled(15,40),1);
        connect(shoot,SIGNAL(sig_is_outOfScrean(Strela *)),this,SLOT(s_deleteStrelu(Strela *)));
        scene()->addItem(shoot);

        timerStrelby.setInterval((rand()%4000)+2500);
        timerStrelby.start();
    }
}

void Boss::s_deleteStrelu(Strela * pa)
{
    disconnect(pa,SIGNAL(sig_is_outOfScrean(Strela *)),this,SLOT(s_deleteStrelu(Strela *)));
    scene()->removeItem(pa);
    delete  pa;
}
