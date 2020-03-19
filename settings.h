#ifndef SETTINGS_H
#define SETTINGS_H
#include <QString>
#include <QGraphicsScene>

//convert 1.png -strip 1.png
//start debug uncomment
#define DEF_DEBUG

//nemozno menej ako 1100
#define WIDTH_SCREAN 1200   //1200 700
//nemozno menej ako 700
#define HIGHT_SCREAN 700
#define MOVE_STEP 20
#define SPEED 3
#define FONT_IN_GAME "Farm to Market Fancy"
#define FONT_GAME_SIZE1 50
#define FONT_GAME_SIZE2 30

#define x_ODSADENIE_PLATNA 150
#define y_ODSADENIE_PLATNA 70



//####STYLESHEETS#####

static QString stylesheet_g1 = "";
static QString stylesheet_site1_1_TIEN = "#btn_1"
                                         "{ border-image: url(:/img/images/MaOS_priradTiene_OFF.png);"
                                         "border-radius: 15px;}"
                                         "#btn_1:pressed"
                                         "{   border-image: url(:/img/images/MaOS_priradTiene_ON.png); }"
                                         "#btn_1:focus "
                                         "{   border-image: url(:/img/images/MaOS_priradTiene_ON.png); }";
static QString stylesheet_site1_2_RocObd = "#btn_2"
                                         "{ border-image: url(:/img/images/MaOS_rocneObdob_OFF.png);"
                                         "border-radius: 15px;}"
                                         "#btn_1:pressed"
                                         "{   border-image: url(:/img/images/MaOS_rocneObdob_ON.png); }"
                                         "#btn_1:focus "
                                         "{   border-image: url(:/img/images/MaOS_rocneObdob_ON.png); }";
static QString stylesheet_site2_1_CoJeMen = "#btn_1"
                                         "{ border-image: url(:/img/images/PaP_coJeMensie_OFF.png);"
                                         "border-radius: 15px;}"
                                         "#btn_1:pressed"
                                         "{   border-image: url(:/img/images/PaP_coJeMensie_ON.pngg); }"
                                         "#btn_1:focus "
                                         "{   border-image: url(:/img/images/PaP_coJeMensie_ON.png); }";
static QString stylesheet_site2_2_NajdiObr = "#btn_2"
                                         "{ border-image: url(:/img/images/PaP_najdiObrazok_OFF.png);"
                                         "border-radius: 15px;}"
                                         "#btn_2:pressed"
                                         "{   border-image: url(:/img/images/PaP_najdiObrazok_ON.png); }"
                                         "#btn_2:focus "
                                         "{   border-image: url(:/img/images/PaP_najdiObrazok_ON.png); }";
static QString stylesheet_site3_1_VecMen_ulohy = "#btn_1"
                                         "{ border-image: url(:/img/images/Mat_velkosti_OFF.png);"
                                         "border-radius: 15px;}"
                                         "#btn_1:pressed"
                                         "{   border-image: url(:/img/images/Mat_velkosti_ON.png); }"
                                         "#btn_1:focus "
                                         "{   border-image: url(:/img/images/Mat_velkosti_ON.png); }";

static QString stylesheet_site4_1_COIN = "#btn_1"
                                       "{ border-image: url(:/img/images/Zab_peniazky_OFF.png);"
                                       "border-radius: 15px;}"
                                       "#btn_1:pressed"
                                       "{   border-image: url(:/img/images/Zab_peniazky_ON.png); }"
                                       "#btn_1:focus "
                                       "{   border-image: url(:/img/images/Zab_peniazky_ON.png); }";
static QString stylesheet_site4_2_Lietadla = "#btn_2"
                                       "{ border-image: url(:/img/images/Zab_lietadla_OFF.png);"
                                       "border-radius: 15px;}"
                                       "#btn_2:pressed"
                                       "{   border-image: url(:/img/images/Zab_lietadla_ON.png); }"
                                       "#btn_2:focus "
                                       "{   border-image: url(:/img/images/Zab_lietadla_ON.png); }";
static QString stylesheet_btn_4_ZPET = "#btn_4 "
                               "{ border-image: url(:/img/images/Z5_OFF.png);"
                               "border-radius: 15px;}"
                               "#btn_4:pressed"
                               "{   border-image: url(:/img/images/Z5_ON.png); }"
                               "#btn_4:focus"
                               "{   border-image: url(:/img/images/Z5_ON.png); }";



/*_____GLOBAL_SETTINGS______*/
static QString stylesheet_site1_1 = "#btn_1"
                        "{   background-color: transparent;"
                        "border-image: url(:/img/images/MaOS_OFF.png); "
                        "background: none;"
                        "border-radius: 15px;  }"
                        "#btn_1:pressed"
                        "{   border-image: url(:/img/images/MaOS_ON.png); }"
                        "#btn_1:focus "
                        "{   border-image: url(:/img/images/MaOS_ON.png); }";

static QString sylesheet_site1_2 = "#btn_2 "
                          "{   background-color: transparent;border-image: url(:/img/images/PaP_OFF.png);"
                          "background: none;"
                          "border-radius: 15px;background-repeat: none; }"
                          "#btn_2:pressed"
                          "{   border-image: url(:/img/images/PaP_ON.png); }"
                          "#btn_2:focus"
                          "{   border-image: url(:/img/images/PaP_OFF.png); }";

static QString stylesheet_site1_3 = "#btn_3"
                                "{    background-color: transparent;"
                                "border-image: url(:/img/images/Mat_OFF.png);"
                                "background: none;"
                                "border-radius: 15px;"
                                "background-repeat: none;}"
                                "#btn_3:pressed"
                                "{   border-image: url(:/img/images/Mat_ON.png); }"
                                "#btn_3:focus"
                                "{	border-image: url(:/img/images/Mat_ON.png);}";

static QString stylesheet_site1_4 = "#btn_4 "
                                "{   background-color: transparent;"
                                "border-image: url(:/img/images/Zabava_OFF.png);"
                                "background: none;"
                                "border-radius: 15px;"
                                "background-repeat: none;}"
                                "#btn_4:pressed"
                                "{   border-image: url(:/img/images/Zabava_ON.png); }"
                                "#btn_4:focus"
                                "{   border-image: url(:/img/images/Zabava_ON.png); }";

static QString stylesheet_site1_sett = "#btn_settings"
                        "{   background-color: transparent;"
                        "border-image: url(:/img/images/SETTINGS_OFF.png); "
                        "background: none;"
                        "border-radius: 15px;  }"
                        "#btn_settings:pressed"
                        "{   border-image: url(:/img/images/SETTINGS_ON.png); }"
                        "#btn_settings:focus "
                        "{   border-image: url(:/img/images/SETTINGS_ON.png); }";

#endif // SETTINGS_H
