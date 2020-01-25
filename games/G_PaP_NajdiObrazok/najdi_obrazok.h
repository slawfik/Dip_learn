#ifndef NAJDI_OBRAZOK_H
#define NAJDI_OBRAZOK_H
#include <QGraphicsView>
#include "../../src/gamesmethod.h"
#include "../utils/my_items.h"
#include <QTimer>
#include <QMovie>

class Najdi_obrazok : public QGraphicsView , public GamesMethod
{
    Q_OBJECT
public:
    Najdi_obrazok(QWidget *parent=nullptr);
    virtual ~Najdi_obrazok() override;

    /*Metody na ovkaladanie*/
    void moveLeft() override;
    void moveRight() override;
    void pressEnter() override;

private:
    QGraphicsScene *scene;
    //my_Items *item;
    QGraphicsTextItem* time_text;
    QMovie* movie = nullptr;
    QTimer *timer = nullptr;
    QList<my_Items*> l_myItems;
    QList<my_Items*>::iterator l_myItems_iter;
    short waitTime;

    void showMenu();
    void showGameOver(bool win,QString data);

public slots:
    void startGame_auto(my_Items* pa_item);
    void startGame_huby(my_Items* pa_item);
    void choice_auto();
    void choice_huby();
    void restartGame();
    void choiced_my_Item_Slot(my_Items *obj);
};

#endif // NAJDI_OBRAZOK_H
