#ifndef BOSS_H
#define BOSS_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include "strela.h"

class Boss: public QObject , public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Boss(QPixmap* pixMap,QSize velkost,qreal x,qreal y,QGraphicsItem *parent=nullptr);
    ~Boss();

    void decrementHelth();
    void add_HealthBar();
private:
    int helth = 100;
    QGraphicsTextItem* healt;
    QTimer timerStrelby;
    QGraphicsRectItem *bar[10];

signals:
    void sig_destroy_boss();
private slots:
    void s_Strielaj();
    void s_deleteStrelu(Strela * pa);
};

#endif // BOSS_H
