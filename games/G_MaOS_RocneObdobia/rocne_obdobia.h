#ifndef ROCNE_OBDOBIA_H
#define ROCNE_OBDOBIA_H
#include <QGraphicsView>
#include "../../src/gamesmethod.h"
#include "../utils/my_items.h"
#include "pexeso_items.h"
#include <QTimer>
#include <QMovie>
#include <QWidget>
#include <QState>
#include <QStateMachine>
#include <QFinalState>

enum status_Game{
    FINDING_PEXESO_FIRST,
    FINDING_PEXESO_PAIR,
    END_PEXESO_GAME,
    START_PRIRADENIA_GAME
};

class Rocne_obdobia : public QGraphicsView , public GamesMethod
{
    Q_OBJECT
public:
    Rocne_obdobia(QWidget *parent=nullptr);
    ~Rocne_obdobia() override;

private:
    QGraphicsScene *scene;
    QGraphicsTextItem* scoreText_Item;
    QGraphicsPixmapItem* answer = nullptr;
    bool b_answer;
    QTimer* timer_answer;
    QTimer* timer;
    short score = 0;
    status_Game gameStatus;
    int randomSett[16];

    QList<pexeso_Items*>::iterator currentFocus_prirad;
    my_Items* openFirst = nullptr;
    QList<pexeso_Items*> hracieKarty;
    QList<pexeso_Items*> up_item;
    my_Items* hracieKarty_back[4][4];
    int cf_row = 0; //cf --> current focus
    int cf_coll = 0;
    QPointF points_pexeso[16];
    QPoint innitPoint[8];

    /*ANIMATION*/
    QState *par_stat1;
    QState *par_stat2;
    QState *state11;
    QState *state12;
    QState *state13;
    QState *state21;
    QState *state22;
    QState *state23;
    QState *state24;
    QFinalState *stateFinal_1;
    QStateMachine *stateMachine;
    QMovie* movie = nullptr;

    void initStates();

    void keyPressEvent(QKeyEvent *event) override;
    void moveRight() override;
    void moveLeft() override;
    void moveDown() override;
    void moveUp() override;
    void pressEnter() override;

    void setPosition();
    bool findFocus_nextRow_down();
    bool findFocus_nextCOll_up();
    void findFocus_item(my_Items *it);
    void changeFocus();
    void startFirstPart_pexeso();
    void endPexeso_startPriradenie();
    void show_Answer(bool ans);

signals:
    void nextState();
    void incorrectAnswer();

public slots:
    void s_click_on_Card(my_Items *item);
    void s_endPexeso_startPriradenie();
    void s_stopDestroy_AnimationTimer();
    void s_click_pexesoItems(pexeso_Items *item);
    void s_showIncorrectMessage();
    void s_showGameOver();
};

#endif // ROCNE_OBDOBIA_H
