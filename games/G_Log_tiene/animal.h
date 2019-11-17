#ifndef ANIMAL_H
#define ANIMAL_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class animal : public QGraphicsPixmapItem
{
public:
    animal(int num,QString pixmap_path,QGraphicsItem *parent = nullptr);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void manual_Focus_ON();
    void manual_Focus_OFF();

    short getId() const;

private:
    QPixmap textura;
    QString textur_ON;
    QString textur_OFF;
    short id;
};

#endif // ANIMAL_H
