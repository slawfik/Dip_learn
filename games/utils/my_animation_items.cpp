#include "my_animation_items.h"

My_animation_items::My_animation_items(QObject *parent)
{
    Q_UNUSED(parent)
}

My_animation_items::My_animation_items(QString path_pixmap,QPointF poz,QSize size)
    : path_OFF(path_pixmap) , velkost(size)
{
    setPixmap(QPixmap(path_OFF).scaled(velkost));
    setPos(poz);
}

void My_animation_items::focusIn()
{
    setPixmap(QPixmap(path_ON).scaled(velkost,Qt::IgnoreAspectRatio));
}

void My_animation_items::focusOut()
{
    setPixmap(QPixmap(path_OFF).scaled(velkost,Qt::IgnoreAspectRatio));

}

void My_animation_items::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    emit pressed(this);
}

QString My_animation_items::getPath_OFF() const
{
    return path_OFF;
}

void My_animation_items::setPath_OFF(const QString &value)
{
    path_OFF = value;
}

QString My_animation_items::getPath_ON() const
{
    return path_ON;
}

void My_animation_items::setPath_ON(const QString &value)
{
    path_ON = value;
}
