#ifndef MY_BUTTON_H
#define MY_BUTTON_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

class My_button:public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
    // constructors
    My_button(QString name, QGraphicsItem* parent=NULL);

    // public methods (events)
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
signals:
    void clicked();
private:
    QGraphicsTextItem* text;
};

#endif // MY_BUTTON_H
