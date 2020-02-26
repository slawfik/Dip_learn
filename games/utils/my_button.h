#ifndef MY_BUTTON_H
#define MY_BUTTON_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QLabel>

class My_button:public QObject, public QGraphicsRectItem{
    Q_OBJECT
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)
public:
    //Create Buttons QObject
    My_button(QString name, QGraphicsItem* parent=nullptr);
    //Create panel QObject
    My_button(qreal x,qreal y,qreal width,qreal height,QColor color,QObject *parent=nullptr);
    //Create Button with own collor
    My_button(QString pa_text,qreal x,qreal y,qreal width,qreal height,QColor color,QObject *parent=nullptr);

    // public methods (events)
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

    static QGraphicsRectItem* drawPanel(int x, int y, int width, int height, QColor color, double opacity);
    static QGraphicsEllipseItem* drowElipse(qreal x, qreal y, qreal width, qreal height,QColor color, double opacity);
    static QLabel * showGif(QMovie *movie,QString pixMap,QPoint point);
    static QGraphicsTextItem* showTitleText(QString data);
    static QGraphicsTextItem* show_own_TitleText(QString data,QPoint point,int size_font,bool center_onThisPoint,qreal text_Len=700);
    static QGraphicsPixmapItem* showImage(QPoint point,QString img_path,QSize velkost);
signals:
    void clicked();
private:
    QGraphicsTextItem* text;
};
#endif // MY_BUTTON_H
