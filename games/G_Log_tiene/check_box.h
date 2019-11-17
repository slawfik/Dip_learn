#ifndef CHECK_BOX_H
#define CHECK_BOX_H
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class check_box : public QGraphicsPixmapItem
{
private:
    short id;
    QString ON_textur;

public:
    check_box(short num,QGraphicsItem *parent = nullptr);
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    int find_ObjectIn_zvierata(int id_animal);
    void restartGameButtonFocus(bool state);

};

#endif // CHECK_BOX_H
