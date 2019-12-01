#include "tiene.h"
#include "../../settings.h"
#include <QDebug>
#include <QGraphicsTextItem>
#include "my_button.h"
#include <QMovie>
#include <QGraphicsProxyWidget>

Tiene::Tiene(QWidget *parent)
{
    Q_UNUSED(parent)
    //init sceny
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,WIDTH_SCREAN,HIGHT_SCREAN); // make the scene 800x600 instead of infinity by infinity (default)

    QImage aa(":/game/tiene/games/G_Log_tiene/textur/tiene_BG.png");
    scene->setBackgroundBrush(QBrush(aa.scaled(WIDTH_SCREAN,HIGHT_SCREAN,Qt::IgnoreAspectRatio)));

    setScene(scene);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(WIDTH_SCREAN,HIGHT_SCREAN);
    //setFocusPolicy(Qt::TabFocus);

    //init kurzora
    kurzor = nullptr;
    setMouseTracking(true);

    addGif();
    //init objektov zvieratiek
    setObject();
}

void Tiene::gameRestart()
{
    //Removes and deletes all items from the scene
    scene->clear();
    zvierata.clear();
    //init kurzora
    kurzor = nullptr;
    btn_return = false;

    setObject();
}

void Tiene::setObject()
{
    QList<animal*>::iterator it;
    QGraphicsTextItem* title = new QGraphicsTextItem("Priraď zvieratká k ich vlastným tieňom: ");
    title->setPos(15,0);
    QFont aa = QFont("Farm to Market Fancy");
    title->setFont(aa);
    title->setScale(4);
    scene->addItem(title);

    zvierata.push_back(new animal(0,":/game/tiene/games/G_Log_tiene/textur/jezko.png"));
    answer[0] = new check_box(0);
    connect(&answer[0],SIGNAL(presed_mouseEvent(check_box *)),this,SLOT(pressEnter_or_mouserEventHandler(check_box *)));
    scene->addItem(answer[0]);

    zvierata.push_back(new animal(1,":/game/tiene/games/G_Log_tiene/textur/vtak.png"));
    answer[1] = new check_box(1);
    scene->addItem(answer[1]);

    zvierata.push_back(new animal(2,":/game/tiene/games/G_Log_tiene/textur/orol.png"));
    answer[2] = new check_box(2);
    scene->addItem(answer[2]);

    zvierata.push_back(new animal(3,":/game/tiene/games/G_Log_tiene/textur/ovecka.png"));
    answer[3] = new check_box(3);
    scene->addItem(answer[3]);

    zvierata.push_back(new animal(4,":/game/tiene/games/G_Log_tiene/textur/vevericka.png"));
    answer[4] = new check_box(4);
    scene->addItem(answer[4]);

    zvierata.push_back(new animal(5,":/game/tiene/games/G_Log_tiene/textur/zajacik.png"));
    answer[5] = new check_box(5);
    scene->addItem(answer[5]);

    restart_game = new check_box(10);
    scene->addItem(restart_game);

    for(it = zvierata.begin();it<zvierata.end();it++)    {
        scene->addItem(*it);
    }
    focusIT = zvierata.begin();
    focusIT.operator*()->manual_Focus_ON();

    gif(false);
}

void Tiene::changeFocus(bool ok_change)
{
    if(ok_change){  //volanie funkcie po korektnom uložení obrázka
        if(zvierata.size() > 0)  {
            focusIT = zvierata.begin();
            focusIT.operator*()->manual_Focus_ON();
        } else {
            showGameOver("msg");
        }
    } else {
        if(zvierata.size() > 0)  {
            focusIT.operator*()->manual_Focus_OFF();
            if(focusIT == zvierata.end()-1)  {
                if(!btn_return) { //focus tlacidla pre zmazanie tahov
                    //focus btn_return
                    btn_return=true;
                    restart_game->restartGameButtonFocus(btn_return);
                    return;
                } else {
                    //close focus btn_return
                    btn_return = false;
                    restart_game->restartGameButtonFocus(btn_return);
                    focusIT = zvierata.begin();
                }
            } else {
                focusIT++;
            }
            focusIT.operator*()->manual_Focus_ON();
        }
    }
}

