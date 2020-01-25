#include "my_scenes.h"
#include "../../settings.h"

My_scenes::My_scenes()
{

}

QGraphicsPixmapItem *My_scenes::get_napoveda()
{
    QGraphicsPixmapItem* parentItem = new QGraphicsPixmapItem();

    QGraphicsPixmapItem* sipkaVlavo = new QGraphicsPixmapItem(parentItem);
    QGraphicsPixmapItem* sipkaVpravo = new QGraphicsPixmapItem(parentItem);

    QGraphicsTextItem* text1 = new QGraphicsTextItem(parentItem);
    QGraphicsTextItem* text2 = new QGraphicsTextItem(parentItem);

    QGraphicsPixmapItem* potvrenie = new QGraphicsPixmapItem(parentItem);

    QGraphicsTextItem* text3 = new QGraphicsTextItem(parentItem);

    QFont titleFont(FONT_IN_GAME,20);

    text1->setPlainText("Sípkami ");
    text1->setFont(titleFont);
    text1->setPos(WIDTH_SCREAN/4,13*(HIGHT_SCREAN/14));

    sipkaVlavo->setPixmap(QPixmap(":/game/score/games/utils/textur/sipka.png").scaled(60,50,Qt::IgnoreAspectRatio));
    sipkaVlavo->setPos(WIDTH_SCREAN/4+90,13*(HIGHT_SCREAN/14)-10);
    sipkaVpravo->setPixmap(QPixmap(":/game/score/games/utils/textur/sipka.png").scaled(60,50,Qt::IgnoreAspectRatio));
    sipkaVpravo->setRotation(180);
    sipkaVpravo->setPos(WIDTH_SCREAN/4+220,13*(HIGHT_SCREAN/14)+40);

    text2->setPlainText(" vyber z objektov a ");
    text2->setFont(titleFont);
    text2->setPos(WIDTH_SCREAN/4+230,13*(HIGHT_SCREAN/14));

    potvrenie->setPixmap(QPixmap(":/game/score/games/utils/textur/potvrdenie.png").scaled(40,40,Qt::IgnoreAspectRatio));
    potvrenie->setPos(WIDTH_SCREAN/4+420,13*(HIGHT_SCREAN/14));

    text3->setPlainText(" potvrď výber.");
    text3->setFont(titleFont);
    text3->setPos(WIDTH_SCREAN/4+470,13*(HIGHT_SCREAN/14));

    return parentItem;
}
