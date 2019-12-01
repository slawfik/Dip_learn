#include "animal.h"
#include "../../settings.h"
#include "tiene.h"
#include "QDebug"

animal::animal(int num,QString pixmap_path,QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{
    short x_pos = 100;
    if(num == 0){
        setPos(x_pos,HIGHT_SCREAN -88 );
    }
    setPos(x_pos+(num*150),HIGHT_SCREAN -88 );

    id = static_cast<short>(num);
    textur_OFF = pixmap_path;
    textur_ON = textur_OFF.split(".")[0] + "_ON.png";
    textura = QPixmap(pixmap_path).scaled(WIDTH_SCREAN/10,HIGHT_SCREAN/10,Qt::IgnoreAspectRatio);

    setPixmap(textura);


}
void animal::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(!tien->changed_mode){
        qDebug() << "pressd";
        tien->changed_mode = true;
        tien->changed_mode_animal = this->id;
        tien->init_kurzor(textur_OFF,event->pos());
    }
}

void animal::manual_Focus_OFF()
{
    setPixmap(textura);
}

short animal::getId() const
{
    return id;
}
void animal::manual_Focus_ON()
{
    setPixmap(QPixmap(textur_ON).scaled(WIDTH_SCREAN/10,HIGHT_SCREAN/10,Qt::IgnoreAspectRatio));
}
