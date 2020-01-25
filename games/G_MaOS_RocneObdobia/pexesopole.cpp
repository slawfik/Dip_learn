#include "pexesopole.h"
#include "../../settings.h"
#include <QThread>

pexesoPole::pexesoPole(my_Items* parent_Item,QObject *parent)
{
    setParent(parent);

    setPosition();
    //my_Items* parent_Item = new my_Items();
    my_Items* item;
    QSize velkost(110,100);
    QString textura;
    QString zadnaStrana(":/game/rokObdobia/games/G_MaOS_RocneObdobia/textur/zadnaStrana.png");
    int hodnota = 0;

    //set karticky
    for(int i = 0;i<16;i++) {       //hodnoty suborov sa rovnaju s nazvami s
        hodnota = i < 8 ? i : i-8;
        item = new my_Items(points_pexeso[i++],zadnaStrana,velkost,hodnota,parent_Item);
        hracieKarty.push_back(item);
        backUp.push_back(item);
        connect(item,SIGNAL(pressed(my_Items*)),this,SLOT(click_on_Card(my_Items*)));
    }

    //set init focus
    currentFocus = hracieKarty.begin();
    currentFocus.operator*()->focusIn();

    //set status game
    gameStatus = FINDING_FIRST;
}

void pexesoPole::setPosition()
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
void pexesoPole::changeFocus()
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

void pexesoPole::backup_ItemOn_hracieKarty(my_Items *first, my_Items *last)
{
    for(int i=0;i < backUp.size();i++){
        if(backUp.at(i) == first){
            hracieKarty.operator[](i)= first;
        } else if(backUp.at(i) == last) {
            hracieKarty.operator[](i)= last;
        }
    }
}

void pexesoPole::click_on_Card(my_Items *item)
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

/*my_Items *pexesoPole::getParent_Item() const
{
    return parent_Item;
}
*/
void pexesoPole::changeFocusRight()
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

void pexesoPole::changeFocusLeft()
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

void pexesoPole::changeFocusUp()
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

void pexesoPole::changeFocusDown()
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
