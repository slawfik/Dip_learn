#include "learn_soft.h"
#include "ui_learn_soft.h"
#include <QDebug>
#include <QResizeEvent>
#include "settings.h"
#include "src/gamesmethod.h"
#include "src/dialog.h"

//#include game
#include "games/G_Zab_Mario_coin/mario_coin.h"
#include "games/G_MaOS_tiene/prirad_tiene.h"
#include "games/G_PaP_CoJeMensie/vecie_mensie.h"
#include "games/G_PaP_NajdiObrazok/najdi_obrazok.h"
#include "games/G_MaOS_RocneObdobia/rocne_obdobia.h"
#include "games/G_Mat_VecsiMensi/vecmen_ulohy.h"

//global variable marked extern
PriradTiene *tien = nullptr;
Vecie_mensie *vec_men = nullptr;
Mario_coin *marioCoin = nullptr;
Najdi_obrazok *najdiObr = nullptr;
Rocne_obdobia *rocObdob = nullptr;
VecMen_ulohy *vec_menUlohy = nullptr;

//global variable
GamesMethod *current_runGame = nullptr;

Learn_soft::Learn_soft(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Learn_soft)
{
    ui->setupUi(this);
    set_mainPage_Style();
    /*newSerialThread.set_run("/dev/ttyUSB1",QSerialPort::Baud9600);

    connect(&newSerialThread, &serialThread::request, this,&Learn_soft::showRequest);
    connect(&newSerialThread, &serialThread::error, this, &Learn_soft::processError);*/
}

Learn_soft::~Learn_soft()
{
    if(tien){
        tien->close();
        delete tien;
    }
    if(vec_men) {
        vec_men->close();
        delete vec_men;
    }
    if (marioCoin) {
        marioCoin->close();
        delete marioCoin;
    }
    if (rocObdob) {
      rocObdob->close();
      delete rocObdob;
    }
    if (vec_menUlohy){
        vec_menUlohy->close();
        delete vec_menUlohy;
    }
    qDebug() << "delete ui";
    delete ui;
}

void Learn_soft::on_btn_1_clicked()
{
    switch (menu) {
        case HOME:
            ui->label_temat->setText("Vyber z nasledujúcich hier:");
            ui->btn_1->setStyleSheet(stylesheet_site1_1_TIEN);
            ui->btn_2->setStyleSheet(stylesheet_site1_2_RocObd);
            ui->btn_3->hide();
            ui->btn_4->setStyleSheet(stylesheet_btn_4_ZPET);
            ui->btn_settings->hide();
            menu = MaOS_1;
            break;
        case MaOS_1:
            tien = new PriradTiene(this);
            tien->show();
            current_runGame = tien;
            qDebug() << "running ";
            break;
        case PaP_2:
            vec_men = new Vecie_mensie();
            vec_men->show();
            current_runGame = vec_men;
            break;
        case MAT_3:
            vec_menUlohy = new VecMen_ulohy();
            vec_menUlohy->show();
            current_runGame = vec_menUlohy;
            break;
        case ZAB_4:
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
            ui->btn_1->setStyleSheet(stylesheet_site2_1_CoJeMen);
            ui->btn_2->setStyleSheet(stylesheet_site2_2_NajdiObr);
            ui->btn_3->hide();
            ui->btn_4->setStyleSheet(stylesheet_btn_4_ZPET);
            ui->btn_settings->hide();
            menu = PaP_2;
            break;
        case  MaOS_1:
            rocObdob = new Rocne_obdobia();
            rocObdob->show();
            current_runGame = rocObdob;
            break;
        case PaP_2:
            najdiObr = new Najdi_obrazok();
            najdiObr->show();
            current_runGame = najdiObr;
            break;
        case MAT_3:
            //mat game2
            break;
        case ZAB_4:
            //zab game2
            break;
    }
}

void Learn_soft::on_btn_3_clicked()
{
    switch (menu) {
        case HOME:
            ui->label_temat->setText("Vyber z nasledujúcich hier:");
            ui->btn_1->setStyleSheet(stylesheet_site3_1_VecMen_ulohy);//tu_
            ui->btn_2->hide();
            ui->btn_3->hide();
            ui->btn_4->setStyleSheet(stylesheet_btn_4_ZPET);
            ui->btn_settings->hide();
            menu = MAT_3;
            break;
        case  MaOS_1:
            //anj game3
            break;
        case PaP_2:
            //PaP_2 game3
            break;
        case MAT_3:
            //mat game3
            break;
        case ZAB_4:
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
            ui->btn_settings->hide();
            menu = ZAB_4;
            break;
        case  MaOS_1:
            set_mainPage_Style();
            break;
        case PaP_2:
            set_mainPage_Style();
            break;
        case MAT_3:
            set_mainPage_Style();
            break;
        case ZAB_4:
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

    ui->btn_settings->show();
    ui->btn_settings->setStyleSheet(stylesheet_site1_sett);

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

/*serial slot error handle*/
void Learn_soft::processError(const QString &s)
{
    qDebug() << s;
}

void Learn_soft::on_btn_settings_clicked()
{
    if(serialInfoDialog.exec()){
        newSerialThread.set_run(serialInfoDialog.getSerialPort(),QSerialPort::Baud9600);
        connect(&newSerialThread, &serialThread::request, this,&Learn_soft::showRequest);
        connect(&newSerialThread, &serialThread::error, this, &Learn_soft::processError);
    }
}
