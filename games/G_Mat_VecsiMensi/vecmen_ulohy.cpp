#include "vecmen_ulohy.h"
#include "../../settings.h"
#include "../utils/my_button.h"
#include "../utils/my_scenes.h"
#include "../utils/my_animation_items.h"

#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <qsignaltransition.h>
#include <QDebug>

VecMen_ulohy::VecMen_ulohy(QWidget *parent)
{
    Q_UNUSED(parent)
    //init sceny
    scene = new QGraphicsScene(this);

    scene->setSceneRect(0,0,WIDTH_SCREAN,HIGHT_SCREAN); // make the scene 800x600 instead of infinity by infinity (default)

    scene->setBackgroundBrush(QBrush(QColor::fromRgb(30, 152, 70)));
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(WIDTH_SCREAN,HIGHT_SCREAN);
    setScene(scene);

    kurzor = nullptr;
    setMouseTracking(true);

    //init game
    init_game1();

    //set timer for animation
    timerForState_1 = new QTimer();
    timerForState_1->setInterval(2000);
    timerForState_1->setSingleShot(true);

    timerForState_2 = new QTimer();
    timerForState_2->setInterval(4500);
    timerForState_2->setSingleShot(true);

    timerForState_3 = new QTimer();
    timerForState_3->setInterval(7500);
    timerForState_3->setSingleShot(true);

    pom_timer = new QTimer();
    pom_timer2 = new QTimer();

    initStete_AND_animationObj();
}

VecMen_ulohy::~VecMen_ulohy()
{
    //Removes and deletes all items from the scene
    scene->clear();
    delete scene;
    #ifdef DEF_DEBUG
     qDebug() << "~VecMen_ulohy.cpp 69 ";
    #endif

    delete timerForState_1;
    delete timerForState_2;
    delete timerForState_3;
    delete pom_timer;
    delete pom_timer2;
}

