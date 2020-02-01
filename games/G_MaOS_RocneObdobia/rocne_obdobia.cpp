//https://www.google.com/search?q=strom+rocne+obdobia&client=ubuntu&tbm=isch&tbs=rimg:CRoPBD5HpcUQImA4n7kMjR1_1g3c0-yxoFPrSVg_1roGP758ck-r7eYzgDkujZIlI7-7ICR0vw6-cz1NuPCPHGdwPFQOE1H8Lh-TZxEh39vfPU_1lMXFGRzTmmtDAUerjbVtQBd6KWlSSsNWhQqEgk4n7kMjR1_1gxEQICMW5n0BHSoSCXc0-yxoFPrSEfUAulpaJ2lbKhIJVg_1roGP758cRh-S52sNrV-cqEgkk-r7eYzgDkhE006PXkohJaSoSCejZIlI7-7ICEVh-dhy3vT-FKhIJR0vw6-cz1NsRc-dsA7zH4rYqEgmPCPHGdwPFQBF8fCOppcTjyyoSCeE1H8Lh-TZxEdy7w1ks-73WKhIJEh39vfPU_1lMRGLxlXJX-hQMqEgkXFGRzTmmtDBFpM7afXwKFdioSCQUerjbVtQBdEbk5AyokRkpFKhIJ6KWlSSsNWhQRdiJD-0qte0Rhh5txqrO_1wd0&tbo=u&sa=X&ved=2ahUKEwj78KXT2Z7nAhUSblAKHc0aDOYQuIIBegQIARA5&biw=1280&bih=922&dpr=1
#include "rocne_obdobia.h"
#include "../../settings.h"
#include "../utils/my_button.h"
#include "../utils/my_scenes.h"
#include <QDebug>
#include <QKeyEvent>
#include <qrandom.h>
#include <QPropertyAnimation>
#include <QState>
#include <QSignalTransition>
#include <QParallelAnimationGroup>

#define DEF_DEBUG

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

    //timer
    timer_answer = new QTimer();
    timer_answer->setSingleShot(true);

    startFirstPart_pexeso();

    /*State init*/
    stateMachine = new QStateMachine();
    par_stat1 = new QState();
    par_stat2 = new QState();
    stateFinal_1 =new QFinalState();
    state11 = new QState(par_stat1);
    state12 = new QState(par_stat1);
    state13 = new QState(par_stat1);
    state21 = new QState(par_stat2);
    state22 = new QState(par_stat2);
    state23 = new QState(par_stat2);
    state24 = new QState(par_stat2);
    par_stat1->setInitialState(state11);
    par_stat2->setInitialState(state21);
    stateMachine->addState(par_stat1);
    stateMachine->addState(par_stat2);
    stateMachine->addState(stateFinal_1);
    stateMachine->setInitialState(par_stat1);

    scoreText_Item = new QGraphicsTextItem();
    scoreText_Item->setPlainText("0 bodov");
    QFont titleFont(FONT_IN_GAME,FONT_GAME_SIZE1);
    scoreText_Item->setFont(titleFont);
    scoreText_Item->setPos(WIDTH_SCREAN-100 - scoreText_Item->boundingRect().width()/2,HIGHT_SCREAN-100);
    scene->addItem(scoreText_Item);

    my_Items::generateRandomNumberWithoutRepetition(randomSett,16,1,17);
}

