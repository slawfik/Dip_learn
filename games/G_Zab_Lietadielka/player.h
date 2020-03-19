#ifndef PLAYER_H
#define PLAYER_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include "strela.h"

class Player: public QObject , public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Player(qreal x,qreal y,QPixmap pixmap, QGraphicsItem *parent = nullptr);
    ~Player();

    void goUp();
    void goDown();
    void goLeft();
    void goRight();
    Strela* bullet(bool left);
private:
    QTimer redy_bulletTimer;
    bool redy_bullet = true;
private slots:
    void s_setRedyBullet();

};

extern G_Status GAME_renderStatus;
#endif // PLAYER_H
