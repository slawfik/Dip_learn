#ifndef VECMEN_ULOHY_H
#define VECMEN_ULOHY_H
#include <QGraphicsView>
#include "../../src/gamesmethod.h"
#include "../utils/my_items.h"
#include <QTimer>
#include <QStateMachine>
#include <QFinalState>

enum game_status {
    PRVA_ULOHA,
    DRUHA_ULOHA_VYBER_FARBU,
    DRUHA_ULOHA_VYBER_SIPKY,
    TRETIA_ULOHA,
    WAIT
};

class VecMen_ulohy : public QGraphicsView , public GamesMethod
{
    Q_OBJECT
public:
    VecMen_ulohy(QWidget *parent=nullptr);
    ~VecMen_ulohy() override;

    void keyPressEvent(QKeyEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void moveLeft() override;
    void moveRight() override;
    void pressEnter() override;
    void pressKocka() override;
    void pressGulicka() override;
    void pressTrojuholnik() override;

public slots:
    void s_start_DruhaUloha();
    void s_clear_answer_Uloha1();
    void s_clear_answer_Uloha2();
    void s_sipkyPressed(my_Items* item);
    void s_takeColours(my_Items* item);
private:
    QGraphicsScene* scene;
    my_Items* rebrik_sipky[13];
    my_Items* colours[4];
    QGraphicsTextItem* colours_Text;
    QGraphicsEllipseItem* focus_rebrik[3];
    QGraphicsTextItem* titleText;
    QGraphicsTextItem* animationTitleText;
    QGraphicsPixmapItem* answer_pixmap;
    QGraphicsPixmapItem * kurzor;
    short farba_zadanie;        //faba sipky == smeru sipky
    short colour_ID = 0;        //zvolena farba
    short currentFocus_rebrik = 0;
    game_status status = PRVA_ULOHA;

    //Animation
    QStateMachine* machine;
    QState* state[8];
    QFinalState* finalState;
    QTimer* timerForState_1;
    QTimer* timerForState_2;
    QTimer* timerForState_3;
    QTimer* pom_timer;

    void initStete_AND_animationObj();
    void init_game1();
    void init_game2();
    void init_Cursor(const QString textura);
    void initRandomMiesta(QPointF *random_miesta);
    void vymalujSipku();
    void changeFocus_Right();
    void changeFocus_Left();
};

#endif // VECMEN_ULOHY_H

