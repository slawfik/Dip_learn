#include "mario_coin.h"
#include "hrac.h"
#include "coin.h"
#include "../../settings.h"

Mario_coin::Mario_coin(QWidget *parent)
{
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,HIGHT_SCREAN,WIDTH_SCREAN); // make the scene 800x600 instead of infinity by infinity (default)
    setBackgroundBrush(QBrush(QImage(":/games/Mario_coin/textur/bg2.jpg")));

    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(HIGHT_SCREAN,WIDTH_SCREAN);

    Hrac* hrac = new Hrac();
    hrac->setPos(0,0);
    hrac->setFlag(QGraphicsItem::ItemIsFocusable);
    hrac->setFocus();
    scene->addItem(hrac);


    show();
}

