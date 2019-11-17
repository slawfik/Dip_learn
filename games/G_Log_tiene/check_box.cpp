#include "check_box.h"
#include "tiene.h"
#include "../../settings.h"
#include <QDebug>

check_box::check_box(short num,QGraphicsItem *parent): QGraphicsPixmapItem(parent) ,id(num)
{
    //setFlag(QGraphicsItem::ItemIsFocusable);
    switch (id) {
        case 0:
            setPos(2*WIDTH_SCREAN/3,HIGHT_SCREAN/2-30);
            setPixmap(QPixmap(":/game/tiene/games/G_Log_tiene/textur/jezko_T.png"));
            ON_textur = ":/game/tiene/games/G_Log_tiene/textur/jezko_ON.png";
            break;
        case 1:
            setPos(80,5*HIGHT_SCREAN/7-85);
            setPixmap(QPixmap(":/game/tiene/games/G_Log_tiene/textur/vtak_T.png").scaled(120,120,Qt::IgnoreAspectRatio));
            ON_textur = ":/game/tiene/games/G_Log_tiene/textur/vtak_ON.png";
            break;
        case 2:
            setPos(2*WIDTH_SCREAN/4+50,HIGHT_SCREAN/7-20);
            setPixmap(QPixmap(":/game/tiene/games/G_Log_tiene/textur/orol_T.png").scaled(300,150,Qt::IgnoreAspectRatio));
            ON_textur = ":/game/tiene/games/G_Log_tiene/textur/orol_ON.png";
            break;
        case 3:
            setPos(2*WIDTH_SCREAN/3+120,5*HIGHT_SCREAN/7-110);
            setPixmap(QPixmap(":/game/tiene/games/G_Log_tiene/textur/ovecka_T.png").scaled(200,200,Qt::IgnoreAspectRatio));
            ON_textur = ":/game/tiene/games/G_Log_tiene/textur/ovecka_ON.png";
            break;
        case 4:
            setPos(WIDTH_SCREAN/8-120,HIGHT_SCREAN/2-30-100);
            setPixmap(QPixmap(":/game/tiene/games/G_Log_tiene/textur/vevericka_T.png").scaled(50,50,Qt::IgnoreAspectRatio));
            ON_textur = ":/game/tiene/games/G_Log_tiene/textur/vevericka_ON.png";
            break;
        case 5:
            setPos(WIDTH_SCREAN/2+10,HIGHT_SCREAN/2+20);
            setPixmap(QPixmap(":/game/tiene/games/G_Log_tiene/textur/zajacik_T.png").scaled(120,120,Qt::IgnoreAspectRatio));
            ON_textur = ":/game/tiene/games/G_Log_tiene/textur/zajacik_ON.png";
            break;
        case 10:
            setPos(WIDTH_SCREAN-100,HIGHT_SCREAN-100);
            setPixmap(QPixmap(":/game/tiene/games/G_Log_tiene/textur/rerun_G_OFF.png").scaled(100,100,Qt::IgnoreAspectRatio));
            ON_textur = ":/game/tiene/games/G_Log_tiene/textur/rerun_G__ON.png";
            break;
    }
}

void check_box::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    int pom;
    if(tien->changed_mode)  {
        if(tien->changed_mode_animal == id){
            switch (id) {
                case 0:
                    this->setPixmap(QPixmap(":/game/tiene/games/G_Log_tiene/textur/jezko.png"));
                    pom = find_ObjectIn_zvierata(id);
                    tien->scene->removeItem(tien->zvierata.operator[](pom));
                    tien->zvierata.removeAt(pom);
                    break;
                case 1:
                    this->setPixmap(QPixmap(":/game/tiene/games/G_Log_tiene/textur/vtak.png").scaled(120,120,Qt::IgnoreAspectRatio));
                    pom = find_ObjectIn_zvierata(id);
                    tien->scene->removeItem(tien->zvierata.operator[](pom));
                    tien->zvierata.removeAt(pom);
                    break;
                case 2:
                    this->setPixmap(QPixmap(":/game/tiene/games/G_Log_tiene/textur/orol.png").scaled(300,150,Qt::IgnoreAspectRatio));
                    pom = find_ObjectIn_zvierata(id);
                    tien->scene->removeItem(tien->zvierata.operator[](pom));
                    tien->zvierata.removeAt(pom);
                    break;
                case 3:
                    this->setPixmap(QPixmap(":/game/tiene/games/G_Log_tiene/textur/ovecka.png").scaled(200,200,Qt::IgnoreAspectRatio));
                    pom = find_ObjectIn_zvierata(id);
                    tien->scene->removeItem(tien->zvierata.operator[](pom));
                    tien->zvierata.removeAt(pom);
                    break;
                case 4:
                    this->setPixmap(QPixmap(":/game/tiene/games/G_Log_tiene/textur/vevericka.png").scaled(50,50,Qt::IgnoreAspectRatio));
                    pom = find_ObjectIn_zvierata(id);
                    tien->scene->removeItem(tien->zvierata.operator[](pom));
                    tien->zvierata.removeAt(pom);
                    break;
                case 5:
                    this->setPixmap(QPixmap(":/game/tiene/games/G_Log_tiene/textur/zajacik.png").scaled(120,120,Qt::IgnoreAspectRatio));
                    pom = find_ObjectIn_zvierata(id);
                    qDebug()<< "animal s id:" << QString::number(tien->zvierata.operator[](pom)->getId());
                    tien->scene->removeItem(tien->zvierata.operator[](pom));
                    tien->zvierata.removeAt(pom);
                    break;

            }
            tien->changeFocus(true);
        }
        tien->changed_mode = false;
        tien->delete_kurzor();


    } else if(id == 10){
        tien->gameRestart();
    }
}

int check_box::find_ObjectIn_zvierata(int id_animal)
{
    for(int i =0;i<tien->zvierata.size();i++)   {
        if(id_animal == tien->zvierata.operator[](i)->getId()){
            qDebug() << tien->zvierata.size() <<" delete zeros" << QString::number(i);
            return i;
        }
    }
    qDebug() << "delete zeros";
    return 0;
}

void check_box::restartGameButtonFocus(bool state)
{
    if(state){
        setPixmap(QPixmap(":/game/tiene/games/G_Log_tiene/textur/rerun_G_ON.png").scaled(100,100,Qt::IgnoreAspectRatio));
    } else {
        setPixmap(QPixmap(":/game/tiene/games/G_Log_tiene/textur/rerun_G_OFF.png").scaled(100,100,Qt::IgnoreAspectRatio));
    }
}
