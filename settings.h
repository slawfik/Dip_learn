#ifndef SETTINGS_H
#define SETTINGS_H
#include <QString>
#include <QGraphicsScene>

#define WIDTH_SCREAN 1200
#define HIGHT_SCREAN 700
#define MOVE_STEP 20



//####STYLESHEETS#####

static QString stylesheet_g1 = "";
static QString stylesheet_site2_1_TIEN = "#btn_1"
                                         "{ border-image: url(:/img/images/G_TIEN_OFF.png);"
                                         "border-radius: 15px;}"
                                         "#btn_1:pressed"
                                         "{   border-image: url(:/img/images/G_TIEN_OFF.png); }"
                                         "#btn_1:focus "
                                         "{   border-image: url(:/img/images/G_TIEN_ON.png); }";
static QString stylesheet_site2_2_VecMen = "#btn_2"
                                         "{ border-image: url(:/img/images/G_VECMEN_OFF.png);"
                                         "border-radius: 15px;}"
                                         "#btn_2:pressed"
                                         "{   border-image: url(:/img/images/G_VECMEN_OFF.png); }"
                                         "#btn_2:focus "
                                         "{   border-image: url(:/img/images/G_VECMEN_ON.png); }";
static QString stylesheet_site4_1_COIN = "#btn_1"
                                       "{ border-image: url(:/img/images/G_COIN_OFF.png);"
                                       "border-radius: 15px;}"
                                       "#btn_1:pressed"
                                       "{   border-image: url(:/img/images/G_COIN_OFF.png); }"
                                       "#btn_1:focus "
                                       "{   border-image: url(:/img/images/G_COIN_ON.png); }";
static QString stylesheet_btn_4_ZPET = "#btn_4 "
                               "{ border-image: url(:/img/images/BT_ZPAT_OFF.png);"
                               "border-radius: 15px;}"
                               "#btn_4:pressed"
                               "{   border-image: url(:/img/images/BT_ZPAT_OFF.png); }"
                               "#btn_4:focus"
                               "{   border-image: url(:/img/images/BT_ZPAT_ON.png); }";



/*_____GLOBAL_SETTINGS______*/
static QString stylesheet_site1_1 = "#btn_1"
                        "{   background-color: transparent;"
                        "border-image: url(:/img/images/BT_ANJ_OFF.png); "
                        "background: none;"
                        "border-radius: 15px;  }"
                        "#btn_1:pressed"
                        "{   border-image: url(:/img/images/BT_ANJ_OFF.png); }"
                        "#btn_1:focus "
                        "{   border-image: url(:/img/images/BT_ANJ_ON.png); }";

static QString sylesheet_site1_2 = "#btn_2 "
                          "{   background-color: transparent;border-image: url(:/img/images/BT_LOG_OFF.png);"
                          "background: none;"
                          "border-radius: 15px;background-repeat: none; }"
                          "#btn_2:pressed"
                          "{   border-image: url(:/img/images/BT_LOG_OFF.png); }"
                          "#btn_2:focus"
                          "{   border-image: url(:/img/images/BT_LOG_ON.png); }";

static QString stylesheet_site1_3 = "#btn_3"
                                "{    background-color: transparent;"
                                "border-image: url(:/img/images/BT_MAT_OFF.png);"
                                "background: none;"
                                "border-radius: 15px;"
                                "background-repeat: none;}"
                                "#btn_3:pressed"
                                "{   border-image: url(:/img/images/BT_MAT_OFF.png); }"
                                "#btn_3:focus"
                                "{	border-image: url(:/img/images/BT_MAT_ON.png);}";

static QString stylesheet_site1_4 = "#btn_4 "
                                "{   background-color: transparent;"
                                "border-image: url(:/img/images/BT_ZAB_OFF.png);"
                                "background: none;"
                                "border-radius: 15px;"
                                "background-repeat: none;}"
                                "#btn_4:pressed"
                                "{   border-image: url(:/img/images/BT_ZAB_OFF.png); }"
                                "#btn_4:focus"
                                "{   border-image: url(:/img/images/BT_ZAB_ON.png); }";

#endif // SETTINGS_H