void VecMen_ulohy::initStete_AND_animationObj()
{
    //INIT OBJECT
    QSize siz(3*WIDTH_SCREAN/5,HIGHT_SCREAN/7);

    My_button* panel = new My_button(WIDTH_SCREAN/8,HIGHT_SCREAN/8,6*WIDTH_SCREAN/8,6*HIGHT_SCREAN/8,Qt::darkGray);
    panel->setZValue(5);
    scene->addItem(panel);
    QGraphicsTextItem* titleText = My_button::show_own_TitleText("Pomôž mi s prvou úlohou.",QPoint(WIDTH_SCREAN/2,HIGHT_SCREAN/4),FONT_GAME_SIZE1,true);
    animationTitleText = titleText;
    titleText->setZValue(5);
    scene->addItem(titleText);
    My_animation_items* pointObr = new My_animation_items(":/game/vecMen_ulohy/games/G_Mat_VecsiMensi/textur/point.png",QPointF(WIDTH_SCREAN/2-(siz.width()/2),(HIGHT_SCREAN/2)+siz.height()),siz);
    scene->addItem(pointObr);
    pointObr->setZValue(5);
    My_animation_items* person = new My_animation_items(":/game/vecMen_ulohy/games/G_Mat_VecsiMensi/textur/femalePerson_fall.png",QPointF(WIDTH_SCREAN/8,HIGHT_SCREAN/8),QSize(70,70));
    person->setZValue(5);
    scene->addItem(person);

    //INIT STATE
    machine = new QStateMachine();
    for(int i=0;i<8;i++){
        state[i] = new QState();
        machine->addState(state[i]);
    }
    machine->setInitialState(state[0]);

    //SET STATES
    for(int i=0;i<8;i++){
        switch (i) {
        case 0:
            state[i]->assignProperty(panel, "opacity", qreal(1));
            state[i]->assignProperty(titleText, "opacity", qreal(1));
            state[i]->assignProperty(pointObr, "opacity", qreal(1));
            state[i]->assignProperty(person, "opacity", qreal(1));
            state[i]->assignProperty(person, "pos", QPointF(WIDTH_SCREAN/8,HIGHT_SCREAN/8));
            break;
        case 1:
            state[i]->assignProperty(panel, "opacity", qreal(1));
            state[i]->assignProperty(titleText, "opacity", qreal(1));
            state[i]->assignProperty(pointObr, "opacity", qreal(1));
            state[i]->assignProperty(person, "opacity", qreal(1));
            state[i]->assignProperty(person, "pos", QPointF(WIDTH_SCREAN/4-35,(HIGHT_SCREAN/2+30)));
            break;
        case 2:
            state[i]->assignProperty(panel, "opacity", qreal(0));
            state[i]->assignProperty(titleText, "opacity", qreal(0));
            state[i]->assignProperty(pointObr, "opacity", qreal(0));
            state[i]->assignProperty(person, "opacity", qreal(0));
            state[i]->assignProperty(person, "pos", QPointF(WIDTH_SCREAN/4-35,(HIGHT_SCREAN/2+30)));
            break;
        case 3:
            state[i]->assignProperty(panel, "opacity", qreal(1));
            state[i]->assignProperty(titleText, "opacity", qreal(1));
            state[i]->assignProperty(pointObr, "opacity", qreal(1));
            state[i]->assignProperty(person, "opacity", qreal(1));
            state[i]->assignProperty(person, "pos", QPointF(WIDTH_SCREAN/4-35,(HIGHT_SCREAN/2+30)));
            break;
        case 4:
            state[i]->assignProperty(panel, "opacity", qreal(1));
            state[i]->assignProperty(titleText, "opacity", qreal(1));
            state[i]->assignProperty(pointObr, "opacity", qreal(1));
            state[i]->assignProperty(person, "opacity", qreal(1));
            state[i]->assignProperty(person, "pos", QPointF(WIDTH_SCREAN/2-35,(HIGHT_SCREAN/2-20)));
            break;
        case 5:
            state[i]->assignProperty(panel, "opacity", qreal(0));
            state[i]->assignProperty(titleText, "opacity", qreal(0));
            state[i]->assignProperty(pointObr, "opacity", qreal(0));
            state[i]->assignProperty(person, "opacity", qreal(0));
            state[i]->assignProperty(person, "pos", QPointF(WIDTH_SCREAN/2-35,(HIGHT_SCREAN/2-20)));
            break;
        case 6:
            state[i]->assignProperty(panel, "opacity", qreal(1));
            state[i]->assignProperty(titleText, "opacity", qreal(1));
            state[i]->assignProperty(pointObr, "opacity", qreal(1));
            state[i]->assignProperty(person, "opacity", qreal(1));
            state[i]->assignProperty(person, "pos", QPointF(WIDTH_SCREAN/2-35,(HIGHT_SCREAN/2-20)));
            break;
        case 7:
            state[i]->assignProperty(panel, "opacity", qreal(1));
            state[i]->assignProperty(titleText, "opacity", qreal(1));
            state[i]->assignProperty(pointObr, "opacity", qreal(1));
            state[i]->assignProperty(person, "opacity", qreal(1));
            state[i]->assignProperty(person, "pos", QPointF(3*WIDTH_SCREAN/4-35,(HIGHT_SCREAN/2+20)));
            break;
        }
    }
    QParallelAnimationGroup *group = new QParallelAnimationGroup();
    for (int i = 0; i < 4; i++) {
        QPropertyAnimation *anim3 = new QPropertyAnimation(titleText, "opacity");
        group->addAnimation(anim3);
        QPropertyAnimation *anim4 = new QPropertyAnimation(panel, "opacity");
        group->addAnimation(anim4);
        QPropertyAnimation *anim1 = new QPropertyAnimation(person, "opacity");
        group->addAnimation(anim1);
        QPropertyAnimation *anim2 = new QPropertyAnimation(pointObr, "opacity");
        group->addAnimation(anim2);
        QPropertyAnimation *anim = new QPropertyAnimation(person, "pos");
        anim->setDuration(750 + i * 25);
        anim->setEasingCurve(QEasingCurve::InOutBack);
        group->addAnimation(anim);
    }

    QSignalTransition *trans;
    trans = state[0]->addTransition(timerForState_1,&QTimer::timeout,state[1]);
    trans->addAnimation(group);

    trans = state[1]->addTransition(timerForState_2,&QTimer::timeout,state[2]);
    trans->addAnimation(group);

    for (int i = 2; i < 7; i++) {
        if(i%3 == 2) {
            trans = state[i]->addTransition(timerForState_1,&QTimer::timeout,state[i+1]);
            trans->addAnimation(group);
        } else if (i%3 == 0) {
            trans = state[i]->addTransition(timerForState_2,&QTimer::timeout,state[i+1]);
            trans->addAnimation(group);
        } else if (i%3 == 1) {
            trans = state[i]->addTransition(timerForState_3,&QTimer::timeout,state[i+1]);
            trans->addAnimation(group);
        }
    }

    machine->start();
    timerForState_1->start();
    timerForState_2->start();
}

