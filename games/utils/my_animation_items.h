#ifndef MY_ANIMATION_ITEMS_H
#define MY_ANIMATION_ITEMS_H
#include <QGraphicsObject>
#include <QGraphicsPixmapItem>
#include <QMouseEvent>

class My_animation_items : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
    /*Q_PROPERTY(QPixmap pixmap READ pixmap WRITE setPixmap)
    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation)*/
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)
    Q_PROPERTY(bool visilbe READ isVisible WRITE setVisible)
    Q_PROPERTY(qreal scale READ scale WRITE setScale)
public:
    My_animation_items(QObject *parent=nullptr);
    My_animation_items(QString path_pixmap,QPointF poz,QSize size);

    void focusIn();
    void focusOut();

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    QString getPath_OFF() const;
    void setPath_OFF(const QString &value);

    QString getPath_ON() const;
    void setPath_ON(const QString &value);

signals:
    void pressed(My_animation_items*);

private:
    QString path_OFF;
    QString path_ON;
    QSize velkost;
    const QPointF poz;
    int hodnota;
};

#endif // MY_ANIMATION_ITEMS_H
