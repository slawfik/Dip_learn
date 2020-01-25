//https://www.google.com/search?q=strom+rocne+obdobia&client=ubuntu&tbm=isch&tbs=rimg:CRoPBD5HpcUQImA4n7kMjR1_1g3c0-yxoFPrSVg_1roGP758ck-r7eYzgDkujZIlI7-7ICR0vw6-cz1NuPCPHGdwPFQOE1H8Lh-TZxEh39vfPU_1lMXFGRzTmmtDAUerjbVtQBd6KWlSSsNWhQqEgk4n7kMjR1_1gxEQICMW5n0BHSoSCXc0-yxoFPrSEfUAulpaJ2lbKhIJVg_1roGP758cRh-S52sNrV-cqEgkk-r7eYzgDkhE006PXkohJaSoSCejZIlI7-7ICEVh-dhy3vT-FKhIJR0vw6-cz1NsRc-dsA7zH4rYqEgmPCPHGdwPFQBF8fCOppcTjyyoSCeE1H8Lh-TZxEdy7w1ks-73WKhIJEh39vfPU_1lMRGLxlXJX-hQMqEgkXFGRzTmmtDBFpM7afXwKFdioSCQUerjbVtQBdEbk5AyokRkpFKhIJ6KWlSSsNWhQRdiJD-0qte0Rhh5txqrO_1wd0&tbo=u&sa=X&ved=2ahUKEwj78KXT2Z7nAhUSblAKHc0aDOYQuIIBegQIARA5&biw=1280&bih=922&dpr=1
#include "rocne_obdobia.h"
#include "../../settings.h"
#include "../utils/my_button.h"
#include "../utils/my_scenes.h"
#include <QDebug>
#include <QKeyEvent>
#include <qrandom.h>
#include <QThread>

Rocne_obdobia::Rocne_obdobia(QWidget *parent)
{
    Q_UNUSED(parent)
    //init sceny
    scene = new QGraphicsScene(this);

    scene->setSceneRect(0,0,WIDTH_SCREAN,HIGHT_SCREAN); // make the scene 800x600 instead of infinity by infinity (default)

    scene->setBackgroundBrush(QBrush(QColor::fromRgb(129, 80, 50)));
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(WIDTH_SCREAN,HIGHT_SCREAN);
    setScene(scene);

    startFirstPart_pexeso();

    scoreText_Item = new QGraphicsTextItem();
    scoreText_Item->setPlainText("0 bodov");
    QFont titleFont(FONT_IN_GAME,FONT_GAME_SIZE1);
    scoreText_Item->setFont(titleFont);
    scoreText_Item->setPos(WIDTH_SCREAN-100 - scoreText_Item->boundingRect().width()/2,HIGHT_SCREAN-100);
    scene->addItem(scoreText_Item);
}

void Rocne_obdobia::startFirstPart_pexeso()
{
    //title text
    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Zahraj si pexeso:"));
    QFont titleFont(FONT_IN_GAME,FONT_GAME_SIZE1);
    titleText->setFont(titleFont);
    titleText->setPos(WIDTH_SCREAN/2 - titleText->boundingRect().width()/2,5);
    scene->addItem(titleText);

    //napoveda
    scene->addItem(My_scenes::get_napoveda());

    //pexeso
    setPosition();
    my_Items* parent_Item = new my_Items();
    my_Items* item;
    QSize velkost(110,100);
    QString textura;
    QString zadnaStrana(":/game/rokObdobia/games/G_MaOS_RocneObdobia/textur/zadnaStrana.png");
    int hodnota = 0;

    //set karticky
    for(int i = 0;i<16;i++) {       //hodnoty suborov sa rovnaju s nazvami s
        hodnota = i < 8 ? i : i-8;
        item = new my_Items(points_pexeso[i],zadnaStrana,velkost,hodnota,parent_Item);
        hracieKarty.push_back(item);
        backUp.push_back(item);
        connect(item,SIGNAL(pressed(my_Items*)),this,SLOT(click_on_Card(my_Items*)));
    }

    //set init focus
    currentFocus = hracieKarty.begin();
    currentFocus.operator*()->focusIn();

    //set status game
    gameStatus = FINDING_FIRST;
    scene->addItem(parent_Item);
}