void VecMen_ulohy::init_game1()
{
    //init game object
    QPointF poz_e[3];
    int random[3];
    my_Items::generateRandomNumberWithoutRepetition(random,3,1,4);

    napovedaParent = My_scenes::get_napoveda();
    scene->addItem(napovedaParent);

    titleText = My_button::show_own_TitleText("Porovnaj rebríky podľa výšky a vyber ten najvyšší.",QPoint(WIDTH_SCREAN/2,HIGHT_SCREAN/4-130),FONT_GAME_SIZE1,true,500);
    scene->addItem(titleText);

    for (int i =0; i<3;i++) {
        poz_e[i] = QPointF(((i+1)*WIDTH_SCREAN/4)-100,(HIGHT_SCREAN/4)-50);

        focus_rebrik[i] = My_button::drow_Elipse(poz_e[i].x(),poz_e[i].y() ,200,450,QColor::fromRgb(53, 228, 234),0.6);
        scene->addItem(focus_rebrik[i]);

        poz_e[i].setX(poz_e[i].x()+40);
        poz_e[i].setY(poz_e[i].y()+50);
        rebrik_sipky[i] = new my_Items(poz_e[i],":/game/vecMen_ulohy/games/G_Mat_VecsiMensi/textur/"+QString::number(random[i])+".png",QSize(120,350),random[i]);
        connect(rebrik_sipky[i],SIGNAL(pressed(my_Items*)),this,SLOT(s_pressRebrik(my_Items*)));
        scene->addItem(rebrik_sipky[i]);
    }
    //init focus rebrik
    focus_rebrik[1]->hide();
    focus_rebrik[2]->hide();
}

void VecMen_ulohy::init_game2()
{
    QString pole[4] = {"vľavo","vpravo","hore","dole"};
    QString farba[4] = {"hnedou","zelenou","žltou","červenou"};

    farba_zadanie = rand() % 4;
    titleText->setPlainText(QString("Šípky ktoré smerujú " + pole[farba_zadanie] +" vymaľuj "+farba[farba_zadanie]+" farbou."));
    titleText->setX(WIDTH_SCREAN/2-titleText->boundingRect().width()/2);
    farba_zadanie=farba_zadanie+10;

    scene->addItem(My_button::drawPanel(WIDTH_SCREAN/5-100,HIGHT_SCREAN/4-50,(3*WIDTH_SCREAN/5)+200,450,QColor(86, 122, 209),0.7));

    QPointF randomMIesta[13];
    initRandomMiesta(randomMIesta);
    int randSipka;
    //sipka vlavo 10, vpravo 11, hore 12, dole 13
    for (int i = 0;i<13;i++) {
        randSipka = (i%4)+10;
        rebrik_sipky[i] = new my_Items(randomMIesta[i],
                                       ":/game/vecMen_ulohy/games/G_Mat_VecsiMensi/textur/s"+QString::number((randSipka%4)+1)
                                       +".png",QSize(80,40),randSipka);
        rebrik_sipky[i]->setTransformOriginPoint(rebrik_sipky[i]->pixmap().rect().center());
        switch (randSipka) {
            case 10:
                break;
            case 11:
                rebrik_sipky[i]->setRotation(-180);
                break;
            case 12:
                rebrik_sipky[i]->setRotation(+90);
                break;
            case 13:
                rebrik_sipky[i]->setRotation(-90);
                break;
        }
        if(randSipka == farba_zadanie){
            pocet_spiopk_preMalovanie++;
        }
        connect(rebrik_sipky[i],SIGNAL(pressed(my_Items*)),this,SLOT(s_sipkyPressed(my_Items*)));
        scene->addItem(rebrik_sipky[i]);
    }

    colours_Text = new QGraphicsTextItem();
    QGraphicsTextItem* it;
    it = My_button::show_own_TitleText("Hnedá",QPoint(WIDTH_SCREAN/5,HIGHT_SCREAN-90),FONT_GAME_SIZE2,false);
    it->setParentItem(colours_Text);
    it = My_button::show_own_TitleText("Zelená",QPoint(2*WIDTH_SCREAN/5,HIGHT_SCREAN-90),FONT_GAME_SIZE2,false);
    it->setParentItem(colours_Text);
    it = My_button::show_own_TitleText("Žltá",QPoint(3*WIDTH_SCREAN/5,HIGHT_SCREAN-90),FONT_GAME_SIZE2,false);
    it->setParentItem(colours_Text);
    it = My_button::show_own_TitleText("Červená",QPoint(4*WIDTH_SCREAN/5,HIGHT_SCREAN-90),FONT_GAME_SIZE2,false);
    it->setParentItem(colours_Text);
    scene->addItem(colours_Text);

    colours[0] = new my_Items(QPoint(WIDTH_SCREAN/5-75,HIGHT_SCREAN-100),":/game/score/games/utils/textur/tt.png",QSize(70,70),10);
    colours[1] = new my_Items(QPoint(2*WIDTH_SCREAN/5-75,HIGHT_SCREAN-100),":/game/score/games/utils/textur/oo.png",QSize(70,70),11);
    colours[2] = new my_Items(QPoint(3*WIDTH_SCREAN/5-75,HIGHT_SCREAN-100),":/game/score/games/utils/textur/ss.png",QSize(70,70),12);
    colours[3] = new my_Items(QPoint(4*WIDTH_SCREAN/5-75,HIGHT_SCREAN-100),":/game/score/games/utils/textur/x.png",QSize(70,70),13);

    for (int i =0;i<4;i++) {
        scene->addItem(colours[i]);
        connect(colours[i],SIGNAL(pressed(my_Items*)),this,SLOT(s_takeColours(my_Items*)));
    }

    status = DRUHA_ULOHA_VYBER_FARBU;
}

