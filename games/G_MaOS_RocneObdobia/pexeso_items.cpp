#include "pexeso_items.h"
#include <QPainter>

pexeso_Items::pexeso_Items(QObject *parent) : QObject(parent)
{

}

pexeso_Items::pexeso_Items(const QPixmap pa_p,QString pixmap_PATH, QSize pa_velkost, const int pa_hodnota, QObject *parent)
    : QObject(parent)  ,QGraphicsPixmapItem(pa_p.scaled(pa_velkost,Qt::IgnoreAspectRatio))
{
    //setCacheMode(DeviceCoordinateCache);
    hodnota = pa_hodnota;
    path_OFF = pixmap_PATH;
    path_ON = pixmap_PATH.split(".")[0] + "_ON.png";

    velkost = pa_velkost;
    setTransformOriginPoint(pixmap().rect().center());
}

pexeso_Items::pexeso_Items(const QPixmap pa_p, const QString pixmap_PATH_OFF, const QString pixmap_PATH_ON, const QSize pa_velkost, const int pa_hodnota, QObject *parent)
    : QObject(parent)  ,QGraphicsPixmapItem(pa_p.scaled(pa_velkost,Qt::IgnoreAspectRatio)) ,path_OFF(pixmap_PATH_OFF) ,path_ON(pixmap_PATH_ON)
{
    velkost = pa_velkost;
    hodnota = pa_hodnota;
    setTransformOriginPoint(pixmap().rect().center());
}

/*void pexeso_Items::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(QPointF(), p);
}

QRectF pexeso_Items::boundingRect() const
{
    return QRectF( QPointF(0, 0), p.size());
}*/

void pexeso_Items::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    emit pressed(this);
}

void pexeso_Items::focusIn()
{
    setPixmap(QPixmap(path_ON).scaled(velkost,Qt::IgnoreAspectRatio));
}

void pexeso_Items::focusOut()
{
    setPixmap(QPixmap(path_OFF).scaled(velkost,Qt::IgnoreAspectRatio));
}

QString pexeso_Items::getPath_OFF() const
{
    return path_OFF;
}

QString pexeso_Items::getPath_ON() const
{
    return path_ON;
}

int pexeso_Items::getHodnota() const
{
    return hodnota;
}
