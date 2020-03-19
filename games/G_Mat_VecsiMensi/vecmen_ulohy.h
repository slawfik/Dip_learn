#ifndef VECMEN_ULOHY_H
#define VECMEN_ULOHY_H
#include <QGraphicsView>
#include "../../src/gamesmethod.h"
#include "../utils/my_items.h"
#include <QMovie>
#include <QTimer>
#include <QStateMachine>
#include <QFinalState>

enum game_status {
    PRVA_ULOHA,
    DRUHA_ULOHA_VYBER_FARBU,
    DRUHA_ULOHA_VYBER_SIPKY,
    TRETIA_ULOHA_SELECT,
    TRETIA_ULOHA_FIND,
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
    void moveUp() override;
    void moveDown() override;
    void pressEnter() override;
    void pressKocka() override;
    void pressGulicka() override;
    void pressTrojuholnik() override;

public slots:
    void s_start_DruhaUloha();
    void s_start_TretiaUloha();
    void s_clear_answer_Uloha1();
    void s_clear_answer_Uloha2();
    void s_pressRebrik(my_Items *item);
    void s_sipkyPressed(my_Items* item);
    void s_takeColours(my_Items* item);
    void s_selectJezko(my_Items* item);
    void s_pressOnPoint_Jezko(my_Items* item);
    void s_show_GameOwer();
private:
    QGraphicsScene* scene;
    QList<my_Items*> jezko;
    QList<my_Items*>::iterator currentJezkoFocus;
    my_Items* rebrik_sipky[13];
    my_Items* colours[5];
    QGraphicsTextItem* colours_Text;
    QGraphicsEllipseItem* focus_rebrik[3];
    QGraphicsTextItem* titleText;
    QGraphicsTextItem* animationTitleText;
    QGraphicsPixmapItem* answer_pixmap;
    QGraphicsPixmapItem * kurzor;
    QGraphicsPixmapItem* napovedaParent;
    short pocet_spiopk_preMalovanie=0;
    short farba_zadanie;        //faba sipky == smeru sipky
    short colour_ID = 0;        //zvolena farba na kurzore
    short currentFocus_object = 0;
    game_status status = PRVA_ULOHA;

    //Animation
    QStateMachine* machine;
    QState* state[8];
    QTimer* timerForState_1;
    QTimer* timerForState_2;
    QTimer* timerForState_3;
    QTimer* pom_timer;
    QTimer* pom_timer2;

    void initStete_AND_animationObj();
    void init_game1();
    void init_game2();
    void init_game3();
    void init_Cursor(const QString textura,const QSize velkost);
    void initRandomMiesta(QPointF *random_miesta);
    void vymalujSipku();
    void changeFocus_Right();
    void changeFocus_Left();
};

#endif // VECMEN_ULOHY_H