Rocne_obdobia::~Rocne_obdobia()
{
    //Removes and deletes all items from the scene
    scene->clear();
    delete scene;
    if(timer)
        delete timer;
    if(timer_answer)
        delete timer_answer;
    if(movie){
       #ifdef DEF_DEBUG
        qDebug() << "~Rocne_obdobia.cpp 78 delete movie";
       #endif
        delete movie;
    }
    if(hracieKarty.size())
        hracieKarty.clear();
    if(up_item.size())
        up_item.clear();
    delete stateMachine;
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
    pexeso_Items* item;
    my_Items* my_it;
    QSize velkost(110,100);
    QString textura ,texturaON,zadnaStrana = ":/game/rokObdobia/games/G_MaOS_RocneObdobia/textur/zadnaStrana.png";
    int hodnota = 0;

    //set karticky
    for(int i = 0;i<16;i++) {       //hodnoty suborov sa rovnaju s nazvami s
        hodnota = i < 8 ? i : i-8;
        if (hodnota<4) {
            textura = ":/game/rokObdobia/games/G_MaOS_RocneObdobia/textur/" + QString::number(hodnota+1) + ".jpg";
            QPixmap pix(textura);
            item = new pexeso_Items(pix,textura,textura,velkost,hodnota);
        } else {
            textura = ":/game/rokObdobia/games/G_MaOS_RocneObdobia/textur/" + QString::number(hodnota+1) + ".png";
            texturaON = ":/game/rokObdobia/games/G_MaOS_RocneObdobia/textur/" + QString::number(hodnota+1) + "_ON.png";
            QPixmap pix(textura);
            item = new pexeso_Items(pix,textura,texturaON,velkost,hodnota);
        }
        //item->hide();
        item->setPos(points_pexeso[i]);
        hracieKarty.push_back(item);
        scene->addItem(item);

        my_it = new my_Items(points_pexeso[i],zadnaStrana,velkost,hodnota);
        connect(my_it,SIGNAL(pressed(my_Items*)),this,SLOT(s_click_on_Card(my_Items*)));
        hracieKarty_back[cf_row][cf_coll] = my_it;
        scene->addItem(my_it);

        cf_row++;
        if(cf_row == 4){
            cf_coll++;
            cf_row = 0;
        }
    }

    //set init focus
    changeFocus();

    //set status game
    gameStatus = FINDING_PEXESO_FIRST;
}

