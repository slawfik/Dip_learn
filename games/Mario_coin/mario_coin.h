#ifndef MARIO_COIN_H
#define MARIO_COIN_H
#include <QGraphicsView>
#include "QTimer"
#include <QList>
#include "coin.h"
#include "hrac.h"
#include "../../gamesmethod.h"

class Mario_coin : public QGraphicsView , public GamesMethod {

public:
    Mario_coin(QWidget * parent=0);

    /*Funkcie pre ovladanie*/
    void moveUp() override;
    void moveDown() override;
    void moveLeft() override;
    void moveRight() override;

    QGraphicsScene * scene;
    QTimer *respown_timer;
    int pocet_coin = 0;
    QList<Coin*> listCoin;
    Hrac* hrac;

};

extern Mario_coin *marioCoin;
#endif // MARIO_COIN_H
