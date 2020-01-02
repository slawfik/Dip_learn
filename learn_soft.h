#ifndef LEARN_SOFT_H
#define LEARN_SOFT_H

#include <QGraphicsPixmapItem>
#include <QMainWindow>
#include "src/serial_thread.h"
#include "src/dialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Learn_soft; }
QT_END_NAMESPACE

typedef enum site{
    HOME = 0,
    MaOS_1 = 1,
    PaP_2 = 2,
    MAT_3 = 3,
    ZAB_4 = 4
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
    void showRequest(const QString &s);
    void processError(const QString &s);

    void on_btn_settings_clicked();

private:
    Dialog serialInfoDialog;
    serialThread newSerialThread;
    MENU menu = HOME;
    QPalette palet;
    QPixmap * pixMap;
    Ui::Learn_soft *ui;
    void set_mainPage_Style();
};
#endif // LEARN_SOFT_H