Tiene::~Tiene()
{
    //Removes and deletes all items from the scene
    scene->clear();
    zvierata.clear();
    delete movie;
    delete scene;
}

void Tiene::mouseMoveEvent(QMouseEvent *event)
{
    if (kurzor){
        kurzor->setPos(event->x()-(kurzor->pixmap().width()/2),event->y()-(kurzor->pixmap().height()/2));
    }
}

void Tiene::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Tab) {
        //qDebug() << "key tab is presed" << zvierata.size();
        changeFocus(false);
    }/* else if(event->key() == Qt::Key_Space){
        showGameOver("over");
    }*/
}

void Tiene::drawPanel(int x, int y, int width, int height, QColor color, double opacity){
    // draws a panel at the specified location with the specified properties
    QGraphicsRectItem* panel = new QGraphicsRectItem(x,y,width,height);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);
    panel->setBrush(brush);
    panel->setOpacity(opacity);
    scene->addItem(panel);
}

void Tiene::showGameOver(QString msg)
{
    Q_UNUSED(msg)
    // pop up semi transparent panel
    drawPanel(0,0,WIDTH_SCREAN,HIGHT_SCREAN,Qt::black,0.65);

    // draw panel
    drawPanel(WIDTH_SCREAN/2-200,HIGHT_SCREAN/2-200,400,400,Qt::lightGray,0.75);

    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Super na:"));
    QFont titleFont("Farm to Market Fancy",50);
    titleText->setFont(titleFont);
    titleText->setPos(WIDTH_SCREAN/2 - titleText->boundingRect().width()/2,150);
    scene->addItem(titleText);

    // parent item for Button
    QGraphicsRectItem *game_OverButtons_parent = new QGraphicsRectItem();

    My_button* playAgain = new My_button(QString("Hrať znova"),game_OverButtons_parent);
    playAgain->setPos(410,HIGHT_SCREAN/2+50);
    connect(playAgain,SIGNAL(clicked()),this,SLOT(gameRestart()));

    My_button* close = new My_button(QString("Koniec"),game_OverButtons_parent);
    close->setPos(410,HIGHT_SCREAN/2+105);
    connect(close,SIGNAL(clicked()),this,SLOT(close()));


    scene->addItem(game_OverButtons_parent);
    gif(true);
}

void Tiene::addGif()
{
    movie = new QMovie(":/game/tiene/games/G_Log_tiene/textur/hviezdicky.gif");
    aniLabel = new QLabel(this);
    aniLabel->setMovie(movie);
    aniLabel->setGeometry(WIDTH_SCREAN/2-75,HIGHT_SCREAN/2-120,150,150);
    movie->start();

    gif(false);

    scene->addWidget(aniLabel);

}

inline void Tiene::gif(bool show)
{
    if(show){
        aniLabel->show();
    } else {
        aniLabel->hide();
    }
}

int Tiene::find_ObjectIn_zvierata(int id_animal)
{
    for(int i =0;i<zvierata.size();i++)   {
        if(id_animal == zvierata.operator[](i)->getId()){
            qDebug() << zvierata.size() <<" delete item:" << QString::number(i);
            return i;
        }
    }
    qDebug() << "delete zeros";
    return 0;
}

