#include "tiene.h"
#include "../../settings.h"

Tiene::Tiene(short pa_id, QGraphicsItem *parent) : QGraphicsPixmapItem(parent) , id(pa_id)
{
    switch (id) {
            case 0:
                setPos(2*WIDTH_SCREAN/3,HIGHT_SCREAN/2-30);
                setPixmap(QPixmap(":/game/tiene/games/G_Log_tiene/textur/jezko_T.png"));
                size = pixmap().size();
                ON_textur = ":/game/tiene/games/G_Log_tiene/textur/jezko.png";
                break;
            case 1:
                setPos(80,5*HIGHT_SCREAN/7-85);
                setPixmap(QPixmap(":/game/tiene/games/G_Log_tiene/textur/vtak_T.png").scaled(120,120,Qt::IgnoreAspectRatio));
                size = pixmap().size();
                ON_textur = ":/game/tiene/games/G_Log_tiene/textur/vtak.png";
                break;
            case 2:
                setPos(2*WIDTH_SCREAN/4+50,HIGHT_SCREAN/7-20);
                setPixmap(QPixmap(":/game/tiene/games/G_Log_tiene/textur/orol_T.png").scaled(300,150,Qt::IgnoreAspectRatio));
                size = pixmap().size();
                ON_textur = ":/game/tiene/games/G_Log_tiene/textur/orol.png";
                break;
            case 3:
                setPos(2*WIDTH_SCREAN/3+120,5*HIGHT_SCREAN/7-110);
                setPixmap(QPixmap(":/game/tiene/games/G_Log_tiene/textur/ovecka_T.png").scaled(200,200,Qt::IgnoreAspectRatio));
                size = pixmap().size();
                ON_textur = ":/game/tiene/games/G_Log_tiene/textur/ovecka.png";
                break;
            case 4:
                setPos(WIDTH_SCREAN/8-120,HIGHT_SCREAN/2-30-100);
                setPixmap(QPixmap(":/game/tiene/games/G_Log_tiene/textur/vevericka_T.png").scaled(50,50,Qt::IgnoreAspectRatio));
                size = pixmap().size();
                ON_textur = ":/game/tiene/games/G_Log_tiene/textur/vevericka.png";
                break;
            case 5:
                setPos(WIDTH_SCREAN/2+10,HIGHT_SCREAN/2+20);
                setPixmap(QPixmap(":/game/tiene/games/G_Log_tiene/textur/zajacik_T.png").scaled(120,120,Qt::IgnoreAspectRatio));
                size = pixmap().size();
                ON_textur = ":/game/tiene/games/G_Log_tiene/textur/zajacik.png";
                break;
            case 10:
                setPos(WIDTH_SCREAN-100,HIGHT_SCREAN-100);
                setPixmap(QPixmap(":/game/tiene/games/G_Log_tiene/textur/rerun_G_OFF.png").scaled(100,100,Qt::IgnoreAspectRatio));
                size = pixmap().size();
                ON_textur = ":/game/tiene/games/G_Log_tiene/textur/rerun_G_ON.png";
                break;
    }
}

void Tiene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit pressed_On_Tiene(this);
}

short Tiene::getId() const
{
    return id;
}

void Tiene::set_focusIN()
{
    setPixmap(QPixmap(ON_textur).scaled(size,Qt::IgnoreAspectRatio));
}

void Tiene::set_focusOUT()
{
    setPixmap(QPixmap(":/game/tiene/games/G_Log_tiene/textur/rerun_G_OFF.png").scaled(size,Qt::IgnoreAspectRatio));
}
