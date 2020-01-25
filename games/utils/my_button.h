#ifndef MY_BUTTON_H
#define MY_BUTTON_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QLabel>

class My_button:public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
    // constructors
    My_button(QString name, QGraphicsItem* parent=NULL);

    // public methods (events)
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

    static QGraphicsRectItem* drawPanel(int x, int y, int width, int height, QColor color, double opacity);
    static QLabel * showGif(QMovie *movie,QString pixMap,QPoint point);
signals:
    void clicked();
private:
    QGraphicsTextItem* text;
};

#endif // MY_BUTTON_H
