#include "my_item.h"
#include "../../settings.h"
#include "QDebug"
#include <QFocusEvent>
#include "vecie_mensie.h"

My_item::My_item(const bool left, QString pixmap_PATH,const int hodnota, QGraphicsItem *parent)
                : QGraphicsPixmapItem(parent) , hodnota(hodnota) {
    path_OFF = pixmap_PATH;
    path_ON = pixmap_PATH.split(".")[0] + "_ON.png";
    if(left) {
        setPos(WIDTH_SCREAN/3-100,HIGHT_SCREAN/2-50);
    } else {
        setPos(2*WIDTH_SCREAN/3-100,HIGHT_SCREAN/2-50);
    }
    setPixmap(QPixmap(pixmap_PATH).scaled(200,200,Qt::IgnoreAspectRatio));
}

void My_item::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    emit pressed(this);
}

void My_item::focusIn()
{
    this->setPixmap(QPixmap(path_ON).scaled(200,200,Qt::IgnoreAspectRatio));
    //qDebug() << " got" ;
}

void My_item::focusOut()
{
    //qDebug() << " lost" ;
    this->setPixmap(QPixmap(path_OFF).scaled(200,200,Qt::IgnoreAspectRatio));
}

int My_item::getHodnota() const
{
    return hodnota;
}

void My_item::setHodnota(int value)
{
    hodnota = value;
}

