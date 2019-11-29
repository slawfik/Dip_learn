#ifndef MY_TIEM_H
#define MY_TIEM_H
#include <QGraphicsPixmapItem>

class My_item : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
private:

    QString path_OFF;
public:
    QString path_ON; // private
    int hodnota;

    My_item(const bool left,QString pixmap_PATH,const int hodnota,QGraphicsItem *parent = nullptr);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void focusIn();
    void focusOut();

    int getHodnota() const;
    void setHodnota(int value);

signals:
    void pressed(My_item*);
};

#endif // MY_TIEM_H
