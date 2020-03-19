#ifndef UPDATE_OBJECT_H
#define UPDATE_OBJECT_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include "strela.h"

class Enemy: public QObject , public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Enemy(QString pixMapPath,QSize velkost,qreal x,qreal y,QGraphicsItem *parent = nullptr);
    ~Enemy();

    void startMovment_downUp(bool onlyDown);
    void startMovment_leftRight(bool onlyLeft);

public slots:
    void s_update_movment_down();
    void s_update_movment_up();
    void s_update_movment_left();
    void s_update_movment_right();

private:
    QPixmap *a;
    bool is_outOfScrean = false; //koli jednemu volaniu pre signal
    QTimer* updateMovment_Timer_UpDown = nullptr;
    QTimer* updateMovment_Timer_LeftRight = nullptr;
    QTimer* strelba;

signals:
    void sig_is_outOfScrean(Enemy *);
};

extern G_Status GAME_renderStatus;
#endif // UPDATE_OBJECT_H
