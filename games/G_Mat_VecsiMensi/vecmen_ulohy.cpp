#include "vecmen_ulohy.h"
#include "../../settings.h"
#include "../utils/my_button.h"
#include "../utils/my_scenes.h"
#include "../utils/my_animation_items.h"

#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <qsignaltransition.h>

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

    srand(time(NULL));
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
    finalState = new QFinalState();
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
    trans = state[8]->addTransition(timerForState_3,&QTimer::timeout,finalState);
    trans->addAnimation(group);

    machine->start();
    timerForState_1->start();
    timerForState_2->start();
}

void VecMen_ulohy::init_game1()
{
    //init game object
    QPointF poz_e[3];

    scene->addItem(My_scenes::get_napoveda());

    titleText = My_button::show_own_TitleText("Porovnaj rebríky podľa výšky a vyber ten najvyšší.",QPoint(WIDTH_SCREAN/2,HIGHT_SCREAN/4-130),FONT_GAME_SIZE1,true,500);
    scene->addItem(titleText);

    for (int i =0; i<3;i++) {
        poz_e[i] = QPointF(((i+1)*WIDTH_SCREAN/4)-100,(HIGHT_SCREAN/4)-50);

        focus_rebrik[i] = My_button::drowElipse(poz_e[i].x(),poz_e[i].y() ,200,450,QColor::fromRgb(53, 228, 234),0.6);
        scene->addItem(focus_rebrik[i]);

        poz_e[i].setX(poz_e[i].x()+40);
        poz_e[i].setY(poz_e[i].y()+50);
        rebrik_sipky[i] = new my_Items(poz_e[i],":/game/vecMen_ulohy/games/G_Mat_VecsiMensi/textur/"+QString::number(i+1)+".png",QSize(120,350),i+1);
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

    scene->addItem(My_button::drawPanel(WIDTH_SCREAN/2-270,HIGHT_SCREAN/4-50,860,490,QColor(15,85,77),0.7));

    QPointF randomMIesta[13];
    initRandomMiesta(randomMIesta);
    int randSipka;
    //sipka vlavo 10, vpravo 11, hore 12, dole 13
    for (int i = 0;i<13;i++) {//pixmap is null
        randSipka = (i%4)+10;
        rebrik_sipky[i] = new my_Items(randomMIesta[i],
                                       ":/game/vecMen_ulohy/games/G_Mat_VecsiMensi/textur/s"+QString::number((randSipka%4)+1)
                                       +".png",QSize(80,40),randSipka);
        rebrik_sipky[i]->setTransformOriginPoint(rebrik_sipky[i]->pixmap().rect().center());
        //musim tu random a viac sipok pridat
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
        connect(rebrik_sipky[i],SIGNAL(pressed(my_Items*)),this,SLOT(s_sipkyPressed(my_Items*)));
        scene->addItem(rebrik_sipky[i]);
    }

    colours_Text = My_button::show_own_TitleText("Vyber správnu farbu!",QPoint(50,HIGHT_SCREAN/2-200),FONT_GAME_SIZE2,false,250);
    scene->addItem(colours_Text);

    colours[0] = new my_Items(QPoint(100,HIGHT_SCREAN/2-90),":/game/score/games/utils/textur/tt.png",QSize(70,70),10);
    colours[1] = new my_Items(QPoint(100,HIGHT_SCREAN/2+20),":/game/score/games/utils/textur/oo.png",QSize(70,70),11);
    colours[2] = new my_Items(QPoint(100,HIGHT_SCREAN/2+130),":/game/score/games/utils/textur/ss.png",QSize(70,70),12);
    colours[3] = new my_Items(QPoint(100,HIGHT_SCREAN/2+240),":/game/score/games/utils/textur/x.png",QSize(70,70),13);

    for (int i =0;i<4;i++) {
        scene->addItem(colours[i]);
        connect(colours[i],SIGNAL(pressed(my_Items*)),this,SLOT(s_takeColours(my_Items*)));
    }

    status = DRUHA_ULOHA_VYBER_FARBU;
}

void VecMen_ulohy::vymalujSipku()
{
    QList<QGraphicsItem *> colliding_items = kurzor->collidingItems();
    for (int i = 0;i < colliding_items.size(); ++i){
        if (typeid(*(colliding_items[i])) == typeid(my_Items)){
            my_Items *it = dynamic_cast<my_Items*>(colliding_items.operator[](i));
            if(colour_ID == farba_zadanie && it->getHodnota() == farba_zadanie && colour_ID==10){
                it->change_Pixmap_Colour(QColor(255,255,255),QColor(169,105,0));
                status = DRUHA_ULOHA_VYBER_SIPKY;
            } else if(colour_ID == farba_zadanie && it->getHodnota() == farba_zadanie && colour_ID == 11){
                it->change_Pixmap_Colour(QColor(255,255,255),QColor(0,255,0));
                status = DRUHA_ULOHA_VYBER_SIPKY;
            } else if(colour_ID == farba_zadanie && it->getHodnota() == farba_zadanie && colour_ID == 12){
                it->change_Pixmap_Colour(QColor(255,255,255),QColor(255,255,0));
                status = DRUHA_ULOHA_VYBER_SIPKY;
            } else if(colour_ID == farba_zadanie && it->getHodnota() == farba_zadanie && colour_ID ==  13){
                it->change_Pixmap_Colour(QColor(255,255,255),QColor(255,0,0));
                status = DRUHA_ULOHA_VYBER_SIPKY;
            } else {
                answer_pixmap = My_button::showImage(QPoint(WIDTH_SCREAN/2,HIGHT_SCREAN/2-60),":/game/score/games/utils/textur/answer_wrong.png",QSize(100,100));
                scene->addItem(answer_pixmap);
                pom_timer->setSingleShot(true);
                pom_timer->setInterval(1000);
                connect(pom_timer,SIGNAL(timeout()),this,SLOT(s_clear_answer_Uloha2()));
                pom_timer->start();
            }
        }
    }
}

void VecMen_ulohy::init_Cursor(const QString textura)
{
    if(kurzor) {
        scene->removeItem(kurzor);
        delete  kurzor;
    }

    kurzor = new QGraphicsPixmapItem(textura);
    QPixmap aa = kurzor->pixmap();
    kurzor->setPixmap(aa.scaled(35,35));
    kurzor->setPos(WIDTH_SCREAN/2,HIGHT_SCREAN/2);
    scene->addItem(kurzor);
}

void VecMen_ulohy::initRandomMiesta(QPointF *random_miesta)
{
    //WIDTH_SCREAN/2-270,HIGHT_SCREAN/4-50,860,490
    random_miesta[0].setX(WIDTH_SCREAN/2-200);
    random_miesta[0].setY(HIGHT_SCREAN/4);

    random_miesta[1].setX(WIDTH_SCREAN/2-150);
    random_miesta[1].setY(HIGHT_SCREAN/4+70);

    random_miesta[2].setX(WIDTH_SCREAN/2-180);
    random_miesta[2].setY(3*HIGHT_SCREAN/4);

    random_miesta[3].setX(WIDTH_SCREAN/2-50);
    random_miesta[3].setY(HIGHT_SCREAN/4+120);

    random_miesta[4].setX(WIDTH_SCREAN/2+40);
    random_miesta[4].setY(HIGHT_SCREAN/4+160);

    random_miesta[5].setX(WIDTH_SCREAN/2+90);
    random_miesta[5].setY(HIGHT_SCREAN/4-20);

    random_miesta[6].setX(WIDTH_SCREAN/2+240);
    random_miesta[6].setY(HIGHT_SCREAN/4+200);

    random_miesta[7].setX(WIDTH_SCREAN/2+300);
    random_miesta[7].setY(HIGHT_SCREAN/4+160);

    random_miesta[8].setX(WIDTH_SCREAN/2+320);
    random_miesta[8].setY(HIGHT_SCREAN/4+300);

    random_miesta[9].setX(WIDTH_SCREAN/2+390);
    random_miesta[9].setY(HIGHT_SCREAN/4+35);

    random_miesta[10].setX(WIDTH_SCREAN/2-200);
    random_miesta[10].setY(HIGHT_SCREAN/2+10);

    random_miesta[11].setX(WIDTH_SCREAN/2+450);
    random_miesta[11].setY(HIGHT_SCREAN/2+10);

    random_miesta[12].setX(WIDTH_SCREAN/2+100);
    random_miesta[12].setY(HIGHT_SCREAN/4+220);
}

void VecMen_ulohy::changeFocus_Right()
{
    focus_rebrik[currentFocus_rebrik]->hide();
    currentFocus_rebrik++;
    if(currentFocus_rebrik > 2)
        currentFocus_rebrik = 0;
    focus_rebrik[currentFocus_rebrik]->show();
}

void VecMen_ulohy::changeFocus_Left()
{
    focus_rebrik[currentFocus_rebrik]->hide();
    currentFocus_rebrik--;
    if(currentFocus_rebrik < 0)
        currentFocus_rebrik = 2;
    focus_rebrik[currentFocus_rebrik]->show();
}


void VecMen_ulohy::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Left)
        changeFocus_Left();
    else if (event->key() == Qt::Key_Right)
        changeFocus_Right();
    else if (event->key() == Qt::Key_Enter)
        pressEnter();
    else if (event->key() == Qt::Key_Tab){

    }
}

