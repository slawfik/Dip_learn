#include "my_button.h"
#include <QGraphicsTextItem>
#include <QBrush>
//#include "tiene.h"


My_button::My_button(QString name, QGraphicsItem *parent): QGraphicsRectItem(parent){
    // draw the rect
    setRect(0,0,380,50);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkCyan);
    setBrush(brush);

    // draw the text
    text = new QGraphicsTextItem(name,this);
    int xPos = static_cast<int>( rect().width()/2 - text->boundingRect().width()/2);
    int yPos = static_cast<int>( rect().height()/2 - text->boundingRect().height()/2);
    text->setPos(xPos,yPos);

    // allow responding to hover events
    setAcceptHoverEvents(true);
}

void My_button::mousePressEvent(QGraphicsSceneMouseEvent *event){
    Q_UNUSED(event)
    emit clicked();

}

void My_button::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    Q_UNUSED(event)
    // change color to cyan
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::cyan);
    setBrush(brush);
    //tien->gameRestart();
}

void My_button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    Q_UNUSED(event)
    // change color to dark cyan
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkCyan);
    setBrush(brush);
}
