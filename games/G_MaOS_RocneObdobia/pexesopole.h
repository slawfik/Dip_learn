#ifndef PEXESOPOLE_H
#define PEXESOPOLE_H
#include <QPoint>
#include <QObject>
#include <QList>
#include <QPair>
#include "../utils/my_items.h"

enum statePexeso{
    FINDING_FIRST,
    FINDING_PAIR,
    END_PEXESO_GAME
};

class pexesoPole : public QObject
{
    Q_OBJECT
public:
    short score = 0;
    pexesoPole( my_Items* parent_Item,QObject *parent = nullptr);

    void changeFocusRight();
    void changeFocusLeft();
    void changeFocusDown();
    void changeFocusUp();

    //my_Items *getParent_Item() const;

private:
    statePexeso gameStatus;
    my_Items* otocenyItem = nullptr;
    QList<my_Items*> hracieKarty;
    QList<my_Items*>::iterator currentFocus = nullptr;
    QList<my_Items*> backUp;
    QPointF points_pexeso[16];

    void setPosition();
    void changeFocus();
    void backup_ItemOn_hracieKarty(my_Items* first,my_Items* last);
    void delete_currentFocus();

public slots:
    void click_on_Card(my_Items *item);
};

#endif // PEXESOPOLE_H
