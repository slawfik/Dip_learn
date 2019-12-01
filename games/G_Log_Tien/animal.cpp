#include "animal.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include "../../settings.h"

Animal::Animal(short pa_id, QString pixmap_path, QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent), textur_OFF(pixmap_path), id(pa_id)
{
    setPos(100+(id*155),HIGHT_SCREAN -88 );
    textur_ON = textur_OFF.split(".")[0] + "_ON.png";
    QPixmap textura = QPixmap(textur_OFF).scaled(WIDTH_SCREAN/10,HIGHT_SCREAN/10,Qt::IgnoreAspectRatio);

    setPixmap(textura);
}

void Animal::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit pressed_On_Animal(this);
}

void Animal::manual_Focus_IN()
{
    setPixmap(QPixmap(textur_ON).scaled(WIDTH_SCREAN/10,HIGHT_SCREAN/10,Qt::IgnoreAspectRatio));
}

void Animal::manual_Focus_OUT()
{
    setPixmap(QPixmap(textur_OFF).scaled(WIDTH_SCREAN/10,HIGHT_SCREAN/10,Qt::IgnoreAspectRatio));
}

short Animal::getId() const
{
    return id;
}
