#include "lietadielka.h"
#include "../../settings.h"
#include <QDebug>
#include <QKeyEvent>
#include "../utils/my_button.h"
#include "boss.h"

G_Status GAME_renderStatus;

Lietadielka::Lietadielka(QWidget *parent)
{
    Q_UNUSED(parent)
    //init sceny
    scene = new QGraphicsScene(this);

    scene->setSceneRect(0,0,WIDTH_SCREAN,HIGHT_SCREAN); // make the scene 800x600 instead of infinity by infinity (default)

    scene->setBackgroundBrush(QBrush(QColor(50, 50, 90)));
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(WIDTH_SCREAN,HIGHT_SCREAN);
    setScene(scene);

    //init game
    GAME_renderStatus = ENEMY_FIGHT;
    init_Game();
}

Lietadielka::~Lietadielka()
{
    #ifdef DEF_DEBUG
     qDebug() << "~Lietadielka() clear scene!";
    #endif
    scene->clear();

    if(timer){
        #ifdef DEF_DEBUG
         qDebug() << "Delete timer in ~Lietadielka()";
        #endif
        delete timer;
    }
    if(animation){
        #ifdef DEF_DEBUG
         qDebug() << "Delete animation in ~Lietadielka()";
        #endif
        delete animation;
    }
    //delete colisions_timer;
    delete spawnEnemy_timer;
    //delete timer_ShootTimout;
}

void Lietadielka::init_Game()
{
    //qTimers
    spawnEnemy_timer = new QTimer();
    spawnEnemy_timer->setInterval(800);
    connect(spawnEnemy_timer,SIGNAL(timeout()),this,SLOT(s_spawnEnemy()));
    spawnEnemy_timer->start();

    colisions_timer = new QTimer(this);
    colisions_timer->setInterval(300);
    connect(colisions_timer,SIGNAL(timeout()),this,SLOT(s_check_Collision_forPlayer()));
    colisions_timer->start();

    timer_ShootTimout = new QTimer(this);
    timer_ShootTimout->setInterval(500);
    connect(timer_ShootTimout,SIGNAL(timeout()),this,SLOT(s_resetPlayerShoot()));
    timer_ShootTimout->start();

    QPixmap player_Pix(":/game/lietadla/games/G_Zab_Lietadielka/textur/player.png");
    player = new Player(WIDTH_SCREAN/2-50,HIGHT_SCREAN-125,player_Pix.scaled(100,100));
    scene->addItem(player);

    skore = My_button::show_own_TitleText(QString::number(score)+" bodov",QPoint(WIDTH_SCREAN-80,HIGHT_SCREAN-50),
                                          FONT_GAME_SIZE2,true);
    scene->addItem(skore);

    keyTimerEvent.setInterval(30);
    connect(&keyTimerEvent,SIGNAL(timeout()),this,SLOT(s_processAllKeys()));
    keyTimerEvent.start();
}

void Lietadielka::player_shot()
{
    if(is_shootRedy)    {
        is_shootRedy = false;
        Strela *shot = player->bullet(true);
        if(shot != nullptr){
            connect(shot,SIGNAL(sig_is_outOfScrean(Strela *,bool)),this,SLOT(s_deleteBullet(Strela *,bool)));
            scene->addItem(shot);
        }

        shot = player->bullet(false);
        if(shot != nullptr){
            connect(shot,SIGNAL(sig_is_outOfScrean(Strela *,bool)),this,SLOT(s_deleteBullet(Strela *,bool)));
            scene->addItem(shot);
        }
    }
}

void Lietadielka::spawn_boss()
{
    QPixmap aa(":/game/lietadla/games/G_Zab_Lietadielka/textur/bos.png");
    boss = new Boss(&aa ,QSize(200,100),WIDTH_SCREAN/2-100,10);
    connect(boss,SIGNAL(sig_destroy_boss()),this,SLOT(s_deleteBoss()));
    GAME_renderStatus = BOSS_FIGHT;

    timer = new QTimeLine(10000);
    timer->setFrameRange(0, 100);
    timer->setLoopCount(40);

    animation = new QGraphicsItemAnimation;
    animation->setItem(boss);
    animation->setTimeLine(timer);

    for (int i = 0; i < 200; ++i)
        animation->setPosAt(i/400.,QPointF(i*(WIDTH_SCREAN/202),10));

    int a = 200;
    for (int i = 200; i < 400; ++i)
        animation->setPosAt(i/400.,QPointF((a--)*(WIDTH_SCREAN/202),10));

    scene->addItem(boss);
    //musísť až po priradení do scény
    boss->add_HealthBar();
    timer->start();

}