void VecMen_ulohy::mouseMoveEvent(QMouseEvent *event)
{
    if (kurzor){
        kurzor->setPos(event->x()-(kurzor->pixmap().width()/2),event->y()-(kurzor->pixmap().height()/2));
    }
}

void VecMen_ulohy::moveLeft()
{
    if(status == PRVA_ULOHA)
        changeFocus_Left();
}

void VecMen_ulohy::moveRight()
{
    if(status == PRVA_ULOHA)
        changeFocus_Right();
}

void VecMen_ulohy::pressEnter()
{
    switch(status) {
        case PRVA_ULOHA:
            status = WAIT;
            if(rebrik_sipky[currentFocus_rebrik]->getHodnota() == 1)  {
                answer_pixmap = My_button::showImage(QPoint(WIDTH_SCREAN/2,HIGHT_SCREAN/2-60),":/game/score/games/utils/textur/answer_correct.png",QSize(150,250));
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
                answer_pixmap = My_button::showImage(QPoint(WIDTH_SCREAN/2,HIGHT_SCREAN/2-60),":/game/score/games/utils/textur/answer_wrong.png",QSize(150,250));
                scene->addItem(answer_pixmap);
                pom_timer->setInterval(2200);
                pom_timer->setSingleShot(true);
                connect(pom_timer,SIGNAL(timeout()),this,SLOT(s_clear_answer_Uloha1()));
                pom_timer->start();
            }
            break;
        case DRUHA_ULOHA_VYBER_FARBU:
            break;
        case DRUHA_ULOHA_VYBER_SIPKY:
            status = WAIT;
            vymalujSipku();
            break;
        case TRETIA_ULOHA:
            break;
        default:
            break;
    }

}

