#include "learn_soft.h"
#include "ui_learn_soft.h"
#include <QDebug>
#include <QResizeEvent>
#include "settings.h"
#include "gamesmethod.h"

//#include game
#include "games/Mario_coin/mario_coin.h"
#include "games/G_Log_Tien/prirad_tiene.h"
#include "games/G_Log_CoJeMensie/vecie_mensie.h"

//global variable marked extern
PriradTiene *tien = nullptr;
Vecie_mensie *vec_men = nullptr;
Mario_coin *marioCoin = nullptr;

//global variable
GamesMethod *current_runGame = nullptr;

Learn_soft::Learn_soft(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Learn_soft)
{
    ui->setupUi(this);
    set_mainPage_Style();
    newSerialThread.set_run("/dev/ttyUSB0",QSerialPort::Baud9600);

    connect(&newSerialThread, &serialThread::request, this,&Learn_soft::showRequest);
    connect(&newSerialThread, &serialThread::error, this, &Learn_soft::processError);
}

Learn_soft::~Learn_soft()
{
    if(tien){
        tien->close();
        delete tien;
  } else if(vec_men) {
        vec_men->close();
        delete vec_men;
  } else if (marioCoin) {
        marioCoin->close();
        delete marioCoin;
  }
    qDebug() << "delete ui";
    delete ui;
}

void Learn_soft::on_btn_1_clicked()
{
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
            tien = new PriradTiene(this);
            tien->show();
            current_runGame = tien;
            qDebug() << "running ";
            break;
        case MAT:
            //mat game1
            break;
        case ZAB:
            marioCoin= new Mario_coin();
            marioCoin->show();
            current_runGame = marioCoin;
            break;
    }
}

void Learn_soft::on_btn_2_clicked()
{
    switch (menu) {
        case HOME:
            ui->label_temat->setText("Vyber z nasledujúcich hier:");
            ui->btn_1->setStyleSheet(stylesheet_site2_1_TIEN);
            ui->btn_2->setStyleSheet(stylesheet_site2_2_VecMen);
            ui->btn_3->hide();
            ui->btn_4->setStyleSheet(stylesheet_btn_4_ZPET);
            menu = LOG;
            break;
        case  ANJ:
            //anj game2
            break;
        case LOG:
            vec_men = new Vecie_mensie();
            vec_men->show();
            current_runGame = vec_men;
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

void Learn_soft::showRequest(const QString &s)
{
    if(current_runGame){
        if(s == "2"){
            current_runGame->moveDown();
        } else     if(s == "8"){
            current_runGame->moveUp();
        } else     if(s == "6"){
            current_runGame->moveRight();
        } else     if(s == "4"){
            current_runGame->moveLeft();
        } else     if(s == "e"){
            current_runGame->pressEnter();
        } else     if(s == "t"){
            current_runGame->pressTab();
        }
    }
}

void Learn_soft::processError(const QString &s)
{
    qDebug() << s;
}
