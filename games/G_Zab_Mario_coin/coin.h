#ifndef COIN_H
#define COIN_H
#include <QObject>
#include <QGraphicsPixmapItem>

class Coin : public QObject , public QGraphicsPixmapItem{
    Q_OBJECT
private:
    QTimer * timer;

public:
    bool smer_pohybu;

    virtual ~Coin();
    Coin(QGraphicsItem * parent=nullptr);

public slots:
    void move();
};

#endif // COIN_H