void VecMen_ulohy::init_game3()
{
    scene->addItem(My_button::showTitleText("Zoraď ježkov od največšieho po najmenšieho:"));
    scene->addItem(My_scenes::get_napoveda());

    int random[5];
    my_Items::generateRandomNumberWithoutRepetition(random,5,0,5);

    my_Items *it;
    for (int i = 0;i<5;i++) {
        it = new my_Items(QPointF((i+1)*WIDTH_SCREAN/7,600 -(70+(random[i]*20))),":/game/vecMen_ulohy/games/G_Mat_VecsiMensi/textur/jezko_OFF.png",":/game/vecMen_ulohy/games/G_Mat_VecsiMensi/textur/jezko_ON.png",QSize(70+(random[i]*20),70+(random[i]*20)),random[i]);
        jezko.push_back(it);
        connect(it,SIGNAL(pressed(my_Items*)),this,SLOT(s_selectJezko(my_Items*)));
        scene->addItem(it);

        scene->addItem(My_button::show_own_TitleText(QString::number(i+1),QPoint((i+1)*WIDTH_SCREAN/7+25,HIGHT_SCREAN/4+80),FONT_GAME_SIZE2,false));
        it = new my_Items(QPointF((i+1)*WIDTH_SCREAN/7,HIGHT_SCREAN/3-(130-(i*12))),":/game/vecMen_ulohy/games/G_Mat_VecsiMensi/textur/elipse.png",QSize(100-(i*10),150-(i*12)),4-i);
        it->setOpacity(0.7);
        connect(it,SIGNAL(pressed(my_Items*)),this,SLOT(s_pressOnPoint_Jezko(my_Items*)));
        scene->addItem(it);
    }

    currentJezkoFocus = jezko.begin();
    jezko.first()->focusIn();

}

void VecMen_ulohy::vymalujSipku()
{
    QList<QGraphicsItem *> colliding_items = kurzor->collidingItems();
    for (int i = 0;i < colliding_items.size(); ++i){
        if (typeid(*(colliding_items[i])) == typeid(my_Items)){
            my_Items *it = dynamic_cast<my_Items*>(colliding_items.operator[](i));
            if(colour_ID == farba_zadanie && it->getHodnota() == farba_zadanie && colour_ID==10){
                it->change_Pixmap_Colour(QColor(255,255,255),QColor(169,105,0));
                pocet_spiopk_preMalovanie--;
                status = DRUHA_ULOHA_VYBER_SIPKY;
            } else if(colour_ID == farba_zadanie && it->getHodnota() == farba_zadanie && colour_ID == 11){
                it->change_Pixmap_Colour(QColor(255,255,255),QColor(0,255,0));
                pocet_spiopk_preMalovanie--;
                status = DRUHA_ULOHA_VYBER_SIPKY;
            } else if(colour_ID == farba_zadanie && it->getHodnota() == farba_zadanie && colour_ID == 12){
                it->change_Pixmap_Colour(QColor(255,255,255),QColor(255,255,0));
                pocet_spiopk_preMalovanie--;
                status = DRUHA_ULOHA_VYBER_SIPKY;
            } else if(colour_ID == farba_zadanie && it->getHodnota() == farba_zadanie && colour_ID ==  13){
                it->change_Pixmap_Colour(QColor(255,255,255),QColor(255,0,0));
                pocet_spiopk_preMalovanie--;
                status = DRUHA_ULOHA_VYBER_SIPKY;
            } else {
                answer_pixmap = My_button::showImage(QPoint(WIDTH_SCREAN/2,HIGHT_SCREAN/2-60),":/game/score/games/utils/textur/answer_wrong.png",QSize(100,100));
                scene->addItem(answer_pixmap);
                pom_timer->setSingleShot(true);
                pom_timer->setInterval(1000);
                connect(pom_timer,SIGNAL(timeout()),this,SLOT(s_clear_answer_Uloha2()));
                pom_timer->start();
            }

            if(!pocet_spiopk_preMalovanie) {
                status = WAIT;
                kurzor = nullptr;
                animationTitleText->setPlainText("Výborne už len posledná úloha.");
                animationTitleText->setX(WIDTH_SCREAN/2-animationTitleText->boundingRect().width() /2);
                timerForState_1->start();
                timerForState_2->start();
                pom_timer2->setInterval(8000);
                pom_timer2->setSingleShot(true);
                connect(pom_timer2,SIGNAL(timeout()),this,SLOT(s_start_TretiaUloha()));
                pom_timer2->start();
            }
        }
    }
}