void Lietadielka::s_showGameOwer()
{
    disconnect(&pom_timer,SIGNAL(timeout()),this,SLOT(s_showGameOwer()));

    // pop up semi transparent panel
    scene->addItem(My_button::drawPanel(0,0,WIDTH_SCREAN,HIGHT_SCREAN,Qt::black,0.65));

    // draw panel
    scene->addItem(My_button::drawPanel(WIDTH_SCREAN/2-250,HIGHT_SCREAN/2-200,500,400,Qt::lightGray,0.75));

    QGraphicsTextItem* titleText = new QGraphicsTextItem("Koniec hry:");
    titleText->setTextWidth(400);
    QFont titleFont("Farm to Market Fancy",50);
    titleText->setFont(titleFont);
    titleText->setPos(WIDTH_SCREAN/2 - titleText->boundingRect().width()/2,HIGHT_SCREAN/2-200);
    scene->addItem(titleText);

    // parent item for Button
    QGraphicsRectItem *game_OverButtons_parent = new QGraphicsRectItem();

    /*My_button* playAgain = new My_button(QString("Hrať znova"),game_OverButtons_parent);
    playAgain->setPos(410,HIGHT_SCREAN/2+50);
    connect(playAgain,SIGNAL(clicked()),this,SLOT(restartGame()));*/

    My_button* close = new My_button(QString("Koniec"),game_OverButtons_parent);
    close->setPos(410,HIGHT_SCREAN/2+105);
    connect(close,SIGNAL(clicked()),this,SLOT(close()));

    scene->addItem(game_OverButtons_parent);

    /*ADD Gif*/
    scene->addWidget(My_button::showGif(QString(":/game/score/games/utils/textur/smajlik.gif"),QPoint(WIDTH_SCREAN/2+50,HIGHT_SCREAN/2-110)));
}

void Lietadielka::s_processAllKeys()
{
    if(keys[Qt::Key_Up])
    {
        player->goUp();
    }
    if(keys[Qt::Key_Down])
    {
        player->goDown();
    }
    if(keys[Qt::Key_Left])
    {
        player->goLeft();
    }
    if(keys[Qt::Key_Right])
    {
        player->goRight();
    }
    if(keys[Qt::Key_Space])
    {
        player_shot();
    }
}

void Lietadielka::s_resetPlayerShoot()
{
    is_shootRedy = true;
}

void Lietadielka::keyPressEvent(QKeyEvent *event)
{
    keys[event->key()] = true;
    QWidget::keyPressEvent(event);
}

void Lietadielka::keyReleaseEvent(QKeyEvent *event)
{
    keys[event->key()] = false;
    QWidget::keyReleaseEvent(event);
}

void Lietadielka::s_deleteEnemy(Enemy *en)
{
   #ifdef DEF_DEBUG
    qDebug() << "Delete enemy";
   #endif
    disconnect(en,SIGNAL(sig_is_outOfScrean(Enemy *)),this,SLOT(s_deleteEnemy(Enemy *)));
    scene->removeItem(en);
    delete en;
}

void Lietadielka::s_deleteBullet(Strela *bull,bool incScore)
{
   #ifdef DEF_DEBUG
    qDebug() << "Delete bullet";
   #endif
    disconnect(bull,SIGNAL(sig_is_outOfScrean(Strela *,bool)),this,SLOT(s_deleteBullet(Strela *,bool)));
    scene->removeItem(bull);
    delete bull;

    if(incScore){
        score++;
        skore->setPlainText(QString::number(score)+" bodov");
        if(score == 10 && !boss){
            //spawn boos
            spawn_boss();
        } else if (boss) {

        }
    }
}

void Lietadielka::s_deleteBoss()
{
    //timeline step
    timer->stop();

    disconnect(boss,SIGNAL(sig_destroy_boss()),this,SLOT(s_deleteBoss()));
    scene->removeItem(boss);
    delete boss;

    GAME_renderStatus = ENEMY_FIGHT;
}

void Lietadielka::s_spawnEnemy()
{
    if(GAME_renderStatus == ENEMY_FIGHT)   {
        Enemy *enemy = new Enemy(":/game/lietadla/games/G_Zab_Lietadielka/textur/enemy.png",QSize(70,70),(rand()%(WIDTH_SCREAN-140))+70,1);
        enemy->startMovment_downUp(true);
        connect(enemy,SIGNAL(sig_is_outOfScrean(Enemy *)),this,SLOT(s_deleteEnemy(Enemy *)));

        scene->addItem(enemy);
    }
}

void Lietadielka::s_check_Collision_forPlayer()
{
    QList<QGraphicsItem *> colliding_items = player->collidingItems();
    for (int i = 0;i < colliding_items.size(); ++i){
        if (typeid(*(colliding_items[i])) == typeid(Enemy)){
            colisions_timer->stop();
            GAME_renderStatus = GAME_OWER;
            if(boss != nullptr)
                timer->stop();

            pom_timer.setInterval(1500);
            pom_timer.setSingleShot(true);
            connect(&pom_timer,SIGNAL(timeout()),this,SLOT(s_showGameOwer()));
            pom_timer.start();
        } else if (typeid(*(colliding_items[i])) == typeid(Strela)) {
            Strela* it = dynamic_cast<Strela*>(colliding_items.operator[](i));
            if(it->hodnota != 0){ // 0 player
                colisions_timer->stop();
                GAME_renderStatus = GAME_OWER;
                //stop bossa
                timer->stop();

                pom_timer.setInterval(1500);
                pom_timer.setSingleShot(true);
                connect(&pom_timer,SIGNAL(timeout()),this,SLOT(s_showGameOwer()));
                pom_timer.start();
            }
        } else if (typeid(*(colliding_items[i])) == typeid(Boss)) {
            colisions_timer->stop();
            GAME_renderStatus = GAME_OWER;
            if(boss != nullptr)
                timer->stop();

            pom_timer.setInterval(1500);
            pom_timer.setSingleShot(true);
            connect(&pom_timer,SIGNAL(timeout()),this,SLOT(s_showGameOwer()));
            pom_timer.start();
        }
    }
}