void Rocne_obdobia::initStates()
{
    pexeso_Items *item;
    QString textura, texturaON;
    QSize velkost(150,150);
    qreal first_scale;
    timer->setInterval(1000);
    timer->setSingleShot(false);
    timer->start();
    hracieKarty.clear();

    my_Items::generateRandomNumberWithoutRepetition(randomSett,8,1,9);

    for(int i = 0;i<8;i++) {       //hodnoty suborov sa rovnaju s nazvami s
        if (randomSett[i]<5) {
            textura = ":/game/rokObdobia/games/G_MaOS_RocneObdobia/textur/" + QString::number(randomSett[i]) + ".jpg";
            QPixmap pix(textura);
            item = new pexeso_Items(pix,textura,textura,velkost,randomSett[i]);
            item->setTransformationMode(Qt::SmoothTransformation);
            up_item.push_back(item);
        } else {
            textura = ":/game/rokObdobia/games/G_MaOS_RocneObdobia/textur/" + QString::number(randomSett[i]) + ".png";
            texturaON = ":/game/rokObdobia/games/G_MaOS_RocneObdobia/textur/" + QString::number(randomSett[i]) + "_ON.png";
            QPixmap pix(textura);
            item = new pexeso_Items(pix,textura,texturaON,velkost,randomSett[i]-4);
            hracieKarty.push_back(item);
            connect(item,SIGNAL(pressed(pexeso_Items*)),this,SLOT(s_click_pexesoItems(pexeso_Items *)));
        }
        scene->addItem(item);
    }

    //setting innitPoint[i]
    QPoint point(WIDTH_SCREAN/2-700,HIGHT_SCREAN/2-200);
    for (int i = 0; i < 8; i++) {
        if(i < 4){
            point.setX(point.x()+250);
            innitPoint[i] = point;
        } else if(i == 4){
            point.setX(WIDTH_SCREAN/2-450);
            point.setY(HIGHT_SCREAN/2+100);
            innitPoint[i] = point;
        } else {
            point.setX(point.x()+250);
            innitPoint[i] = point;
        }
    }
    //seting states
    for (int i = 0; i < 4; i++) {
        //_____State 11
        state11->assignProperty(hracieKarty.at(i), "pos", points_pexeso[i+4]);
        state11->assignProperty(hracieKarty.at(i), "opacity", qreal(0.1));
        state11->assignProperty(up_item.at(i), "pos", points_pexeso[i]);
        state11->assignProperty(up_item.at(i), "opacity", qreal(0.1));
        //_____State 12
        state12->assignProperty(hracieKarty.at(i), "pos", points_pexeso[i+4]);
        state12->assignProperty(hracieKarty.at(i), "opacity", qreal(1));
        state12->assignProperty(up_item.at(i), "pos", points_pexeso[i]);
        state12->assignProperty(up_item.at(i), "opacity", qreal(1));
        //_____State 13
        state13->assignProperty(hracieKarty.at(i), "pos",innitPoint[i+4]);
        state13->assignProperty(hracieKarty.at(i), "opacity", qreal(1));
        state13->assignProperty(up_item.at(i), "pos", innitPoint[i]);
        state13->assignProperty(up_item.at(i), "opacity", qreal(1));

        // #### States 2x
        point.setX(WIDTH_SCREAN/2-(hracieKarty.at(i)->pixmap().size().width()/2));
        point.setY(HIGHT_SCREAN/2-200);
        first_scale = hracieKarty[0]->scale();
        //_____State 21
        if (i == 0){
            state21->assignProperty(up_item.at(i), "opacity", qreal(1));
            state21->assignProperty(up_item.at(i), "pos",point);//stred Obrazovky
            state21->assignProperty(up_item.at(i), "scale",first_scale+1);

            state22->assignProperty(up_item.at(i), "opacity", qreal(0));
            state22->assignProperty(up_item.at(i), "pos",innitPoint[i]);
            state22->assignProperty(up_item.at(i), "scale",first_scale);

            state23->assignProperty(up_item.at(i), "opacity", qreal(0));
            state23->assignProperty(up_item.at(i), "pos",innitPoint[i]);
            state23->assignProperty(up_item.at(i), "scale",first_scale);

            state24->assignProperty(up_item.at(i), "opacity", qreal(0));
            state24->assignProperty(up_item.at(i), "pos",innitPoint[i]);
            state24->assignProperty(up_item.at(i), "scale",first_scale);
        } else if (i == 1)  {
            state21->assignProperty(up_item.at(i), "opacity", qreal(0));
            state21->assignProperty(up_item.at(i), "pos",innitPoint[i]);
            state21->assignProperty(up_item.at(i), "scale",first_scale);

            state22->assignProperty(up_item.at(i), "opacity", qreal(1));
            state22->assignProperty(up_item.at(i), "pos",point);
            state22->assignProperty(up_item.at(i), "scale",first_scale+1);

            state23->assignProperty(up_item.at(i), "opacity", qreal(0));
            state23->assignProperty(up_item.at(i), "pos",innitPoint[i]);
            state23->assignProperty(up_item.at(i), "scale",first_scale);

            state24->assignProperty(up_item.at(i), "opacity", qreal(0));
            state24->assignProperty(up_item.at(i), "pos",innitPoint[i]);
            state24->assignProperty(up_item.at(i), "scale",first_scale);
        } else if (i == 2) {
            state21->assignProperty(up_item.at(i), "opacity", qreal(0));
            state21->assignProperty(up_item.at(i), "pos",innitPoint[i]);
            state21->assignProperty(up_item.at(i), "scale",first_scale);

            state22->assignProperty(up_item.at(i), "opacity", qreal(0));
            state22->assignProperty(up_item.at(i), "pos",innitPoint[i]);
            state22->assignProperty(up_item.at(i), "scale",first_scale);

            state23->assignProperty(up_item.at(i), "opacity", qreal(1));
            state23->assignProperty(up_item.at(i), "pos",point);
            state23->assignProperty(up_item.at(i), "scale",first_scale+1);

            state24->assignProperty(up_item.at(i), "opacity", qreal(0));
            state24->assignProperty(up_item.at(i), "pos",innitPoint[i]);
            state24->assignProperty(up_item.at(i), "scale",first_scale);
        }
        else if (i == 3) {
            state21->assignProperty(up_item.at(i), "opacity", qreal(0));
            state21->assignProperty(up_item.at(i), "pos",innitPoint[i]);
            state21->assignProperty(up_item.at(i), "scale",first_scale);

            state22->assignProperty(up_item.at(i), "opacity", qreal(0));
            state22->assignProperty(up_item.at(i), "pos",innitPoint[i]);
            state22->assignProperty(up_item.at(i), "scale",first_scale);

            state23->assignProperty(up_item.at(i), "opacity", qreal(0));
            state23->assignProperty(up_item.at(i), "pos",innitPoint[i]);
            state23->assignProperty(up_item.at(i), "scale",first_scale);

            state24->assignProperty(up_item.at(i), "opacity", qreal(1));
            state24->assignProperty(up_item.at(i), "pos",point);
            state24->assignProperty(up_item.at(i), "scale",first_scale+1);
        }
        state21->assignProperty(hracieKarty.at(i), "pos",innitPoint[i+4]);
        state21->assignProperty(hracieKarty.at(i), "opacity", qreal(1));
        state22->assignProperty(hracieKarty.at(i), "pos",innitPoint[i+4]);
        state22->assignProperty(hracieKarty.at(i), "opacity", qreal(1));
        state23->assignProperty(hracieKarty.at(i), "pos",innitPoint[i+4]);
        state23->assignProperty(hracieKarty.at(i), "opacity", qreal(1));
        state24->assignProperty(hracieKarty.at(i), "pos",innitPoint[i+4]);
        state24->assignProperty(hracieKarty.at(i), "opacity", qreal(1));
    }

    QParallelAnimationGroup *group = new QParallelAnimationGroup();
    for (int i = 0; i < 4; i++) {
        QPropertyAnimation *anim3 = new QPropertyAnimation(up_item[i], "scale");
        //anim3->setDuration(750 + i * 25);
        //anim3->setEndValue(anim3->startValue());
        //anim3->setEasingCurve(QEasingCurve::InOutBack);
        group->addAnimation(anim3);
        QPropertyAnimation *anim = new QPropertyAnimation(up_item[i], "pos");
        anim->setDuration(750 + i * 25);
        anim->setEasingCurve(QEasingCurve::InOutBack);
        group->addAnimation(anim);
        QPropertyAnimation *anim2 = new QPropertyAnimation(up_item[i], "opacity");
        group->addAnimation(anim2);
        QPropertyAnimation *anim4 = new QPropertyAnimation(hracieKarty[i], "pos");
        group->addAnimation(anim4);
        QPropertyAnimation *anim5 = new QPropertyAnimation(hracieKarty[i], "opacity");
        group->addAnimation(anim5);
    }
    QAbstractTransition *trans = state11->addTransition(timer,&QTimer::timeout, state12);
    trans->addAnimation(group);

    trans = state12->addTransition(timer,&QTimer::timeout, state13);
    trans->addAnimation(group);

    trans = state13->addTransition(timer,&QTimer::timeout, state21);
    trans->addAnimation(group);

    trans = state21->addTransition(this,&Rocne_obdobia::nextState, state22);
    trans->addAnimation(group);

    trans = state22->addTransition(this,&Rocne_obdobia::nextState, state23);
    trans->addAnimation(group);

    trans = state23->addTransition(this,&Rocne_obdobia::nextState, state24);
    trans->addAnimation(group);

    trans = state24->addTransition(this,&Rocne_obdobia::nextState, stateFinal_1);
    trans->addAnimation(group);

    //connect final states
    connect(stateMachine,SIGNAL(finished()),this,SLOT(s_stopDestroy_AnimationTimer()));

    stateMachine->start();
}