void VecMen_ulohy::init_Cursor(const QString textura,const QSize velkost)
{
    if(kurzor) {
        scene->removeItem(kurzor);
        delete  kurzor;
    }

    kurzor = new QGraphicsPixmapItem(textura);
    QPixmap aa = kurzor->pixmap();
    kurzor->setPixmap(aa.scaled(velkost));
    kurzor->setPos(WIDTH_SCREAN/2,HIGHT_SCREAN/2);
    scene->addItem(kurzor);
}

void VecMen_ulohy::initRandomMiesta(QPointF *random_miesta)
{
    //WIDTH_SCREAN/2-270,HIGHT_SCREAN/4-50,860,490
    random_miesta[0].setX(WIDTH_SCREAN/5-50);
    random_miesta[0].setY(HIGHT_SCREAN/4);

    random_miesta[1].setX(WIDTH_SCREAN/2-150);
    random_miesta[1].setY(HIGHT_SCREAN/4+70);

    random_miesta[2].setX(WIDTH_SCREAN/5+5);
    random_miesta[2].setY(2*HIGHT_SCREAN/4+70);

    random_miesta[3].setX(WIDTH_SCREAN/5+40);
    random_miesta[3].setY(HIGHT_SCREAN/4+120);

    random_miesta[4].setX(WIDTH_SCREAN/2+40);
    random_miesta[4].setY(HIGHT_SCREAN/4+160);

    random_miesta[5].setX(WIDTH_SCREAN/2+90);
    random_miesta[5].setY(HIGHT_SCREAN/4-20);

    random_miesta[6].setX(WIDTH_SCREAN/2+240);
    random_miesta[6].setY(HIGHT_SCREAN/4+200);

    random_miesta[7].setX(WIDTH_SCREAN/2+300);
    random_miesta[7].setY(HIGHT_SCREAN/4+160);

    random_miesta[8].setX(WIDTH_SCREAN/2+280);
    random_miesta[8].setY(HIGHT_SCREAN/4);

    random_miesta[9].setX(WIDTH_SCREAN/2-50);
    random_miesta[9].setY(HIGHT_SCREAN/4+70);

    random_miesta[10].setX(WIDTH_SCREAN/2);
    random_miesta[10].setY(HIGHT_SCREAN/2+100);

    random_miesta[11].setX(WIDTH_SCREAN/2-100);//
    random_miesta[11].setY(HIGHT_SCREAN/2+130);

    random_miesta[12].setX(WIDTH_SCREAN/2+100);
    random_miesta[12].setY(HIGHT_SCREAN/4+220);
}

void VecMen_ulohy::changeFocus_Right()
{
    if(status == PRVA_ULOHA)    {
        focus_rebrik[currentFocus_object]->hide();
        currentFocus_object++;
        if(currentFocus_object > 2)
            currentFocus_object = 0;
        focus_rebrik[currentFocus_object]->show();
    } else if (status == TRETIA_ULOHA_SELECT || status == TRETIA_ULOHA_FIND)  {
        currentJezkoFocus.operator*()->focusOut();
        currentJezkoFocus++;
        if(currentJezkoFocus>jezko.end()-1){
            currentJezkoFocus = jezko.begin();
        }
        currentJezkoFocus.operator*()->focusIn();
    }
}

void VecMen_ulohy::changeFocus_Left()
{
    if(status == PRVA_ULOHA)    {
        focus_rebrik[currentFocus_object]->hide();
        currentFocus_object--;
        if(currentFocus_object < 0)
            currentFocus_object = 2;
        focus_rebrik[currentFocus_object]->show();
    } else if(status == TRETIA_ULOHA_SELECT)   {
        currentJezkoFocus.operator*()->focusOut();
        currentJezkoFocus--;
        if(currentJezkoFocus<jezko.begin()){
            currentJezkoFocus = jezko.end()-1;
        }
        currentJezkoFocus.operator*()->focusIn();
    }
}


