#ifndef BULLET_H
#define BULLET_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>

//rendes status for game
enum G_Status{
    ENEMY_FIGHT,
    BOSS_FIGHT,
    GAME_OWER,
};
extern G_Status GAME_renderStatus;

class Strela: public QObject , public QGraphicsPixmapItem{
    Q_OBJECT
public:
    short hodnota;

    Strela(qreal x,qreal y,QPixmap pa_pix,short hodnota,QGraphicsItem *parent = nullptr);

private:
    bool is_outOfScrean = false; //koli jednemu volaniu pre signal
    QTimer moveTimer;
    QTimer check_colision_Timer;

private slots:
    void s_moveDown();
    void s_moveUp();
    void s_colidingWithEnemy();
signals:
    void sig_is_outOfScrean(Strela *,bool);
    void sig_is_outOfScrean(Strela *);
};
#endif // BULLET_H
