#ifndef ANIMAL_H
#define ANIMAL_H
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class Animal :  public QObject , public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    QString textur_OFF;

    Animal(short pa_id,QString pixmap_path,QGraphicsItem *parent = nullptr);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    void manual_Focus_IN();
    void manual_Focus_OUT();

    short getId() const;


signals:
    void pressed_On_Animal(Animal*);

private:
    QString textur_ON;
    short id;
};

#endif // ANIMAL_H
