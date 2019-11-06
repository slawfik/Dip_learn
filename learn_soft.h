#ifndef LEARN_SOFT_H
#define LEARN_SOFT_H

#include <QGraphicsPixmapItem>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Learn_soft; }
QT_END_NAMESPACE

class Learn_soft : public QMainWindow
{
    Q_OBJECT

protected:
    void resizeEvent(QResizeEvent *event) override;

public:
    Learn_soft(QWidget *parent = nullptr);
    ~Learn_soft() override;

private:
    QPalette palet;
    QPixmap * pixMap;
    Ui::Learn_soft *ui;
};
#endif // LEARN_SOFT_H