void VecMen_ulohy::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Left)
        moveLeft();
    else if (event->key() == Qt::Key_Right)
        moveRight();
    else if (event->key() == Qt::Key_Enter)
        pressEnter();
    else if (event->key() == Qt::Key_Tab){

    } else if (event->key() == Qt::Key_K)
        pressTrojuholnik();
    else if(event->key() == Qt::Key_M)
        pressKocka();
    else if (event->key() == Qt::Key_Up)
        moveUp();
    else if (event->key() == Qt::Key_Down)
        moveDown();
}

void VecMen_ulohy::mouseMoveEvent(QMouseEvent *event)
{
    if (kurzor){
        kurzor->setPos(event->x()-(kurzor->pixmap().width()/2),event->y()-(kurzor->pixmap().height()/2));
    }
}

void VecMen_ulohy::moveLeft()
{
    if (kurzor && (kurzor->x()-MOVE_STEP) > 0){
        kurzor->setX(kurzor->x()-MOVE_STEP);
    }
    if(status == PRVA_ULOHA || status == TRETIA_ULOHA_SELECT)
        changeFocus_Left();
}

void VecMen_ulohy::moveRight()
{
    if (kurzor && (kurzor->x()+MOVE_STEP) < WIDTH_SCREAN){
        kurzor->setX(kurzor->x()+MOVE_STEP);
    }
    if(status == PRVA_ULOHA || status == TRETIA_ULOHA_SELECT)
        changeFocus_Right();
}

void VecMen_ulohy::moveUp()
{
    if (kurzor && (kurzor->y()-MOVE_STEP) > 0){
        kurzor->setY(kurzor->y()-MOVE_STEP);
    }
}

void VecMen_ulohy::moveDown()
{
    if (kurzor && (kurzor->y()+MOVE_STEP) < HIGHT_SCREAN){
        kurzor->setY(kurzor->y()+MOVE_STEP);
    }
}

void VecMen_ulohy::pressEnter()
{
    switch(status) {
        case WAIT:
            break;
        case PRVA_ULOHA:
            status = WAIT;
            if(rebrik_sipky[currentFocus_object]->getHodnota() == 1)  {
                QPoint pos(static_cast<int>(rebrik_sipky[currentFocus_object]->x()+70),static_cast<int>(rebrik_sipky[currentFocus_object]->y()+100));
                answer_pixmap = My_button::showImage(pos,":/game/score/games/utils/textur/answer_correct.png",QSize(150,250));
                scene->addItem(answer_pixmap);
                pom_timer2->setInterval(7000);
                pom_timer2->setSingleShot(true);
                connect(pom_timer2,SIGNAL(timeout()),this,SLOT(s_start_DruhaUloha()));
                pom_timer2->start();

                animationTitleText->setPlainText("A poďme na druhú úlohu.");
                timerForState_1->start();
                timerForState_2->start();
                timerForState_3->start();
            } else {
                QPoint pos(static_cast<int>(rebrik_sipky[currentFocus_object]->x()+70),static_cast<int>(rebrik_sipky[currentFocus_object]->y()+100));
                answer_pixmap = My_button::showImage(pos,":/game/score/games/utils/textur/answer_wrong.png",QSize(150,250));
                scene->addItem(answer_pixmap);
                pom_timer->setInterval(2200);
                pom_timer->setSingleShot(true);
                connect(pom_timer,SIGNAL(timeout()),this,SLOT(s_clear_answer_Uloha1()));
                pom_timer->start();
            }
            break;
        case DRUHA_ULOHA_VYBER_FARBU:
            s_takeColours(rebrik_sipky[4]);//x vyberie cervenu
            break;
        case DRUHA_ULOHA_VYBER_SIPKY:
            status = WAIT;
            vymalujSipku();
            break;
        case TRETIA_ULOHA_SELECT:
            init_Cursor(":/game/vecMen_ulohy/games/G_Mat_VecsiMensi/textur/jezko_OFF.png",currentJezkoFocus.operator*()->velkost);
            status = TRETIA_ULOHA_FIND;
            break;
        case TRETIA_ULOHA_FIND:
            QList<QGraphicsItem *> colliding_items = kurzor->collidingItems();
            for (int i = 0;i < colliding_items.size(); ++i){
                if (typeid(*(colliding_items[i])) == typeid(my_Items)){
                    my_Items *it = dynamic_cast<my_Items*>(colliding_items.operator[](i));
                    if(it->getHodnota() == currentJezkoFocus.operator*()->getHodnota()) {
                        s_pressOnPoint_Jezko(it);
                        break;
                    }
                }
            }
            break;
    }
}

