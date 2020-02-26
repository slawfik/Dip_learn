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

    text1->setPlainText("Šípkami ");
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

    potvrenie->setPixmap(QPixmap(":/game/score/games/utils/textur/xx.png").scaled(50,50,Qt::IgnoreAspectRatio));
    potvrenie->setPos(WIDTH_SCREAN/4+415,13*(HIGHT_SCREAN/14-1));

    text3->setPlainText(" potvrď výber.");
    text3->setFont(titleFont);
    text3->setPos(WIDTH_SCREAN/4+470,13*(HIGHT_SCREAN/14));

    return parentItem;
}

QGraphicsPixmapItem *My_scenes::get_infoWindow_with_Picture(QString infoString, QString pixmap_path)
{
    QGraphicsPixmapItem* parentItem = new QGraphicsPixmapItem();

    QGraphicsRectItem* panel = new QGraphicsRectItem(WIDTH_SCREAN/2-300,HIGHT_SCREAN/2-200,600,400,parentItem);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkGray);
    panel->setBrush(brush);
    panel->setOpacity(0.6);

    if(pixmap_path != "_") {
        QGraphicsPixmapItem* postavicka = new QGraphicsPixmapItem(parentItem);
        postavicka->setPixmap(QPixmap(pixmap_path).scaled(150,250));
        postavicka->setPos(QPointF(WIDTH_SCREAN/2-75,HIGHT_SCREAN/2-60));
    }
    QGraphicsTextItem* text1 = new QGraphicsTextItem(parentItem);

    QFont titleFont(FONT_IN_GAME,FONT_GAME_SIZE1);
    text1->setPlainText(infoString);
    text1->setFont(titleFont);
    text1->setPos(WIDTH_SCREAN/2-250,HIGHT_SCREAN/2-200);
    text1->setTextWidth(500);

    return parentItem;
}