void VecMen_ulohy::s_start_DruhaUloha()
{
    disconnect(pom_timer,SIGNAL(timeout()),this,SLOT(s_start_DruhaUloha()));

    for (int i=0;i<3;i++) {
        scene->removeItem(rebrik_sipky[i]);
        delete rebrik_sipky[i];
        focus_rebrik[i]->hide();
    }

    answer_pixmap->hide();
    scene->removeItem(answer_pixmap);
    delete answer_pixmap;

    init_game2();
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

void VecMen_ulohy::s_sipkyPressed(my_Items *item)
{
    Q_UNUSED(item)
    if(status == DRUHA_ULOHA_VYBER_SIPKY)   {
        pressEnter();
    }
}

void VecMen_ulohy::s_takeColours(my_Items *item)
{
    if(status == DRUHA_ULOHA_VYBER_FARBU || status == DRUHA_ULOHA_VYBER_SIPKY){
        switch (item->getHodnota()) {
            case 10:
                init_Cursor(":/game/score/games/utils/textur/cursor10.png");
                colour_ID = 10;
                break;
            case 11:
                init_Cursor(":/game/score/games/utils/textur/cursor11.png");
                colour_ID = 11;
                break;
            case 12:
                init_Cursor(":/game/score/games/utils/textur/cursor12.png");
                colour_ID = 12;
                break;
            case 13:
                init_Cursor(":/game/score/games/utils/textur/cursor13.png");
                colour_ID = 13;
                break;
        }

        status = DRUHA_ULOHA_VYBER_SIPKY;
    }
}

void VecMen_ulohy::pressKocka()
{

}

void VecMen_ulohy::pressGulicka()
{

}

void VecMen_ulohy::pressTrojuholnik()
{

}