void VecMen_ulohy::s_start_DruhaUloha()
{
    disconnect(pom_timer2,SIGNAL(timeout()),this,SLOT(s_start_DruhaUloha()));

    for (int i=0;i<3;i++) {
        scene->removeItem(rebrik_sipky[i]);
        delete rebrik_sipky[i];
        focus_rebrik[i]->hide();
    }

    //clean napoveda
    auto childObject = napovedaParent->childItems();
    QGraphicsItem* var;
    foreach (var, childObject) {
        scene->removeItem(var);
        delete var;
    }
    delete napovedaParent;

    scene->removeItem(answer_pixmap);
    delete answer_pixmap;

    init_game2();
}

void VecMen_ulohy::s_start_TretiaUloha()
{
    scene->clear();

    init_game3();
    status = TRETIA_ULOHA_SELECT;
}

void VecMen_ulohy::s_clear_answer_Uloha1()
{
    disconnect(pom_timer,SIGNAL(timeout()),this,SLOT(s_clear_answer_Uloha1()));

    answer_pixmap->hide();
    scene->removeItem(answer_pixmap);
    delete answer_pixmap;

    status = PRVA_ULOHA;
}

void VecMen_ulohy::s_clear_answer_Uloha2()
{
    disconnect(pom_timer,SIGNAL(timeout()),this,SLOT(s_clear_answer_Uloha2()));

    answer_pixmap->hide();
    scene->removeItem(answer_pixmap);
    delete answer_pixmap;

    status = DRUHA_ULOHA_VYBER_SIPKY;
}

void VecMen_ulohy::s_pressRebrik(my_Items *item)
{
    focus_rebrik[currentFocus_object]->hide();
    if(status == PRVA_ULOHA)    {
        status = WAIT;
        if(item->getHodnota() == 1)  {
            QPoint pos(static_cast<int>(item->x()+70),static_cast<int>(item->y()+100));
            answer_pixmap = My_button::showImage(pos,":/game/score/games/utils/textur/answer_correct.png",QSize(150,250));
            scene->addItem(answer_pixmap);
            pom_timer->setInterval(2200);
            pom_timer->setSingleShot(true);
            connect(pom_timer,SIGNAL(timeout()),this,SLOT(s_start_DruhaUloha()));
            pom_timer->start();

            animationTitleText->setPlainText("A poďme na druhú úlohu.");
            timerForState_1->start();
            timerForState_2->start();
            timerForState_3->start();
        } else {
            QPoint pos(static_cast<int>(item->x()+70),static_cast<int>(item->y()+100));
            answer_pixmap = My_button::showImage(pos,":/game/score/games/utils/textur/answer_wrong.png",QSize(150,250));
            scene->addItem(answer_pixmap);
            pom_timer->setInterval(2200);
            pom_timer->setSingleShot(true);
            connect(pom_timer,SIGNAL(timeout()),this,SLOT(s_clear_answer_Uloha1()));
            pom_timer->start();
        }
    }
}

void VecMen_ulohy::s_sipkyPressed(my_Items *item)
{
    Q_UNUSED(item)
    if(status == DRUHA_ULOHA_VYBER_SIPKY)   {
        pressEnter();
    }
}

void VecMen_ulohy::s_takeColours(my_Items *item)
{
    if(status == DRUHA_ULOHA_VYBER_FARBU ){
        switch (item->getHodnota()) {
            case 10:
                init_Cursor(":/game/score/games/utils/textur/cursor10.png",QSize(30,30));
                colour_ID = 10;
                break;
            case 11:
                init_Cursor(":/game/score/games/utils/textur/cursor11.png",QSize(30,30));
                colour_ID = 11;
                break;
            case 12:
                init_Cursor(":/game/score/games/utils/textur/cursor12.png",QSize(30,30));
                colour_ID = 12;
                break;
            case 13:
                init_Cursor(":/game/score/games/utils/textur/cursor13.png",QSize(30,30));
                colour_ID = 13;
                break;
        }
        //hide texts & buttons
        auto items = colours_Text->childItems();
        QGraphicsItem * it;
        foreach (it, items) {
            if(static_cast<int>(it->x()) != static_cast<int>(WIDTH_SCREAN/5))
                it->hide();
            else    {
                QGraphicsTextItem* a = dynamic_cast<QGraphicsTextItem*>(it);
                a->setPlainText("Zmeň farbu!");
            }
        }

        for (int i = 1;i<4;i++) {
            colours[i]->hide();
        }

        status = DRUHA_ULOHA_VYBER_SIPKY;
    } else if (status == DRUHA_ULOHA_VYBER_SIPKY){
        auto items = colours_Text->childItems();
        QGraphicsItem * it;
        foreach (it, items) {   //texty
            if(static_cast<int>(it->x()) != static_cast<int>(WIDTH_SCREAN/5))
                it->show();
            else    {
                QGraphicsTextItem* a = dynamic_cast<QGraphicsTextItem*>(it);
                a->setPlainText("Hnedá");
            }
        }
                //tlacidla
        for (int i = 1;i<4;i++) {
            colours[i]->show();
        }
        colour_ID = 0;
        scene->removeItem(kurzor);
        kurzor = nullptr;
        status = DRUHA_ULOHA_VYBER_FARBU;
    }
}

