#ifndef VECIE_MENSIE_H
#define VECIE_MENSIE_H
#include <QGraphicsView>
#include "../../gamesmethod.h"
#include "my_item.h"

class Vecie_mensie : public QGraphicsView , public GamesMethod
{
    Q_OBJECT
public:
    QGraphicsScene * scene;

    Vecie_mensie(QWidget * parent=nullptr);
    void changeFocusItem();
    void keyPressEvent(QKeyEvent *event) override;

    /*Metody na ovkaladanie*/
    void pressTab() override;
    void pressEnter() override;

private:
    int round_number = 1;
    QList<My_item *> focusedItems;
    int curent_focus;

    void drawPanel(int x, int y, int width, int height, QColor color, double opacity);
    void set_random_Round();

private slots:
    void my_ItemPressSlot(My_item* obj);
};

extern Vecie_mensie *vec_men;

#endif // VECIE_MENSIE_H
