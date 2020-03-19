#include "my_button.h"
#include <QGraphicsTextItem>
#include <QBrush>
#include <QMovie>
#include "../../settings.h"

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

My_button::My_button(qreal x,qreal y,qreal width,qreal height,QColor color ,QObject *parent)
{
    setParent(parent);
    // draw the rect
    setRect(x,y,width,height);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);
    setBrush(brush);
}

My_button::My_button(QString pa_text, qreal x, qreal y, qreal width, qreal height, QColor color, QObject *parent)
{
    setParent(parent);

    setRect(x,y,width,height);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);
    setBrush(brush);

    // draw the text
    text = new QGraphicsTextItem(pa_text,this);
    int xPos = static_cast<int>( rect().width()/2 - text->boundingRect().width()/2);
    int yPos = static_cast<int>( rect().height()/2 - text->boundingRect().height()/2);
    text->setPos(xPos,yPos);
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

QGraphicsRectItem *My_button::drawPanel(int x, int y, int width, int height, QColor color, double opacity)
{
    // draws a panel at the specified location with the specified properties
    QGraphicsRectItem* panel = new QGraphicsRectItem(x,y,width,height);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);
    panel->setBrush(brush);
    panel->setOpacity(opacity);
    return panel;
}

QGraphicsEllipseItem *My_button::drow_Elipse(qreal x, qreal y, qreal width, qreal height, QColor color, double opacity)
{
    QGraphicsEllipseItem* elipse = new QGraphicsEllipseItem(x,y,width,height);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);
    elipse->setBrush(brush);
    elipse->setOpacity(opacity);
    return elipse;
}

QLabel *My_button::showGif(QString pixMap,QPoint point)
{
    //movie =  new QMovie(pixMap);
    static QMovie moviee(pixMap);
    QLabel * aniLabel = new QLabel;
    aniLabel->setAttribute(Qt::WA_TranslucentBackground); //transparet background
    aniLabel->setMovie(&moviee);
    moviee.start();
    aniLabel->setGeometry(point.x(),point.y(),150,150);

    aniLabel->show();
    return aniLabel;    //scene->addWidget(aniLabel);
}

QGraphicsTextItem* My_button::showTitleText(QString data)
{
    //title text
    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString(data));
    QFont titleFont(FONT_IN_GAME,FONT_GAME_SIZE1);
    titleText->setFont(titleFont);
    titleText->setPos(WIDTH_SCREAN/2 - titleText->boundingRect().width()/2,5);
    return titleText;
}

QGraphicsTextItem *My_button::show_own_TitleText(QString data, QPoint point, int size_font,bool center_onThisPoint,qreal text_Len)
{
    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString(data));
    QFont titleFont(FONT_IN_GAME,size_font);
    titleText->setFont(titleFont);
    if(center_onThisPoint){
        titleText->setPos(point.x() - titleText->boundingRect().width()/2,point.y());
    } else {
        titleText->setTextWidth(text_Len);
        titleText->setPos(point);
    }
    return titleText;
}

QGraphicsPixmapItem *My_button::showImage(QPoint point, QString img_path,QSize velkost)
{
    QGraphicsPixmapItem* img = new QGraphicsPixmapItem();
    QPixmap pix(img_path);

    img->setPixmap(pix.scaled(velkost));
    img->setPos(point.x()-(velkost.width()/2),point.y());
    return img;
}