void VecMen_ulohy::s_selectJezko(my_Items *item)
{
    if(status == TRETIA_ULOHA_SELECT)   {
        while(item != currentJezkoFocus.operator*())
            changeFocus_Right();
        init_Cursor(":/game/vecMen_ulohy/games/G_Mat_VecsiMensi/textur/jezko_OFF.png",item->velkost);
        status = TRETIA_ULOHA_FIND;
    }
}

void VecMen_ulohy::s_pressOnPoint_Jezko(my_Items *item)
{
    if(status == TRETIA_ULOHA_FIND) {
        if(item->getHodnota() == currentJezkoFocus.operator*()->getHodnota()) {
            //disconnect jezko
            disconnect(currentJezkoFocus.operator*(),SIGNAL(pressed(my_Items*)),this,SLOT(s_selectJezko(my_Items*)));
            currentJezkoFocus.operator*()->focusOut();
            currentJezkoFocus.operator*()->setPos(item->pos().x(),HIGHT_SCREAN/3-currentJezkoFocus.operator*()->velkost.height());

            //change focus
            jezko.removeOne(currentJezkoFocus.operator*());
            if(!jezko.isEmpty())    {
                currentJezkoFocus = jezko.begin();
                currentJezkoFocus.operator*()->focusIn();

            } else {
                pom_timer->setInterval(1200);
                pom_timer->setSingleShot(true);
                connect(pom_timer,SIGNAL(timeout()),this,SLOT(s_show_GameOwer()));
                pom_timer->start();
            }

            //clear kurzor
            scene->removeItem(kurzor);
            delete  kurzor;
            kurzor = nullptr;

            //disconnect elipse
            disconnect(item,SIGNAL(pressed(my_Items*)),this,SLOT(s_pressOnPoint_Jezko(my_Items*)));
            item->hide();

            status = TRETIA_ULOHA_SELECT;
        } else {
            pom_timer->setInterval(1500);
            pom_timer->setSingleShot(true);
            //dokoncit
        }
    }
}

void VecMen_ulohy::s_show_GameOwer()
{
    my_Items * it;
    foreach (it, jezko) {
        it->hide(); // koli z value
    }

    scene->addItem(My_button::drawPanel(0,0,WIDTH_SCREAN,HIGHT_SCREAN,Qt::black,0.65));

    // draw panel
    scene->addItem(My_button::drawPanel(WIDTH_SCREAN/2-275,HIGHT_SCREAN/2-250,550,450,Qt::lightGray,0.75));

    // texty
    scene->addItem(My_button::show_own_TitleText("Koniec hry",QPoint(WIDTH_SCREAN/2,HIGHT_SCREAN/2-220),30,true));

    scene->addItem(My_button::show_own_TitleText("Si veľmi škovný",QPoint(WIDTH_SCREAN/2,HIGHT_SCREAN/2-180),30,true));

    My_button* close = new My_button(QString("Koniec"));
    close->setPos(410,HIGHT_SCREAN/2+105);
    connect(close,SIGNAL(clicked()),this,SLOT(close()));

    scene->addItem(close);

    /*ADD Gif*/
    scene->addWidget(My_button::showGif(QString(":/game/score/games/utils/textur/hviezdicky.gif"),QPoint(WIDTH_SCREAN/2-75,HIGHT_SCREAN/2-110)));
}

void VecMen_ulohy::pressKocka()
{
    s_takeColours(rebrik_sipky[3]);
}

void VecMen_ulohy::pressGulicka()
{
    s_takeColours(rebrik_sipky[1]);
}

void VecMen_ulohy::pressTrojuholnik()
{
    s_takeColours(rebrik_sipky[0]);
}


