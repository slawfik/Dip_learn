#include "najdi_obrazok.h"
#include "../../settings.h"
#include "../utils/my_button.h"
#include "../utils/my_scenes.h"
#include <QDebug>

#define SPRAVNA_ODPOVED 0

Najdi_obrazok::Najdi_obrazok(QWidget *parent)
{
    Q_UNUSED(parent)
    //init sceny
    scene = new QGraphicsScene(this);

    scene->setSceneRect(0,0,WIDTH_SCREAN,HIGHT_SCREAN); // make the scene 800x600 instead of infinity by infinity (default)

    scene->setBackgroundBrush(QBrush(QColor::fromRgb(129, 69, 99)));
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(WIDTH_SCREAN,HIGHT_SCREAN);
    setScene(scene);

    showMenu();
}

Najdi_obrazok::~Najdi_obrazok()
{
    //Removes and deletes all items from the scene
    scene->clear();
    delete scene;
    if(timer)
        delete timer;
    if(movie){
        qDebug() << "~najdi_obrazok.cpp 37 delete movie";
        delete movie;
    }
    if(l_myItems.size())
        l_myItems.clear();
}

void Najdi_obrazok::moveLeft()
{
    l_myItems_iter.operator*()->focusOut();
    if(l_myItems_iter != l_myItems.end()-1)   {
        l_myItems_iter++;
        l_myItems_iter.operator*()->focusIn();
    } else {
        l_myItems_iter = l_myItems.begin();
        l_myItems_iter.operator*()->focusIn();
    }
}

void Najdi_obrazok::moveRight()
{
    l_myItems_iter.operator*()->focusOut();
    if(l_myItems_iter != l_myItems.begin())   {
        l_myItems_iter--;
        l_myItems_iter.operator*()->focusIn();
    } else {
        l_myItems_iter = l_myItems.end()-1;
        l_myItems_iter.operator*()->focusIn();
    }
}

void Najdi_obrazok::pressEnter()
{
    emit(l_myItems_iter.operator*()->pressed(l_myItems_iter.operator*()));
}

void Najdi_obrazok::showMenu()
{
    // parent item for Button & Image
    my_Items *menu_Items_Parent = new my_Items();

    my_Items *obr_auto = new my_Items(QPointF((WIDTH_SCREAN/2)-250,HIGHT_SCREAN/2-125),
                                      ":/game/najdiObr/games/G_PaP_NajdiObrazok/textur/AUTO4.png",
                                      QSize(200,200),
                                      0,menu_Items_Parent);

    my_Items *obr_huby = new my_Items(QPointF(WIDTH_SCREAN/2,HIGHT_SCREAN/2-125),
                                      ":/game/najdiObr/games/G_PaP_NajdiObrazok/textur/hrib1.png",
                                      QSize(200,200),
                                      0,menu_Items_Parent);

    connect(obr_huby,SIGNAL(pressed(my_Items*)),this,SLOT(startGame_huby(my_Items*)));
    connect(obr_auto,SIGNAL(pressed(my_Items*)),this,SLOT(startGame_auto(my_Items*)));
    l_myItems.append(obr_auto);
    l_myItems.append(obr_huby);

    //set focus
    l_myItems.at(0)->focusIn();
    l_myItems_iter = l_myItems.begin();

    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Vyber si s akými obrázkami budeš hrať."));
    QFont titleFont(FONT_IN_GAME,50);
    titleText->setFont(titleFont);
    titleText->setPos(WIDTH_SCREAN/2 - titleText->boundingRect().width()/2,HIGHT_SCREAN/8);
    scene->addItem(titleText);

    scene->addItem(menu_Items_Parent);

    scene->addItem(My_scenes::get_napoveda());
}

void Najdi_obrazok::startGame_auto(my_Items* pa_item)
{
    Q_UNUSED(pa_item)
    scene->clear();

    //text
    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Pozorne si prezri a zapametaj obrázok."));
    QFont titleFont(FONT_IN_GAME,50);
    titleText->setFont(titleFont);
    titleText->setPos(WIDTH_SCREAN/2 - titleText->boundingRect().width()/2,HIGHT_SCREAN/8);
    scene->addItem(titleText);

    //vzorovy obrazok
    QSize itemSize(400,400);
    my_Items *item = new my_Items(QPointF(WIDTH_SCREAN/2-itemSize.width()/2,HIGHT_SCREAN/2-itemSize.height()/2)
                                  ,":/game/najdiObr/games/G_PaP_NajdiObrazok/textur/AUTO1.png",
                                  itemSize,0);
    scene->addItem(item);

    //Casomiera vzoroveho obrazku
    waitTime = 15;
    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(choice_auto()));

    //Informácie o zostávajúcom čase
    time_text = new QGraphicsTextItem(QString("%1 sec").arg(waitTime));
    QFont Timer_font(FONT_IN_GAME,50);
    time_text->setFont(Timer_font);
    time_text->setPos(WIDTH_SCREAN-100 - time_text->boundingRect().width()/2,HIGHT_SCREAN-100);
    scene->addItem(time_text);

    //start timer
    timer->start(1000);
}

