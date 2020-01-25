#include "prirad_tiene.h"
#include <QDebug>
#include <QMouseEvent>
#include <qgraphicsitem.h>
#include "../utils/my_button.h"
#include <QMovie>

PriradTiene::PriradTiene(QWidget *parent)
{
    Q_UNUSED(parent)

    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,WIDTH_SCREAN,HIGHT_SCREAN); // make the scene 800x600 instead of infinity by infinity (default)

    QImage aa(":/game/tiene/games/G_MaOS_tiene/textur/tiene_BG.png");
    scene->setBackgroundBrush(QBrush(aa.scaled(WIDTH_SCREAN,HIGHT_SCREAN,Qt::IgnoreAspectRatio)));

    setScene(scene);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(WIDTH_SCREAN,HIGHT_SCREAN);

    kurzor = nullptr;
    setMouseTracking(true);

    setNewGame();
}

PriradTiene::~PriradTiene()
{
    scene->clear();
    l_animal.clear();
    if(movie){
        qDebug() << "~prirad_Tiene.cpp 37 delete movie";
        delete movie;
    }
    delete scene;
}

void PriradTiene::pressEnter_Animal(Animal *a)
{
    if(!chandegMode)    {
        /*__Seting focus__*/
        //a->manual_Focus_IN();
        /*__End Seting focus*/
        chandegMode = true;
        chanded_mode_animal = a->getId();
        init_Kurzor(a->textur_OFF);
    }
}

void PriradTiene::pressEnter_Tiene(Tiene *t)
{
    int i = -1;

    if(chandegMode) {
        if(t->getId() == chanded_mode_animal) {
            t->set_focusIN();
            for (i = 0;i<l_animal.size();i++) {
                if(t->getId() == l_animal.operator[](i)->getId())
                    break;
            }
            if(i != -1)    {
                //scene->removeItem(l_animal.operator[](i));
                l_animal.operator[](i)->hide();
                l_animal.removeAt(i);
                change_Focus(true);
            }
            delete_Kurzor();
            chandegMode = false;
        }  else {
            chandegMode = false;
            delete_Kurzor();
        }
    }
}

void PriradTiene::pressEnter_ResetGame_Tiene(Tiene *t)
{
    Q_UNUSED(t)
    //Removes and deletes all items from the scene
    scene->clear();
    l_animal.clear(); //koli nedokoncenej hre
    setNewGame();
}

void PriradTiene::restartGame()
{
    if(movie){
        delete movie;
        movie = nullptr;
    }
    //Removes and deletes all items from the scene
    scene->clear();
    l_animal.clear(); //koli nedokoncenej hre
    setNewGame();
}

void PriradTiene::mouseMoveEvent(QMouseEvent *event)
{
    if (kurzor){
        kurzor->setPos(event->x()-(kurzor->pixmap().width()/2),event->y()-(kurzor->pixmap().height()/2));
    }
}

void PriradTiene::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Tab) {
        change_Focus(false);
    } else  if(event->key() == Qt::Key_Space) {
        showGameOver();
    }
}

void PriradTiene::moveUp()
{
    if(kurzor){
        QPointF currentPos = kurzor->pos();
        kurzor->setPos(currentPos.x(),currentPos.y()-MOVE_STEP);
    }
}

void PriradTiene::moveDown()
{
    if(kurzor){
        QPointF currentPos = kurzor->pos();
        kurzor->setPos(currentPos.x(),currentPos.y()+MOVE_STEP);
    }
}

void PriradTiene::moveLeft()
{
    if(kurzor){
        QPointF currentPos = kurzor->pos();
        kurzor->setPos(currentPos.x()+MOVE_STEP,currentPos.y());
    }
}

void PriradTiene::moveRight()
{
    if(kurzor){
        QPointF currentPos = kurzor->pos();
        kurzor->setPos(currentPos.x()-MOVE_STEP,currentPos.y());
    }
}

void PriradTiene::pressTab()
{
    change_Focus(false);
}

void PriradTiene::pressEnter()
{
    if(chandegMode){
        QList<QGraphicsItem *> colliding_items = kurzor->collidingItems();
        for (int i = 0, n = colliding_items.size(); i < n; ++i){
            if (typeid(*(colliding_items[i])) == typeid(Tiene)){
                Tiene *tien = dynamic_cast<Tiene*>(colliding_items.operator[](i)) ;
                pressEnter_Tiene(tien);
            }
        }
    } else {
        if (return_BTN_Focus)  {
            pressEnter_ResetGame_Tiene(reset_BTN);
        } else {
            if (l_animal.size() > 0){
                chandegMode = true;
                chanded_mode_animal = focus_iterator.operator*()->getId();
                init_Kurzor(focus_iterator.operator*()->textur_OFF);
            }
        }
    }
}

void PriradTiene::showGameOver()
{
    // pop up semi transparent panel
    scene->addItem(My_button::drawPanel(0,0,WIDTH_SCREAN,HIGHT_SCREAN,Qt::black,0.65));

    // draw panel
    scene->addItem(My_button::drawPanel(WIDTH_SCREAN/2-250,HIGHT_SCREAN/2-200,500,400,Qt::lightGray,0.75));

    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Super zvladol si to na:"));
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
    scene->addWidget(My_button::showGif(movie,QString(":/game/score/games/utils/textur/hviezdicky.gif"),
                                        QPoint(WIDTH_SCREAN/2-75,HIGHT_SCREAN/2-110)));
}

