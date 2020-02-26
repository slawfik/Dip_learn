    QT       += core gui serialport widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    games/G_MaOS_RocneObdobia/pexeso_items.cpp \
    games/G_MaOS_RocneObdobia/rocne_obdobia.cpp \
    games/G_Mat_VecsiMensi/vecmen_ulohy.cpp \
    games/G_PaP_CoJeMensie/my_item.cpp \
    games/G_PaP_CoJeMensie/vecie_mensie.cpp \
    games/G_MaOS_tiene/animal.cpp \
    games/G_MaOS_tiene/prirad_tiene.cpp \
    games/G_MaOS_tiene/tiene.cpp \
    games/G_PaP_NajdiObrazok/najdi_obrazok.cpp \
    games/G_Zab_Mario_coin/coin.cpp \
    games/G_Zab_Mario_coin/hrac.cpp \
    games/G_Zab_Mario_coin/mario_coin.cpp \
    games/utils/my_animation_items.cpp \
    games/utils/my_button.cpp \
    games/utils/my_items.cpp \
    games/utils/my_scenes.cpp \
    src/gamesmethod.cpp \
    main.cpp \
    learn_soft.cpp \
    src/serial_thread.cpp \
    src/dialog.cpp

HEADERS += \
    games/G_MaOS_RocneObdobia/pexeso_items.h \
    games/G_MaOS_RocneObdobia/rocne_obdobia.h \
    games/G_Mat_VecsiMensi/vecmen_ulohy.h \
    games/G_PaP_CoJeMensie/my_item.h \
    games/G_PaP_CoJeMensie/vecie_mensie.h \
    games/G_MaOS_tiene/animal.h \
    games/G_MaOS_tiene/prirad_tiene.h \
    games/G_MaOS_tiene/tiene.h \
    games/G_PaP_NajdiObrazok/najdi_obrazok.h \
    games/G_Zab_Mario_coin/coin.h \
    games/G_Zab_Mario_coin/hrac.h \
    games/G_Zab_Mario_coin/mario_coin.h \
    games/utils/my_animation_items.h \
    games/utils/my_button.h \
    games/utils/my_items.h \
    games/utils/my_scenes.h \
    src/gamesmethod.h \
    learn_soft.h \
    src/serial_thread.h \
    settings.h \ \
    src/dialog.h

FORMS += \
    learn_soft.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES +=
