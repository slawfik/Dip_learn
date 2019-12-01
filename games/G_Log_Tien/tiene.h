#ifndef TIENE_H
#define TIENE_H
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class Tiene : public QObject , public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Tiene(short pa_id,QGraphicsItem *parent = nullptr);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    short getId() const;
    void set_focusIN();
    void set_focusOUT();

signals:
    void pressed_On_Tiene(Tiene *);

private:
    short id;
    QSize size;
    QString ON_textur;
};

#endif // TIENE_H