void PriradTiene::init_Kurzor(const QString textura)
{
    if(kurzor) {
        scene->removeItem(kurzor);
        delete  kurzor;
    }

    kurzor = new QGraphicsPixmapItem(textura);
    QPixmap aa = kurzor->pixmap();
    kurzor->setPixmap(aa.scaled(WIDTH_SCREAN/10,HIGHT_SCREAN/10,Qt::IgnoreAspectRatio));
    kurzor->setPos(5,5);
    scene->addItem(kurzor);
}

void PriradTiene::delete_Kurzor()
{
    scene->removeItem(kurzor);
    delete kurzor;
    kurzor = nullptr;
}

void PriradTiene::change_Focus(bool odznova)
{
    if(l_animal.size() > 0) {
        if(odznova){
            focus_iterator = l_animal.begin();
            focus_iterator.operator*()->manual_Focus_IN();
        } else {
            focus_iterator.operator*()->manual_Focus_OUT();
            focus_iterator++;
            if(focus_iterator < l_animal.end())    {
                focus_iterator.operator*()->manual_Focus_IN();
            } else {
                if(!return_BTN_Focus) {
                    focus_iterator--; // koli preteceniu
                    return_BTN_Focus = true;
                    reset_BTN->set_focusIN();
                } else {
                    return_BTN_Focus = false;
                    reset_BTN->set_focusOUT();
                    change_Focus(true);
                }
            }
        }
    } else {
        showGameOver();
        // end game
    }
}

void PriradTiene::setNewGame()
{
    QList<Animal*>::iterator it;
    QGraphicsTextItem* title = new QGraphicsTextItem("Priraď zvieratká k ich vlastným tieňom: ");
    title->setPos(15,0);
    QFont aa = QFont("Farm to Market Fancy");
    title->setFont(aa);
    title->setScale(4);
    scene->addItem(title);

    Tiene *tien;

    l_animal.push_back(new Animal(0,":/game/tiene/games/G_MaOS_tiene/textur/jezko.png"));
    tien = new Tiene(0);
    scene->addItem(tien);
    scene->addItem(l_animal.operator[](0));
    connect(tien,SIGNAL(pressed_On_Tiene(Tiene*)),this,SLOT(pressEnter_Tiene(Tiene *)));
    connect(l_animal.operator[](0),SIGNAL(pressed_On_Animal(Animal*)),this,SLOT(pressEnter_Animal(Animal*)));

    l_animal.push_back(new Animal(1,":/game/tiene/games/G_MaOS_tiene/textur/vtak.png"));
    tien = new Tiene(1);
    scene->addItem(tien);
    scene->addItem(l_animal.operator[](1));
    connect(tien,SIGNAL(pressed_On_Tiene(Tiene*)),this,SLOT(pressEnter_Tiene(Tiene *)));
    connect(l_animal.operator[](1),SIGNAL(pressed_On_Animal(Animal*)),this,SLOT(pressEnter_Animal(Animal*)));

    l_animal.push_back(new Animal(2,":/game/tiene/games/G_MaOS_tiene/textur/orol.png"));
    tien = new Tiene(2);
    scene->addItem(tien);
    scene->addItem(l_animal.operator[](2));
    connect(tien,SIGNAL(pressed_On_Tiene(Tiene*)),this,SLOT(pressEnter_Tiene(Tiene *)));
    connect(l_animal.operator[](2),SIGNAL(pressed_On_Animal(Animal*)),this,SLOT(pressEnter_Animal(Animal*)));

    l_animal.push_back(new Animal(3,":/game/tiene/games/G_MaOS_tiene/textur/ovecka.png"));
    tien = new Tiene(3);
    scene->addItem(tien);
    scene->addItem(l_animal.operator[](3));
    connect(tien,SIGNAL(pressed_On_Tiene(Tiene*)),this,SLOT(pressEnter_Tiene(Tiene *)));
    connect(l_animal.operator[](3),SIGNAL(pressed_On_Animal(Animal*)),this,SLOT(pressEnter_Animal(Animal*)));

    l_animal.push_back(new Animal(4,":/game/tiene/games/G_MaOS_tiene/textur/vevericka.png"));
    tien = new Tiene(4);
    scene->addItem(tien);
    scene->addItem(l_animal.operator[](4));
    connect(tien,SIGNAL(pressed_On_Tiene(Tiene*)),this,SLOT(pressEnter_Tiene(Tiene *)));
    connect(l_animal.operator[](4),SIGNAL(pressed_On_Animal(Animal*)),this,SLOT(pressEnter_Animal(Animal*)));

    l_animal.push_back(new Animal(5,":/game/tiene/games/G_MaOS_tiene/textur/zajacik.png"));
    tien = new Tiene(5);
    scene->addItem(tien);
    scene->addItem(l_animal.operator[](5));
    connect(tien,SIGNAL(pressed_On_Tiene(Tiene*)),this,SLOT(pressEnter_Tiene(Tiene *)));
    connect(l_animal.operator[](5),SIGNAL(pressed_On_Animal(Animal*)),this,SLOT(pressEnter_Animal(Animal*)));

    reset_BTN = new Tiene(10);
    scene->addItem(reset_BTN);
    connect(reset_BTN,SIGNAL(pressed_On_Tiene(Tiene*)),this,SLOT(pressEnter_ResetGame_Tiene(Tiene *)));

    return_BTN_Focus = false;
    chandegMode = false;
    // seting first pocus
    change_Focus(true);
}
