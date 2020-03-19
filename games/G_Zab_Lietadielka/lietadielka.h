#ifndef LIETADIELKA_H
#define LIETADIELKA_H
#include <QGraphicsView>
#include "../../src/gamesmethod.h"
#include <QGraphicsItemAnimation>
#include <QGraphicsTextItem>
#include <QMovie>
#include "player.h"
#include "enemy.h"
#include "strela.h"
#include "boss.h"
#include <QTimeLine>
#include <QSet>

extern G_Status GAME_renderStatus;
class Lietadielka: public QGraphicsView , public GamesMethod
{
    Q_OBJECT
public:
    Lietadielka(QWidget *parent=nullptr);
    ~Lietadielka() override;

    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private:
    bool is_shootRedy = true;
    //move
    QTimer keyTimerEvent;
    QMap<int, bool> keys;

    QGraphicsScene* scene;
    QGraphicsTextItem* skore;
    QTimer* spawnEnemy_timer;
    QTimer* colisions_timer;
    QTimer pom_timer;
    QTimer *timer_ShootTimout = nullptr;

    QTimeLine *timer = nullptr;
    QGraphicsItemAnimation *animation = nullptr;
    int score = 0;

    Player* player;
    Boss* boss = nullptr;

    void init_Game();
    void player_shot();
    void spawn_boss();

private slots:
    void s_deleteEnemy(Enemy* en);
    void s_deleteBullet(Strela* bull,bool incScore);
    void s_deleteBoss();
    void s_spawnEnemy();
    void s_check_Collision_forPlayer();
    void s_showGameOwer();
    void s_processAllKeys();
    void s_resetPlayerShoot();
};

#endif // LIETADIELKA_H
