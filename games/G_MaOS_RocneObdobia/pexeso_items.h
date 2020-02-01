#ifndef PEXESO_ITEMS_H
#define PEXESO_ITEMS_H
#include <QGraphicsObject>
#include <QGraphicsPixmapItem>
#include <QMouseEvent>

class pexeso_Items: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
    Q_PROPERTY(QPixmap pixmap READ pixmap WRITE setPixmap)
    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation)
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)
    Q_PROPERTY(bool visilbe READ isVisible WRITE setVisible)
    Q_PROPERTY(qreal scale READ scale WRITE setScale)

public:
    pexeso_Items(QObject *parent=nullptr);
    pexeso_Items(const QPixmap pa_p,QString pixmap_PATH,QSize pa_velkost,const int pa_hodnota,QObject *parent = nullptr);
    pexeso_Items(const QPixmap pa_p,const QString pixmap_PATH_OFF,const QString pixmap_PATH_ON,const QSize pa_velkost,const int pa_hodnota,QObject *parent = nullptr);

    void focusIn();
    void focusOut();

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    QString getPath_OFF() const;
    QString getPath_ON() const;

    int getHodnota() const;

signals:
    void pressed(pexeso_Items*);

private:
    QString path_OFF;
    QString path_ON;
    QSize velkost;
    const QPointF poz;
    int hodnota;
};

#endif // PEXESO_ITEMS_H