/*void Rocne_obdobia::setPozicie()
{
    int numberRand = (rand() %13)+3;
    if(numberRand == 6){
        numberRand = 4;
    }
    QPointF point(WIDTH_SCREAN/2-355,HIGHT_SCREAN/2-250);    //__prvy stlpec
    for (int i = 0;i<4;i++){
        //pexeso[(i*numberRand)%16] = point;
        pexeso[i] = point;
        point.setY(point.y()+130);
    }

    point.setX(WIDTH_SCREAN/2-155);      //__druhy stlpec
    point.setY(HIGHT_SCREAN/2-250);
    for (int i = 4;i<8;i++){
        //pexeso[(i*numberRand)%16] = point;
        pexeso[i] = point;
        point.setY(point.y()+130);
    }

    point.setX(WIDTH_SCREAN/2+45);      //__treti stlpec
    point.setY(HIGHT_SCREAN/2-250);
    for (int i = 8;i<12;i++){
        //pexeso[(i*numberRand)%16] = point;
        pexeso[i] = point;
        point.setY(point.y()+130);
    }

    point.setX(WIDTH_SCREAN/2+245);      //__stvrty stlpec
    point.setY(HIGHT_SCREAN/2-250);
    for (int i = 12;i<16;i++){
        //pexeso[(i*numberRand)%16] = point;
        pexeso[i] = point;
        point.setY(point.y()+130);
    }
}*/

void Rocne_obdobia::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Down){
        changeFocusDown();
    } else if(event->key() == Qt::Key_Up){
        changeFocusUp();
    } else if(event->key() == Qt::Key_Left){
        changeFocusLeft();
    } else if(event->key() == Qt::Key_Right){
        changeFocusRight();
    } else if (event->key() == Qt::Key_Enter) {
        //pexesoPole. (currentFocus.operator*());
    }
}

void Rocne_obdobia::setPosition()
{
    QPointF point(WIDTH_SCREAN/2-355,HIGHT_SCREAN/2-250);    //__prvy stlpec
    for (int i = 0;i<4;i++){
        points_pexeso[i] = point;
        point.setY(point.y()+130);
    }

    point.setX(WIDTH_SCREAN/2-155);      //__druhy stlpec
    point.setY(HIGHT_SCREAN/2-250);
    for (int i = 4;i<8;i++){
        points_pexeso[i] = point;
        point.setY(point.y()+130);
    }

    point.setX(WIDTH_SCREAN/2+45);      //__treti stlpec
    point.setY(HIGHT_SCREAN/2-250);
    for (int i = 8;i<12;i++){
        points_pexeso[i] = point;
        point.setY(point.y()+130);
    }

    point.setX(WIDTH_SCREAN/2+245);      //__stvrty stlpec
    point.setY(HIGHT_SCREAN/2-250);
    for (int i = 12;i<16;i++){
        points_pexeso[i] = point;
        point.setY(point.y()+130);
    }
}

//po otoceni karty zmena focusu a delete from 2d array
void Rocne_obdobia::changeFocus()
{
    QList<my_Items*>::iterator it;
    for(it=hracieKarty.begin();it != currentFocus;it++){
        it.operator*() = nullptr;
    }
    for(it=hracieKarty.begin();it != hracieKarty.end();it++){
        if(it.operator*() != nullptr){
            currentFocus = it;
            currentFocus.operator*()->focusIn();
        }
    }
}