void Tiene::pressEnter_or_mouserEventHandler(check_box *item)
{
    int pom;
    if(changed_mode)  {
        if(changed_mode_animal == item->id){
            switch (item->id) {
                case 0:
                    item->setPixmap(QPixmap(":/game/tiene/games/G_Log_tiene/textur/jezko.png"));
                    pom = find_ObjectIn_zvierata(item->id);
                    scene->removeItem(zvierata.operator[](pom));
                    zvierata.removeAt(pom);
                    break;
                case 1:
                    item->setPixmap(QPixmap(":/game/tiene/games/G_Log_tiene/textur/vtak.png").scaled(120,120,Qt::IgnoreAspectRatio));
                    pom = find_ObjectIn_zvierata(item->id);
                    scene->removeItem(zvierata.operator[](pom));
                    zvierata.removeAt(pom);
                    break;
                case 2:
                    item->setPixmap(QPixmap(":/game/tiene/games/G_Log_tiene/textur/orol.png").scaled(300,150,Qt::IgnoreAspectRatio));
                    pom = find_ObjectIn_zvierata(item->id);
                    scene->removeItem(zvierata.operator[](pom));
                    zvierata.removeAt(pom);
                    break;
                case 3:
                    item->setPixmap(QPixmap(":/game/tiene/games/G_Log_tiene/textur/ovecka.png").scaled(200,200,Qt::IgnoreAspectRatio));
                    pom = find_ObjectIn_zvierata(item->id);
                    scene->removeItem(zvierata.operator[](pom));
                    zvierata.removeAt(pom);
                    break;
                case 4:
                    item->setPixmap(QPixmap(":/game/tiene/games/G_Log_tiene/textur/vevericka.png").scaled(50,50,Qt::IgnoreAspectRatio));
                    pom = find_ObjectIn_zvierata(item->id);
                    scene->removeItem(zvierata.operator[](pom));
                    zvierata.removeAt(pom);
                    break;
                case 5:
                    item->setPixmap(QPixmap(":/game/tiene/games/G_Log_tiene/textur/zajacik.png").scaled(120,120,Qt::IgnoreAspectRatio));
                    pom = find_ObjectIn_zvierata(item->id);
                    qDebug()<< "animal s id:" << QString::number(zvierata.operator[](pom)->getId());
                    scene->removeItem(zvierata.operator[](pom));
                    zvierata.removeAt(pom);
                    break;

            }
            changeFocus(true);
        }
        changed_mode = false;
        delete_kurzor();


    } else if(item->id == 10){
        gameRestart();
    }
}

void Tiene::init_kurzor(QString textur,QPointF pos)
{
    if(kurzor) {
        scene->removeItem(kurzor);
        delete  kurzor;
    }

    kurzor = new QGraphicsPixmapItem(textur);
    QPixmap aa = kurzor->pixmap();
    kurzor->setPixmap(aa.scaled(WIDTH_SCREAN/10,HIGHT_SCREAN/10,Qt::IgnoreAspectRatio));
    kurzor->setPos(pos.x()-(kurzor->pixmap().width()/2),pos.y()-(kurzor->pixmap().height()/2));
    scene->addItem(kurzor);

}

void Tiene::delete_kurzor()
{
    scene->removeItem(kurzor);
    delete kurzor;
    kurzor = nullptr;
}

void Tiene::moveUp()
{
    if(kurzor != nullptr)
        kurzor->setPos(kurzor->x(),kurzor->y()-10);
}

void Tiene::moveDown()
{
    if(kurzor != nullptr)
        kurzor->setPos(kurzor->x(),kurzor->y()+10);
}

void Tiene::moveLeft()
{
    if(kurzor != nullptr)
        kurzor->setPos(kurzor->x()+10,kurzor->y());
}

void Tiene::moveRight()
{
    if(kurzor != nullptr)
        kurzor->setPos(kurzor->x()-10,kurzor->y());
}

void Tiene::pressEnter()
{
    if(!changed_mode)   {
        changed_mode = true;
        changed_mode_animal = focusIT.operator*()->getId();
        init_kurzor(focusIT.operator*()->textur_OFF,QPointF(0,0));
    } else {
        //QGraphicsSceneMouseEvent *event;
        //mousePressEvent(event);
        qDebug() << "vloy";
    }
}

void Tiene::pressTab()
{
    if(kurzor == nullptr)
        changeFocus(false);
}
