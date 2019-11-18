#ifndef TIENE_H
#define TIENE_H
#include <QGraphicsView>
#include <QMouseEvent>
#include "animal.h"
#include "check_box.h"
#include <QList>
#include <QLabel>

class Tiene : public QGraphicsView
{
    Q_OBJECT
public:    
    QGraphicsScene * scene;
    QList <animal*> zvierata;
    check_box *answer[6] = {nullptr,nullptr,nullptr,nullptr,nullptr,nullptr};
    check_box *restart_game;
    QList<animal*>::iterator focusIT;

    bool btn_return = false;
    int changed_mode_animal = -1;
    bool changed_mode = false;

    Tiene(QWidget * parent=nullptr);
    virtual ~Tiene();
    void mouseMoveEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

    void init_kurzor(QString textur,QPointF pos);
    void delete_kurzor();
    void setObject();
    void changeFocus(bool ok_change);
    void drawPanel(int x, int y, int width, int height, QColor color, double opacity);
    void showGameOver(QString msg);
    void addGif();
    inline void gif(bool show);

public slots:
    void gameRestart();

private:
    QGraphicsPixmapItem * kurzor;
    QLabel *aniLabel;
    // need delete
    QMovie *movie;

};

extern Tiene *tien;

#endif // TIENE_H
