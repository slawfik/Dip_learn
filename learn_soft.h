#ifndef LEARN_SOFT_H
#define LEARN_SOFT_H

#include <QGraphicsPixmapItem>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Learn_soft; }
QT_END_NAMESPACE

typedef enum site{
    HOME = 0,
    ANJ = 1,
    LOG = 2,
    MAT = 3,
    ZAB = 4
}MENU;

class Learn_soft : public QMainWindow
{
    Q_OBJECT

protected:
    //void resizeEvent(QResizeEvent *event) override;

public:
    Learn_soft(QWidget *parent = nullptr);
    ~Learn_soft() override;

private slots:
    void on_btn_1_clicked();

    void on_btn_2_clicked();

    void on_btn_3_clicked();

    void on_btn_4_clicked();

private:
    MENU menu = HOME;
    QPalette palet;
    QPixmap * pixMap;
    Ui::Learn_soft *ui;
    void set_mainPage_Style();
};
#endif // LEARN_SOFT_H
