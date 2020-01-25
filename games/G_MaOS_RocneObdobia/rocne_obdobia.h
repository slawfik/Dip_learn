#ifndef ROCNE_OBDOBIA_H
#define ROCNE_OBDOBIA_H
#include <QGraphicsView>
#include "../../src/gamesmethod.h"
#include "pexesopole.h"
#include "../utils/my_items.h"
#include <QTimer>
#include <QMovie>

class Rocne_obdobia : public QGraphicsView , public GamesMethod
{
    Q_OBJECT
public:
    Rocne_obdobia(QWidget *parent=nullptr);

private:
    pexesoPole *pexeso_Pole;
    QGraphicsScene *scene;
    QGraphicsTextItem* scoreText_Item;
    short score = 0;
    statePexeso gameStatus;
    my_Items* otocenyItem = nullptr;
    QList<my_Items*> hracieKarty;
    QList<my_Items*>::iterator currentFocus = nullptr;
    QList<my_Items*> backUp;
    QPointF points_pexeso[16];

    void startFirstPart_pexeso();

    void keyPressEvent(QKeyEvent *event) override;
    void changeFocusRight();
    void changeFocusLeft();
    void changeFocusDown();
    void changeFocusUp();

    void setPosition();
    void changeFocus();
    void backup_ItemOn_hracieKarty(my_Items* first,my_Items* last);
    void delete_currentFocus();

public slots:
    void click_on_Card(my_Items *item);
};

#endif // ROCNE_OBDOBIA_H