void Najdi_obrazok::startGame_huby(my_Items* pa_item)
{
    Q_UNUSED(pa_item)
    scene->clear();

    //text
    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Pozorne si prezri a zapametaj obrázok."));
    QFont titleFont(FONT_IN_GAME,50);
    titleText->setFont(titleFont);
    titleText->setPos(WIDTH_SCREAN/2 - titleText->boundingRect().width()/2,HIGHT_SCREAN/8);
    scene->addItem(titleText);

    //vzorovy obrazok
    QSize itemSize(400,400);
    my_Items *item = new my_Items(QPointF(WIDTH_SCREAN/2-itemSize.width()/2,HIGHT_SCREAN/2-itemSize.height()/2)
                                  ,":/game/najdiObr/games/G_PaP_NajdiObrazok/textur/hrib1.png",
                                  itemSize,0);
    scene->addItem(item);

    //Casomiera vzoroveho obrazku
    waitTime = 15;
    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(choice_huby()));

    //Informácie o zostávajúcom čase
    time_text = new QGraphicsTextItem(QString("%1 sec").arg(waitTime));
    QFont Timer_font(FONT_IN_GAME,50);
    time_text->setFont(Timer_font);
    time_text->setPos(WIDTH_SCREAN-100 - time_text->boundingRect().width()/2,HIGHT_SCREAN-100);
    scene->addItem(time_text);

    //start timer
    timer->start(1000);


}

void Najdi_obrazok::choice_auto()
{
    //qDebug() << "decrement time";
    waitTime--;
    time_text->setPlainText(QString("%1 sec").arg(waitTime));
    if(!waitTime) {
        timer->stop();
        scene->clear();
        //clear items list
        l_myItems.clear();

        //pozadie platno
        scene->addItem(My_button::drawPanel(x_ODSADENIE_PLATNA,y_ODSADENIE_PLATNA,
                                            WIDTH_SCREAN-2*x_ODSADENIE_PLATNA,HIGHT_SCREAN-2*y_ODSADENIE_PLATNA,
                                            Qt::yellow,0.6));

        //text
        QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Vyber rovnaký obrázok aký si už videl: "));
        QFont titleFont(FONT_IN_GAME,50);
        titleText->setFont(titleFont);
        titleText->setPos(WIDTH_SCREAN/2 - titleText->boundingRect().width()/2,HIGHT_SCREAN/8);
        scene->addItem(titleText);

        //napoveda
        scene->addItem(My_scenes::get_napoveda());

        // parent item for Button
        my_Items *parentItem_myItems = new my_Items();
        QSize size_IMG(150,200);

        my_Items *item = new my_Items(QPointF(WIDTH_SCREAN*3/12,200),":/game/najdiObr/games/G_PaP_NajdiObrazok/textur/AUTO4.png",size_IMG,3,parentItem_myItems);
        l_myItems.append(item);
        connect(item,SIGNAL(pressed(my_Items*)),this,SLOT(choiced_my_Item_Slot(my_Items*)));

        item = new my_Items(QPointF(WIDTH_SCREAN*3/12,400),":/game/najdiObr/games/G_PaP_NajdiObrazok/textur/AUTO3.png",size_IMG,2,parentItem_myItems);
        l_myItems.append(item);
        connect(item,SIGNAL(pressed(my_Items*)),this,SLOT(choiced_my_Item_Slot(my_Items*)));

        item = new my_Items(QPointF(WIDTH_SCREAN*6/12,200),":/game/najdiObr/games/G_PaP_NajdiObrazok/textur/AUTO1.png",size_IMG,0,parentItem_myItems);
        l_myItems.append(item);
        connect(item,SIGNAL(pressed(my_Items*)),this,SLOT(choiced_my_Item_Slot(my_Items*)));

        item = new my_Items(QPointF(WIDTH_SCREAN*6/12,400),":/game/najdiObr/games/G_PaP_NajdiObrazok/textur/AUTO2.png",size_IMG,1,parentItem_myItems);
        l_myItems.append(item);
        connect(item,SIGNAL(pressed(my_Items*)),this,SLOT(choiced_my_Item_Slot(my_Items*)));

        scene->addItem(parentItem_myItems);

        //set focus
        l_myItems.at(0)->focusIn();
        l_myItems_iter = l_myItems.begin();
    }
}