void Rocne_obdobia::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Down){
        moveDown();
    } else if(event->key() == Qt::Key_Up){
        moveUp();
    } else if(event->key() == Qt::Key_Left){
        moveLeft();
    } else if(event->key() == Qt::Key_Right){
        moveRight();
    } else if (event->key() == Qt::Key_Enter) {
        pressEnter();
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

void Rocne_obdobia::s_click_on_Card(my_Items *item)
{
    //nastavenie focusu
    if(item != hracieKarty_back[cf_row][cf_coll]){
        hracieKarty_back[cf_row][cf_coll]->focusOut();
        //find and set focus
        findFocus_item(item);
    }

    switch (gameStatus) {
        case FINDING_PEXESO_FIRST:
            openFirst = item;
            item->start_open_Animation();

            gameStatus = FINDING_PEXESO_PAIR;
            break;
        case FINDING_PEXESO_PAIR:
            item->start_open_Animation();
            if(openFirst->getHodnota() == item->getHodnota()){
                score++;
                scoreText_Item->setPlainText(QString::number(score) +" bodov");
                if(score == 8){
                    gameStatus = END_PEXESO_GAME;
                    endPexeso_startPriradenie();
                }
            } else {
                //Set focus OUT exture and if not visible show it
                openFirst->focusOut_withTimeout(3000);
                item->focusOut_withTimeout(3000);
            }
            gameStatus = FINDING_PEXESO_FIRST;

            break;
        default:

            break;
    }
    //changeFocus();
}

//STARTING PRIRADENIA GAME
void Rocne_obdobia::s_endPexeso_startPriradenie()
{
    timer->stop();
    disconnect(timer,SIGNAL(timeout()),this,SLOT(s_endPexeso_startPriradenie()));

    //remove and delete all items
    scene->clear();
    //nastavuje hracieKarty a stvy
    initStates();

    //napoveda
    scene->addItem(My_scenes::get_napoveda());
    scene->addItem(My_button::showTitleText("Aké ročné obdobie je zachytené na tomto obrázku?"));

    currentFocus_prirad = hracieKarty.begin();
    currentFocus_prirad.operator*()->focusIn();
    gameStatus = START_PRIRADENIA_GAME;
}

void Rocne_obdobia::endPexeso_startPriradenie()
{
    foreach (pexeso_Items *var, hracieKarty) {
        var->hide();
    }
    scene->addItem(My_button::drawPanel(0,0,WIDTH_SCREAN,HIGHT_SCREAN,Qt::black,0.65));

    // draw panel
    scene->addItem(My_button::drawPanel(WIDTH_SCREAN/2-275,HIGHT_SCREAN/2-250,550,450,Qt::lightGray,0.75));

    // texty
    scene->addItem(My_button::show_own_TitleText("Výborne!",QPoint(WIDTH_SCREAN/2,HIGHT_SCREAN/2-220),30,true));
    scene->addItem(My_button::show_own_TitleText("Ale ešte sa sústreď a pomôž mi správne priradiť obrázky.",QPoint(WIDTH_SCREAN/2-250,HIGHT_SCREAN/2-150),30,false,500));

    // img Matko
    scene->addItem(My_button::showImage(QPoint(WIDTH_SCREAN/2+20,HIGHT_SCREAN/2-40),":/game/score/games/utils/textur/Matko_postavicka.png",QSize(150,250)));

    timer = new QTimer();
    timer->setInterval(5000);
    timer->setSingleShot(true);
    connect(timer,SIGNAL(timeout()),this,SLOT(s_endPexeso_startPriradenie()));
    timer->start();
}

// CONNECT ON FINAL STATE
void Rocne_obdobia::s_stopDestroy_AnimationTimer()
{
    timer->stop();
    disconnect(stateMachine,SIGNAL(finished()),this,SLOT(s_stopDestroy_AnimationTimer()));
   #ifdef DEF_DEBUG
    qDebug() << "s_stopDestroy_AnimationTimer() stop Timer and delete it, disconnect ";
   #endif
    timer->setInterval(1500);
    timer->setSingleShot(true);
    connect(timer,SIGNAL(timeout()),this,SLOT(s_showGameOver()));
    timer->start();
}

void Rocne_obdobia::s_click_pexesoItems(pexeso_Items *item)
{
    // QStateMachine::configuration() gives you the current states.
    if(stateMachine->configuration().contains(state21) && item->getHodnota() == up_item[0]->getHodnota())  {
        show_Answer(true);
        #ifdef DEF_DEBUG
         qDebug() << "s_click_pexesoItems() state21 ";
        #endif
    } else if (stateMachine->configuration().contains(state22) && item->getHodnota() == up_item[1]->getHodnota())  {
        show_Answer(true);
        #ifdef DEF_DEBUG
         qDebug() << "s_click_pexesoItems() state22 ";
        #endif
    } else if(stateMachine->configuration().contains(state23) && item->getHodnota() == up_item[2]->getHodnota())   {
        show_Answer(true);
        #ifdef DEF_DEBUG
         qDebug() << "s_click_pexesoItems() state23 ";
        #endif
    } else if (stateMachine->configuration().contains(state24) && item->getHodnota() == up_item[3]->getHodnota())  {
        show_Answer(true);
        #ifdef DEF_DEBUG
         qDebug() << "s_click_pexesoItems() state24 ";
        #endif
    } else {
        show_Answer(false);
    }
}

void Rocne_obdobia::s_showIncorrectMessage()
{
    scene->removeItem(answer);
    disconnect(timer_answer,SIGNAL(timeout()),this,SLOT(s_showIncorrectMessage()));

    delete answer;
    answer = nullptr;

    if (b_answer){
        //nova otazka
        emit nextState();
    }
}

void Rocne_obdobia::show_Answer(bool ans)
{
    if(answer==nullptr) {
        if(ans){
            answer = My_button::showImage(QPoint(WIDTH_SCREAN/2,HIGHT_SCREAN/2-40),":/game/score/games/utils/textur/answer_correct.png",QSize(80,80));
            b_answer = true;
        } else {
            answer = My_button::showImage(QPoint(WIDTH_SCREAN/2,HIGHT_SCREAN/2-40),":/game/score/games/utils/textur/answer_wrong.png",QSize(80,80));
            b_answer = false;
        }
        scene->addItem(answer);

        //timer_answer is singleshot timer & initialized in constructor
        timer_answer->setInterval(1500);
        connect(timer_answer,SIGNAL(timeout()),this,SLOT(s_showIncorrectMessage()));
        timer_answer->start();
    }
}

void Rocne_obdobia::s_showGameOver()
{
    gameStatus = END_PEXESO_GAME;
    scene->addItem(My_button::drawPanel(0,0,WIDTH_SCREAN,HIGHT_SCREAN,Qt::black,0.65));

    // draw panel
    scene->addItem(My_button::drawPanel(WIDTH_SCREAN/2-275,HIGHT_SCREAN/2-250,550,450,Qt::lightGray,0.75));

    // texty
    scene->addItem(My_button::show_own_TitleText("Koniec hry",QPoint(WIDTH_SCREAN/2,HIGHT_SCREAN/2-220),30,true));

    scene->addItem(My_button::show_own_TitleText("Si veľmi škovný",QPoint(WIDTH_SCREAN/2,HIGHT_SCREAN/2-180),30,true));

    // parent item for Button
    //QGraphicsRectItem *game_OverButtons_parent = new QGraphicsRectItem();

    /*My_button* playAgain = new My_button(QString("Hrať znova"),game_OverButtons_parent);
    playAgain->setPos(410,HIGHT_SCREAN/2+50);
    connect(playAgain,SIGNAL(clicked()),this,SLOT(s_restartGame()));*/

    My_button* close = new My_button(QString("Koniec"));
    close->setPos(410,HIGHT_SCREAN/2+105);
    connect(close,SIGNAL(clicked()),this,SLOT(close()));

    scene->addItem(close);

    /*ADD Gif*/
    scene->addWidget(My_button::showGif(movie,QString(":/game/score/games/utils/textur/hviezdicky.gif"),QPoint(WIDTH_SCREAN/2-75,HIGHT_SCREAN/2-110)));

}

void Rocne_obdobia::pressEnter()
{
    if(gameStatus == FINDING_PEXESO_PAIR || gameStatus == FINDING_PEXESO_FIRST){
        s_click_on_Card(hracieKarty_back[cf_row][cf_coll]);
    } else if(gameStatus == START_PRIRADENIA_GAME) {
        s_click_pexesoItems(currentFocus_prirad.operator*());
    }
}

//po otoceni karty zmena focusu a delete from 2d array
void Rocne_obdobia::changeFocus()
{
    for(int i = 0;i<4;i++){
        for(int j = 0;j<4;j++){
            if(hracieKarty_back[i][j]->isVisible()){
                cf_row = i;
                cf_coll = j;
                hracieKarty_back[i][j]->focusIn();
                return;
            }
        }
    }
    //ak nezostane ziadna karta na hracom poli
    gameStatus = END_PEXESO_GAME;
}

bool Rocne_obdobia::findFocus_nextRow_down()
{
    cf_row++;
    if(cf_row >= 4)
        cf_row = 0;

    for (int i =0;i<4;i++) {
        if(hracieKarty_back[cf_row][cf_coll]->isVisible()){
            return true;
        }
        cf_coll++;
        if(cf_coll>=4)
            cf_coll = 0;
    }
    return false;
}

bool Rocne_obdobia::findFocus_nextCOll_up()
{
    cf_row--;
    if(cf_row < 0)
        cf_row = 3;

    for (int i =0;i<4;i++) {
        if(hracieKarty_back[cf_row][cf_coll]->isVisible()){
            return true;
        }
        cf_coll++;
        if(cf_coll>=4)
            cf_coll = 0;
    }
    return false;
}

void Rocne_obdobia::findFocus_item(my_Items *it)
{
    for (int i =0;i<4;i++) {
        for (int j =0;j<4;j++) {
            if(it == hracieKarty_back[i][j]){
                cf_row =i;
                cf_coll=j;
                hracieKarty_back[cf_row][cf_coll]->focusIn();
                return;
            }
        }
    }
}

void Rocne_obdobia::moveRight()
{
    if(gameStatus == FINDING_PEXESO_PAIR || gameStatus == FINDING_PEXESO_FIRST){
        hracieKarty_back[cf_row][cf_coll] ->focusOut();
        for(int i = 0;i<3;i++) {
            cf_coll++;
            if(cf_coll>=4)
                cf_coll = 0;
            if(hracieKarty_back[cf_row][cf_coll]->isVisible()){
                hracieKarty_back[cf_row][cf_coll]->focusIn();
                return;
            }
        }
        for(int i = 0;i<4;i++) {
            if(findFocus_nextRow_down()){
                hracieKarty_back[cf_row][cf_coll]->focusIn();
                return;
            }
        }
        gameStatus = END_PEXESO_GAME;
    } else if(gameStatus == START_PRIRADENIA_GAME) {
       #ifdef DEF_DEBUG
        qDebug() << "moveRight() run ";
       #endif
        currentFocus_prirad.operator*()->focusOut();
        currentFocus_prirad++;
        if(currentFocus_prirad == hracieKarty.end()){
            currentFocus_prirad = hracieKarty.begin();
        }
        currentFocus_prirad.operator*()->focusIn();
    }

}

void Rocne_obdobia::moveLeft()
{
    if(gameStatus == FINDING_PEXESO_PAIR || gameStatus == FINDING_PEXESO_FIRST){
        hracieKarty_back[cf_row][cf_coll] ->focusOut();
        for(int i = 0;i<3;i++) {
            cf_coll--;
            if(cf_coll<0)
                cf_coll = 3;
            if(hracieKarty_back[cf_row][cf_coll]->isVisible()){
                hracieKarty_back[cf_row][cf_coll]->focusIn();
                return;
            }
        }
        for(int i = 0;i<4;i++) {
            if(findFocus_nextRow_down()){
                hracieKarty_back[cf_row][cf_coll]->focusIn();
                return;
            }
        }
        gameStatus = END_PEXESO_GAME;
    } else if(gameStatus == START_PRIRADENIA_GAME) {
       #ifdef DEF_DEBUG
        qDebug() << "moveLeft() run ";
       #endif
        currentFocus_prirad.operator*()->focusOut();
        currentFocus_prirad--;
        if(currentFocus_prirad == hracieKarty.begin()-1){
            currentFocus_prirad =(hracieKarty.end()-1);
        }
        currentFocus_prirad.operator*()->focusIn();
    }
}

void Rocne_obdobia::moveUp()
{
    if(gameStatus == FINDING_PEXESO_PAIR || gameStatus == FINDING_PEXESO_FIRST){
        hracieKarty_back[cf_row][cf_coll] ->focusOut();
        for(int i = 0;i<4;i++) {
            if(findFocus_nextCOll_up()){
                hracieKarty_back[cf_row][cf_coll]->focusIn();
                return;
            }
        }
        gameStatus = END_PEXESO_GAME;
    }
}

void Rocne_obdobia::moveDown()
{
     if(gameStatus == FINDING_PEXESO_PAIR || gameStatus == FINDING_PEXESO_FIRST){
        hracieKarty_back[cf_row][cf_coll] ->focusOut();
        for(int i = 0;i<4;i++) {
            if(findFocus_nextRow_down()){
                hracieKarty_back[cf_row][cf_coll]->focusIn();
                return;
            }
        }
        gameStatus = END_PEXESO_GAME;
    }
}




