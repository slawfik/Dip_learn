#ifndef PRIRADTIENE_H
#define PRIRADTIENE_H

#include <QGraphicsView>
#include "../../src/gamesmethod.h"
#include "../../settings.h"
#include "animal.h"
#include "tiene.h"

class PriradTiene : public QGraphicsView , public GamesMethod
{
    Q_OBJECT
public:
    QGraphicsPixmapItem * kurzor;
    QGraphicsScene *scene;
    Tiene *reset_BTN;
    QList <Animal*> l_animal;
    QList <Animal*>::iterator focus_iterator;

    bool return_BTN_Focus = false;
    bool chandegMode = false;
    int chanded_mode_animal;

    PriradTiene(QWidget *parent);
    virtual ~PriradTiene();
    void mouseMoveEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

    /*Function pre ovladac*/
    void moveUp() override;
    void moveDown() override;
    void moveLeft() override;
    void moveRight() override;
    void pressTab() override;
    void pressEnter() override;

public slots:
    void pressEnter_Animal(Animal *a);
    void pressEnter_Tiene(Tiene *t);
    void pressEnter_ResetGame_Tiene(Tiene *t);

private:
    void setNewGame();
    void init_Kurzor(const QString textura);
    void delete_Kurzor();
    void change_Focus(bool odznova);
};
#endif // PRIRADTIENE_H