void Rocne_obdobia::backup_ItemOn_hracieKarty(my_Items *first, my_Items *last)
{
    for(int i=0;i < backUp.size();i++){
        if(backUp.at(i) == first){
            hracieKarty.operator[](i)= first;
        } else if(backUp.at(i) == last) {
            hracieKarty.operator[](i)= last;
        }
    }
}

void Rocne_obdobia::click_on_Card(my_Items *item)
{
    int hodnota;
    QString textura;
    QString zadnaStrana(":/game/rokObdobia/games/G_MaOS_RocneObdobia/textur/zadnaStrana.png");

    if(item != currentFocus.operator*()){
        currentFocus.operator*()->focusOut();
        currentFocus.operator*() = item;
        item->focusIn();
    }

    switch (gameStatus) {
        case FINDING_FIRST:
            otocenyItem = item;
            hodnota = item->getHodnota();
            if(hodnota<=4){
                textura = ":/game/rokObdobia/games/G_MaOS_RocneObdobia/textur/"+QString::number(hodnota)+".jpg";
            } else {
                textura = ":/game/rokObdobia/games/G_MaOS_RocneObdobia/textur/"+QString::number(hodnota)+".png";
            }
            item->setPath_ON(textura);
            item->start_open_Animation();
            changeFocus();
            gameStatus = FINDING_PAIR;
            break;
        case FINDING_PAIR:
            if(item->getHodnota() == otocenyItem->getHodnota()) {
               score++;
               //hide
               item->hideWIth_timeout(3000);
               otocenyItem->hideWIth_timeout(3000);
               otocenyItem=nullptr;
               if(score == 8){
                   gameStatus = END_PEXESO_GAME;
               } else {
                   gameStatus = FINDING_FIRST;
               }
            } else {
               item->setPath_ON(zadnaStrana);
               otocenyItem->setPath_ON(zadnaStrana);
               item->focusOut_withTimeout(2000);
               otocenyItem->focusOut_withTimeout(2000);
               QThread::msleep(2000);
               backup_ItemOn_hracieKarty(otocenyItem,item);
               gameStatus = FINDING_FIRST;
            }
            break;
        case END_PEXESO_GAME:

            break;
    }
}

void Rocne_obdobia::changeFocusRight()
{
    /*QList<my_Items*>::iterator it;
    for(it=hracieKarty.begin();it != hracieKarty.end();it++){

    }*/
    currentFocus.operator*()->focusOut();
    for(int i = 0;i<4;i++) {
        if(currentFocus+i >= hracieKarty.end()){
            currentFocus = currentFocus-12;
        } else {
            currentFocus = currentFocus +4;
        }
        if(currentFocus.operator*() != nullptr){
            currentFocus.operator*()->focusIn();
            break;
        }
    }
}

void Rocne_obdobia::changeFocusLeft()
{
    currentFocus.operator*()->focusOut();
    for(int i = 0;i<4;i++) {
        if(currentFocus+i <= hracieKarty.begin()){
            currentFocus = currentFocus+12;
        } else {
            currentFocus = currentFocus -4;
        }
        if(currentFocus.operator*() != nullptr){
            currentFocus.operator*()->focusIn();
            break;
        }
    }
}

void Rocne_obdobia::changeFocusUp()
{
    currentFocus.operator*()->focusOut();
    for(int i = 0;i<16;i=i+4){
        if(currentFocus.operator*() == hracieKarty.at(i)){
            currentFocus = currentFocus + 3;
        } else {
            currentFocus--;
        }
        if(currentFocus.operator*() != nullptr){
            currentFocus.operator*()->focusIn();
            break;
        }
    }
}

void Rocne_obdobia::changeFocusDown()
{
    currentFocus.operator*()->focusOut();
    for(int i = 3;i<16;i=i+4){
        if(currentFocus.operator*() == hracieKarty.at(i)){
            currentFocus = currentFocus - 3;
        } else {
            currentFocus++;
        }
        if(currentFocus.operator*() != nullptr){
            currentFocus.operator*()->focusIn();
            break;
        }
    }
}




