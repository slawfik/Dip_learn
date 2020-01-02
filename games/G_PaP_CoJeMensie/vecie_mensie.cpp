#include "vecie_mensie.h"
#include "../../settings.h"
#include "../utils/my_button.h"
#include <QGraphicsItem>
#include <QDebug>
#include <QMovie>
#include <QKeyEvent>
#include <random>
#include <QLabel>
#include <QStateMachine>

Vecie_mensie::Vecie_mensie(QWidget *parent)
{
    Q_UNUSED(parent)
    //init sceny
    scene = new QGraphicsScene(this);

    scene->setSceneRect(0,0,WIDTH_SCREAN,HIGHT_SCREAN); // make the scene 800x600 instead of infinity by infinity (default)

    QImage aa(":/game/vecsiMensi/games/G_PaP_CoJeMensie/texture/G_mecMen.jpg");
    scene->setBackgroundBrush(QBrush(aa.scaled(WIDTH_SCREAN,HIGHT_SCREAN,Qt::IgnoreAspectRatio)));

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(WIDTH_SCREAN,HIGHT_SCREAN);
    setScene(scene);

    set_Texts_for_scene();

    /*__setup first round__*/
    set_random_Round();
}

Vecie_mensie::~Vecie_mensie()
{
    if(movie){
        delete movie;
    }
    scene->clear();
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
    path = ":/game/vecsiMensi/games/G_PaP_CoJeMensie/texture/" + QString::number(pomL) +".png";
    My_item* item_L = new My_item(true, path,pomL);
    path = ":/game/vecsiMensi/games/G_PaP_CoJeMensie/texture/" + QString::number(pomR) +".png";
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

void Vecie_mensie::showGameOver()
{
    // pop up semi transparent panel
    drawPanel(0,0,WIDTH_SCREAN,HIGHT_SCREAN,Qt::black,0.65);

    // draw panel
    drawPanel(WIDTH_SCREAN/2-250,HIGHT_SCREAN/2-200,500,400,Qt::lightGray,0.75);

    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Super zvladol si to na:"));
    QFont titleFont("Farm to Market Fancy",50);
    titleText->setFont(titleFont);
    titleText->setPos(WIDTH_SCREAN/2 - titleText->boundingRect().width()/2,HIGHT_SCREAN/2-200);
    scene->addItem(titleText);

    // parent item for Button
    QGraphicsRectItem *game_OverButtons_parent = new QGraphicsRectItem();

    My_button* playAgain = new My_button(QString("Hrať znova"),game_OverButtons_parent);
    playAgain->setPos(410,HIGHT_SCREAN/2+50);
    connect(playAgain,SIGNAL(clicked()),this,SLOT(restart_Game()));

    My_button* close = new My_button(QString("Koniec"),game_OverButtons_parent);
    close->setPos(410,HIGHT_SCREAN/2+105);
    connect(close,SIGNAL(clicked()),this,SLOT(close()));

    scene->addItem(game_OverButtons_parent);

    /*__Vyhodnotenie__*/
    if(body > 3) {
        movie =  new QMovie(":/game/score/games/utils/textur/hviezdicky.gif");
        QLabel * aniLabel = new QLabel;
        aniLabel->setAttribute(Qt::WA_TranslucentBackground); //transparet background
        aniLabel->setMovie(movie);
        movie->start();
        aniLabel->setGeometry(WIDTH_SCREAN/2-75,HIGHT_SCREAN/2-120,150,150);

        aniLabel->show();
        scene->addWidget(aniLabel);
    } else {
        movie =  new QMovie(":/game/score/games/utils/textur/hviezdicky2.gif");
        QLabel * aniLabel = new QLabel;
        aniLabel->setAttribute(Qt::WA_TranslucentBackground); //transparet background
        aniLabel->setMovie(movie);
        movie->start();
        aniLabel->setGeometry(WIDTH_SCREAN/2-75,HIGHT_SCREAN/2-120,150,150);

        aniLabel->show();
        scene->addWidget(aniLabel);
    }
}

void Vecie_mensie::set_Texts_for_scene()
{
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
}

void Vecie_mensie::restart_Game()
{
    round_number = 0;
    body = 0;
    if(movie){
        delete movie;
        movie = nullptr;
    }
    scene->clear();
    focusedItems.clear();

    /*Start game*/
    set_Texts_for_scene();
    set_random_Round();
}

void Vecie_mensie::my_ItemPressSlot(My_item* obj)
{
    if(obj != focusedItems.operator[](curent_focus))    {
        changeFocusItem();
    }
    /*vyhodnotenie eventu*/
    if(obj->hodnota < focusedItems.operator[]((curent_focus == 0)? 1 : 0)->hodnota) {
        qDebug() << "OK BOD! ";
        body++;
    }

  #ifdef DEBUG
    qDebug() << "Round number: " << QString::number(round_number);
    qDebug() << "Signal pressed from" << obj->path_ON << " object!";
  #endif

    if(round_number<=5){
        round_number++;
        set_random_Round();
    } else {
        showGameOver();
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
    QStateMachine machine;
    QState *state1 = new QState(&machine);
    QState *state2 = new QState(&machine);

    machine.setInitialState(state1);

    // State 1
    //state1->assignProperty(focusedItems.operator[](curent_focus),"pos", QPointF(68, 200));
    state1->assignProperty(focusedItems.operator[](curent_focus), "rotation", qreal(270));
    state1->assignProperty(focusedItems.operator[](curent_focus), "opacity", qreal(1));
    //QAbstractAnimation *a = state1->addTransition(focusedItems.operator[](curent_focus),SIGNAL(pressed(My_item*)),state1);

    changeFocusItem();

    state2->assignProperty(focusedItems.operator[](curent_focus), "rotation", qreal(270));
    state2->assignProperty(focusedItems.operator[](curent_focus), "opacity", qreal(1));
    machine.start();
    //    connect(item_L,SIGNAL(pressed(My_item*)),this,SLOT(my_ItemPressSlot(My_item*)));

}

void Vecie_mensie::pressEnter()
{
    my_ItemPressSlot(focusedItems.operator[](curent_focus));
}

