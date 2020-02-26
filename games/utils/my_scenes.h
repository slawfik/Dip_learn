#ifndef NAPOVEDA_H
#define NAPOVEDA_H
#include <QGraphicsPixmapItem>

class My_scenes
{
public:
    My_scenes();
    static QGraphicsPixmapItem* get_napoveda();
    static QGraphicsPixmapItem* get_infoWindow_with_Picture(QString infoString,QString pixmap_path = "_");
};

#endif // NAPOVEDA_H