void Najdi_obrazok::choice_huby()
{
    //qDebug() << "decrement time";
    waitTime--;
    time_text->setPlainText(QString("%1 sec").arg(waitTime));
    if(!waitTime) {
        timer->stop();
        scene->clear();
        //clear items list
        l_myItems.clear();

        //pozadie platno
        scene->addItem(My_button::drawPanel(x_ODSADENIE_PLATNA,y_ODSADENIE_PLATNA,
                                            WIDTH_SCREAN-2*x_ODSADENIE_PLATNA,HIGHT_SCREAN-2*y_ODSADENIE_PLATNA,
                                            Qt::yellow,0.6));

        //text
        QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Vyber rovnaký obrázok aký si už videl: "));
        QFont titleFont(FONT_IN_GAME,50);
        titleText->setFont(titleFont);
        titleText->setPos(WIDTH_SCREAN/2 - titleText->boundingRect().width()/2,HIGHT_SCREAN/8);
        scene->addItem(titleText);

        //napoveda
        scene->addItem(My_scenes::get_napoveda());

        // parent item for my_Items
        my_Items *parentItem_myItems = new my_Items();
        QSize size_IMG(150,200);

        my_Items *item = new my_Items(QPointF(WIDTH_SCREAN*3/12,200),":/game/najdiObr/games/G_PaP_NajdiObrazok/textur/hrib4.png",size_IMG,3,parentItem_myItems);
        l_myItems.append(item);
        connect(item,SIGNAL(pressed(my_Items*)),this,SLOT(choiced_my_Item_Slot(my_Items*)));

        item = new my_Items(QPointF(WIDTH_SCREAN*3/12,400),":/game/najdiObr/games/G_PaP_NajdiObrazok/textur/hrib3.png",size_IMG,2,parentItem_myItems);
        l_myItems.append(item);
        connect(item,SIGNAL(pressed(my_Items*)),this,SLOT(choiced_my_Item_Slot(my_Items*)));

        item = new my_Items(QPointF(WIDTH_SCREAN*6/12,200),":/game/najdiObr/games/G_PaP_NajdiObrazok/textur/hrib1.png",size_IMG,0,parentItem_myItems);
        l_myItems.append(item);
        connect(item,SIGNAL(pressed(my_Items*)),this,SLOT(choiced_my_Item_Slot(my_Items*)));

        item = new my_Items(QPointF(WIDTH_SCREAN*6/12,400),":/game/najdiObr/games/G_PaP_NajdiObrazok/textur/hrib2.png",size_IMG,1,parentItem_myItems);
        l_myItems.append(item);
        connect(item,SIGNAL(pressed(my_Items*)),this,SLOT(choiced_my_Item_Slot(my_Items*)));

        scene->addItem(parentItem_myItems);

        //set focus
        l_myItems.at(0)->focusIn();
        l_myItems_iter = l_myItems.begin();
    }
}

void Najdi_obrazok::choiced_my_Item_Slot(my_Items * obj)
{
    obj->start_press_Animation();
    if(obj->getHodnota() == SPRAVNA_ODPOVED){
        showGameOver(true,"Super zvladol si to na:");
    } else {
        showGameOver(false,"Nevadí nabudúce to pôjde :)");
    }
}

void Najdi_obrazok::showGameOver(bool win,QString data)
{
    // pop up semi transparent panel
    scene->addItem(My_button::drawPanel(0,0,WIDTH_SCREAN,HIGHT_SCREAN,Qt::black,0.65));

    // draw panel
    scene->addItem(My_button::drawPanel(WIDTH_SCREAN/2-250,HIGHT_SCREAN/2-200,500,400,Qt::lightGray,0.75));

    QGraphicsTextItem* titleText = new QGraphicsTextItem(data);
    titleText->setTextWidth(400);
    QFont titleFont("Farm to Market Fancy",50);
    titleText->setFont(titleFont);
    titleText->setPos(WIDTH_SCREAN/2 - titleText->boundingRect().width()/2,HIGHT_SCREAN/2-200);
    scene->addItem(titleText);

    // parent item for Button
    QGraphicsRectItem *game_OverButtons_parent = new QGraphicsRectItem();

    My_button* playAgain = new My_button(QString("Hrať znova"),game_OverButtons_parent);
    playAgain->setPos(410,HIGHT_SCREAN/2+50);
    connect(playAgain,SIGNAL(clicked()),this,SLOT(restartGame()));

    My_button* close = new My_button(QString("Koniec"),game_OverButtons_parent);
    close->setPos(410,HIGHT_SCREAN/2+105);
    connect(close,SIGNAL(clicked()),this,SLOT(close()));

    scene->addItem(game_OverButtons_parent);

    /*ADD Gif*/
    if(win) {
        scene->addWidget(My_button::showGif(movie,QString(":/game/score/games/utils/textur/hviezdicky.gif"),QPoint(WIDTH_SCREAN/2-75,HIGHT_SCREAN/2-110)));
    } else {
        scene->addWidget(My_button::showGif(movie,QString(":/game/score/games/utils/textur/smajlik.gif"),QPoint(WIDTH_SCREAN/2+50,HIGHT_SCREAN/2-110)));
    }
}

void Najdi_obrazok::restartGame()
{
    if(movie != nullptr)
        delete movie;
    if(timer)
        delete timer;

    scene->clear();
    l_myItems.clear();
    showMenu();
}
