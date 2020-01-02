#ifndef VECIE_MENSIE_H
#define VECIE_MENSIE_H
#include <QGraphicsView>
#include "../../src/gamesmethod.h"
#include "my_item.h"

class Vecie_mensie : public QGraphicsView , public GamesMethod
{
    Q_OBJECT
public:
    QGraphicsScene * scene;

    Vecie_mensie(QWidget * parent=nullptr);
    virtual ~Vecie_mensie() override;
    void changeFocusItem();
    void keyPressEvent(QKeyEvent *event) override;

    /*Metody na ovkaladanie*/
    void pressTab() override;
    void pressEnter() override;

private:
    QMovie *movie = nullptr;
    int round_number = 1;
    int body = 0;
    QList<My_item *> focusedItems;
    int curent_focus;

    void drawPanel(int x, int y, int width, int height, QColor color, double opacity);
    void set_random_Round();
    void showGameOver();
    void set_Texts_for_scene();

private slots:
    void my_ItemPressSlot(My_item* obj);
    void restart_Game();
};

#endif // VECIE_MENSIE_H
