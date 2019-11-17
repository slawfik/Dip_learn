#include "learn_soft.h"
#include "ui_learn_soft.h"
#include <QDebug>
#include <QResizeEvent>
#include "settings.h"

//#include game
#include "games/Mario_coin/mario_coin.h"
#include "games/G_Log_tiene/tiene.h"

//global variable
Tiene *tien;

Learn_soft::Learn_soft(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Learn_soft)
{
    //ui->btn_1->setFocus();
    ui->setupUi(this);

    set_mainPage_Style();

}

Learn_soft::~Learn_soft()
{
    delete ui;
}

void Learn_soft::on_btn_1_clicked()
{
    Mario_coin *game;
    switch (menu) {
        case HOME:
            ui->label_temat->setText("Vyber z nasledujúcich hier:");
            ui->btn_1->hide();
            ui->btn_2->hide();
            ui->btn_3->hide();
            ui->btn_4->setStyleSheet(stylesheet_btn_4_ZPET);
            menu = ANJ;
            break;
        case ANJ:
            //anj game1
            break;
        case LOG:
            tien = new Tiene();
            tien->show();
            break;
        case MAT:
            //mat game1
            break;
        case ZAB:
            game= new Mario_coin();
            game->show();
            break;
    }
}

void Learn_soft::on_btn_2_clicked()
{
    switch (menu) {
        case HOME:
            ui->label_temat->setText("Vyber z nasledujúcich hier:");
            ui->btn_1->setStyleSheet(stylesheet_site2_1_COIN);
            ui->btn_2->hide();
            ui->btn_3->hide();
            ui->btn_4->setStyleSheet(stylesheet_btn_4_ZPET);
            menu = LOG;
            break;
        case  ANJ:
            //anj game2
            break;
        case LOG:
            //log game2
            break;
        case MAT:
            //mat game2
            break;
        case ZAB:
            //zab game2
            break;
    }
}

void Learn_soft::on_btn_3_clicked()
{
    switch (menu) {
        case HOME:
            ui->label_temat->setText("Vyber z nasledujúcich hier:");
            ui->btn_1->hide();
            ui->btn_2->hide();
            ui->btn_3->hide();
            ui->btn_4->setStyleSheet(stylesheet_btn_4_ZPET);
            menu = MAT;
            break;
        case  ANJ:
            //anj game3
            break;
        case LOG:
            //log game3
            break;
        case MAT:
            //mat game3
            break;
        case ZAB:
            //zab game3
            break;
    }
}

void Learn_soft::on_btn_4_clicked()
{
    switch (menu) {
        case HOME:
            ui->label_temat->setText("Vyber z nasledujúcich hier:");
            ui->btn_1->setStyleSheet(stylesheet_site4_1_COIN);
            ui->btn_2->hide();
            ui->btn_3->hide();
            ui->btn_4->setStyleSheet(stylesheet_btn_4_ZPET);
            menu = ZAB;
            break;
        case  ANJ:
            set_mainPage_Style();
            break;
        case LOG:
            set_mainPage_Style();
            break;
        case MAT:
            set_mainPage_Style();
            break;
        case ZAB:
            set_mainPage_Style();
            break;
    }
}

void Learn_soft::set_mainPage_Style()
{
    ui->label_temat->setText("Výber tematického okruhu:");

    ui->btn_1->show();
    ui->btn_1->setStyleSheet(stylesheet_site1_1);
    ui->btn_2->show();
    ui->btn_2->setStyleSheet(sylesheet_site1_2);
    ui->btn_3->show();
    ui->btn_3->setStyleSheet(stylesheet_site1_3);
    ui->btn_4->show();
    ui->btn_4->setStyleSheet(stylesheet_site1_4);

    ui->btn_1->setFocus();
    menu = HOME;
}
