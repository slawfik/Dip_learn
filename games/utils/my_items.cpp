#include "my_items.h"
#include <QDebug>

void my_Items::setPath_OFF(const QString &value)
{
    path_OFF = value;
}

my_Items::my_Items()
{
    
}

my_Items::my_Items(QPointF pa_poz, QString pixmap_PATH,QSize pa_velkost, const int pa_hodnota, QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent) ,poz(pa_poz)
{
    hodnota = pa_hodnota;
    path_OFF = pixmap_PATH;
    path_ON = pixmap_PATH.split(".")[0] + "_ON.png";

    velkost = pa_velkost;

    setPos(pa_poz);
    setPixmap(QPixmap(path_OFF).scaled(pa_velkost,Qt::IgnoreAspectRatio));
}

my_Items::my_Items(QPointF pa_poz, QString pixmap_OFF, QString pixmap_ON, QSize pa_velkost, const int pa_hodnota, QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent), path_OFF(pixmap_OFF), path_ON(pixmap_ON) ,poz(pa_poz)
{
    hodnota = pa_hodnota;
    velkost = pa_velkost;

    setPos(pa_poz);
    setPixmap(QPixmap(path_OFF).scaled(pa_velkost,Qt::IgnoreAspectRatio));
    //setPixmap(QPixmap(path_ON).scaled(pa_velkost,Qt::IgnoreAspectRatio));
}

my_Items::~my_Items()
{
    if(hideTimer){
        delete hideTimer;
    }
    if(hideTimer){
        delete  hideTimer;
    }
}

void my_Items::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    emit pressed(this);
}

void my_Items::focusIn()
{
    setPixmap(QPixmap(path_ON).scaled(velkost,Qt::IgnoreAspectRatio));
}

void my_Items::focusOut()
{
    setPixmap(QPixmap(path_OFF).scaled(velkost,Qt::IgnoreAspectRatio));
}

void my_Items::s_hide_item(my_Items *item)
{
    if(item->isVisible())   {
        item->hide();
    }
}

void my_Items::s_hide_item()
{
    this->hide();
    disconnect(hideTimer,SIGNAL(timeout()),this,SLOT(s_hide_item()));
    delete hideTimer;
    hideTimer = nullptr;
}

void my_Items::hideWIth_timeout(int mSec)
{
    hideTimer = new QTimer();
    hideTimer->setInterval(mSec);

    connect(hideTimer,SIGNAL(timeout()),this,SLOT(s_hide_item()));
    hideTimer->start();
}

void my_Items::s_focus_Out()
{
    this->setPixmap(QPixmap(path_OFF).scaled(velkost,Qt::IgnoreAspectRatio));
    disconnect(focusTimer,SIGNAL(timeout()),this,SLOT(s_focus_Out()));
    delete hideTimer;
    hideTimer = nullptr;
}

void my_Items::focusOut_withTimeout(int mSec)
{
    focusTimer = new QTimer();
    focusTimer->setInterval(mSec);

    connect(focusTimer,SIGNAL(timeout()),this,SLOT(s_focus_Out()));
    focusTimer->start();
}

void my_Items::s_pressAnimation()
{
    if(press_animationStep) {
        press_animationStep--;
        if(press_animationStep >= 9) {
            //qDebug() << "as";
            this->setRotation(this->rotation()+2);
        } else if (press_animationStep >= 3){
            //qDebug() << "ps";
            this->setRotation(this->rotation()-2);
        } else {
            //qDebug() << "as";
            this->setRotation(this->rotation()+2);
        }
    } else {
        press_animationTimer.stop();
    }
}

void my_Items::start_press_Animation()
{
    this->setTransformOriginPoint(this->pixmap().rect().center());
    press_animationTimer.setInterval(80);
    connect(&press_animationTimer,SIGNAL(timeout()),this,SLOT(s_pressAnimation()));
    press_animationStep = 12;
    press_animationTimer.start();
}

void my_Items::s_openAnimation()
{
    if(openAnimationStep == 0){
        focusIn();
        setPos(poz);
        open_animationTimer.stop();
        disconnect(&press_animationTimer,SIGNAL(timeout()),this,SLOT(s_openAnimation()));
        qDebug() << "timer stop & disconnect";
    } else if(openAnimationStep > 0){
        int rozdiel = pixmap().width()-(pixmap().width()/openAnimationStep);
        setPixmap(pixmap().scaled(openAnimationStep*pixmap().width()/4,pixmap().height(),Qt::IgnoreAspectRatio));
        setPos(static_cast<qreal>(this->x()+rozdiel/2),this->y());
        openAnimationStep--;
        qDebug() << "openAnimationStep--; s_openAnimation";
    }
}

void my_Items::start_open_Animation()
{
    press_animationTimer.setInterval(80);
    connect(&press_animationTimer,SIGNAL(timeout()),this,SLOT(s_openAnimation()));
    press_animationTimer.start();//
    openAnimationStep = 4;
}

int my_Items::getHodnota() const
{
    return hodnota;
}

void my_Items::setHodnota(int value)
{
    hodnota = value;
}

void my_Items::setPath_ON(const QString &value)
{
    path_ON = value;
}
