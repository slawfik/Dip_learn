#ifndef MARIO_COIN_H
#define MARIO_COIN_H
#include <QGraphicsView>
#include "QTimer"
#include <QList>
#include "coin.h"

class Mario_coin : public QGraphicsView {

public:
    Mario_coin(QWidget * parent=0);

    QGraphicsScene * scene;
    QTimer *respown_timer;
    int pocet_coin = 0;
    QList<Coin*> listCoin;

};

#endif // MARIO_COIN_H
