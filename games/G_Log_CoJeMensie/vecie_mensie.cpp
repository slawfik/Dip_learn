#include "vecie_mensie.h"
#include "../../settings.h"
#include <QGraphicsItem>
#include <QDebug>
#include <QKeyEvent>
#include <random>

Vecie_mensie::Vecie_mensie(QWidget *parent)
{
    Q_UNUSED(parent)
    //init sceny
    scene = new QGraphicsScene(this);

    scene->setSceneRect(0,0,WIDTH_SCREAN,HIGHT_SCREAN); // make the scene 800x600 instead of infinity by infinity (default)

    QImage aa(":/game/vecsiMensi/games/G_Log_CoJeMensie/texture/G_mecMen.jpg");
    scene->setBackgroundBrush(QBrush(aa.scaled(WIDTH_SCREAN,HIGHT_SCREAN,Qt::IgnoreAspectRatio)));

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(WIDTH_SCREAN,HIGHT_SCREAN);
    setScene(scene);

    drawPanel(100,100,WIDTH_SCREAN-200,HIGHT_SCREAN-200,Qt::yellow/*darkYellow*/,0.5);

    /*__set Title text__*/
    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Čo je menšie?"));
    titleText->setFont(QFont("Farm to Market Fancy",50));
    titleText->setPos(WIDTH_SCREAN/2 - titleText->boundingRect().width()/2,150);
    scene->addItem(titleText);

    /*__set napoveda text__*/
    QGraphicsTextItem* napoveda = new QGraphicsTextItem(QString("Šípkami označ a potvrď čo je v reálnom živote menšie."));
    napoveda->setFont(QFont("Farm to Market Fancy",24));
    napoveda->setPos(WIDTH_SCREAN/2 - napoveda->boundingRect().width()/2,HIGHT_SCREAN- 150);
    scene->addItem(napoveda);

    /*__setup first round__*/
    set_random_Round();
}

void Vecie_mensie::drawPanel(int x, int y, int width, int height, QColor color, double opacity){
    // draws a panel at the specified location with the specified properties
    QGraphicsRectItem* panel = new QGraphicsRectItem(x,y,width,height);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);
    panel->setBrush(brush);
    panel->setOpacity(opacity);
    scene->addItem(panel);
}

void Vecie_mensie::set_random_Round()
{
    int pomL = rand()%7;
    pomL = pomL== 0 ? 7 : pomL;
    int pomR = pomL;
    QString path;
  #ifdef DEBUG
    qDebug() << "focusItems_size= " << QString::number(focusedItems.size());
  #endif
    if(focusedItems.size()) {
      #ifdef DEBUG
        qDebug() << "delete old items " << QString::number(focusedItems.size());
      #endif
        scene->removeItem(focusedItems.operator[](0));
        scene->removeItem(focusedItems.operator[](1));
        delete focusedItems.operator[](0);
        delete focusedItems.operator[](1);
        focusedItems.clear();
    }
    while(pomR == pomL) {
        pomR = rand()%7;
        pomR = pomR== 0 ? 7 : pomR;
    }
    path = ":/game/vecsiMensi/games/G_Log_CoJeMensie/texture/" + QString::number(pomL) +".png";
    My_item* item_L = new My_item(true, path,pomL);
    path = ":/game/vecsiMensi/games/G_Log_CoJeMensie/texture/" + QString::number(pomR) +".png";
    My_item* item_R = new My_item(false,path,pomR);

    connect(item_L,SIGNAL(pressed(My_item*)),this,SLOT(my_ItemPressSlot(My_item*)));
    connect(item_R,SIGNAL(pressed(My_item*)),this,SLOT(my_ItemPressSlot(My_item*)));

    focusedItems.push_back(item_L);
    focusedItems.push_back(item_R);
    scene->addItem(item_L);
    scene->addItem(item_R);

    /*__seting Focus flag __*/
    item_L->setFlag(QGraphicsItem::ItemIsFocusable, true);
    item_R->setFlag(QGraphicsItem::ItemIsFocusable, true);
    /*__set Focus__*/
    curent_focus = 0;
    focusedItems.operator[](curent_focus)->focusIn();
}

void Vecie_mensie::my_ItemPressSlot(My_item* obj)
{
    if(obj != focusedItems.operator[](curent_focus))    {
        changeFocusItem();
    }
    /*vyhodnotenie eventu*/
    if(obj->hodnota < focusedItems.operator[]((curent_focus == 0)? 1 : 0)->hodnota) {
        qDebug() << "OK BOD! ";
    }

  #ifdef DEBUG
    qDebug() << "Round number: " << QString::number(round_number);
    qDebug() << "Signal pressed from" << obj->path_ON << " object!";
  #endif

    if(round_number<=5){
        round_number++;
        set_random_Round();
    }
}

void Vecie_mensie::changeFocusItem()
{
    focusedItems.operator[](curent_focus)->focusOut();
    curent_focus++;
    if(curent_focus>=focusedItems.size()){
        curent_focus =0;
    }
    focusedItems.operator[](curent_focus)->focusIn();

}

void Vecie_mensie::keyPressEvent(QKeyEvent *event)
{
   if (event->key() == Qt::Key_Tab)    {
        changeFocusItem();
   }
}

void Vecie_mensie::pressTab()
{
    changeFocusItem();
}

void Vecie_mensie::pressEnter()
{
    if(focusedItems.operator[](curent_focus)->hodnota < focusedItems.operator[]((curent_focus == 0)? 1 : 0)->hodnota){
        qDebug() << "OK BOD! ";
    }

#ifdef DEBUG
  qDebug() << "Round number: " << QString::number(round_number);
  qDebug() << "Signal pressed from" << focusedItems.operator[](curent_focus)->path_ON << " object!";
#endif

  if(round_number<=5){
      round_number++;
      set_random_Round();
  }
}

