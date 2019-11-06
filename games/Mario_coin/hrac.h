#ifndef HRAC_H
#define HRAC_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
//#include <QGraphicsTextItem>

class Hrac : public QObject , public QGraphicsPixmapItem{
    Q_OBJECT

private:
    QTimer * checkColision_timer;
    QTimer * coinSpawnTimer;
    //QGraphicsTextItem score_text;
    int score;

public:
    virtual ~Hrac();
    Hrac(QGraphicsItem * parent=nullptr);
    void keyPressEvent(QKeyEvent * event);

public slots:
    void spawn_new();
    void check_colision();
};

#endif // HRAC_H
