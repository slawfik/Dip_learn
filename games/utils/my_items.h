#ifndef MY_ITEMS_H
#define MY_ITEMS_H
#include <QGraphicsPixmapItem>
#include <QTimer>

class my_Items : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
protected:
    short press_animationStep = 0;
    short openAnimationStep = 0;

private:
    QTimer press_animationTimer;
    QTimer open_animationTimer;
    QTimer *hideTimer = nullptr;
    QTimer *focusTimer = nullptr;
    QString path_OFF;
    QString path_ON; // private
    QSize velkost;
    const QPointF poz;
    int hodnota;
    bool focusMutexLock = false;

public:
    my_Items();
    my_Items(QPointF pa_poz, QString pixmap_PATH,QSize pa_velkost,const int pa_hodnota,QGraphicsItem *parent = nullptr);
    my_Items(QPointF pa_poz, QString pixmap_OFF,QString pixmap_ON,QSize pa_velkost,const int pa_hodnota,QGraphicsItem *parent = nullptr);
    virtual ~my_Items();

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void focusIn();
    void focusOut();
    void focusOut_withTimeout(int mSec);

    int getHodnota() const;
    void setHodnota(int value);
    void setPath_ON(const QString &value);
    void setPath_OFF(const QString &value);
    void hideWIth_timeout(int mSec);

    //Animation
    void start_press_Animation();
    void start_open_Animation();

signals:
    void pressed(my_Items*);

public slots:
    void s_focus_Out();
    void s_hide_item(my_Items * item);
    void s_hide_item();
    void s_pressAnimation();
    void s_openAnimation();
};

#endif // MY_ITEMS_H
