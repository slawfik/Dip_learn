    QT       += core gui serialport

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
    games/G_Log_CoJeMensie/my_item.cpp \
    games/G_Log_CoJeMensie/vecie_mensie.cpp \
    games/G_Log_tiene/animal.cpp \
    games/G_Log_tiene/check_box.cpp \
    games/G_Log_tiene/my_button.cpp \
    games/G_Log_tiene/tiene.cpp \
    games/Mario_coin/coin.cpp \
    games/Mario_coin/hrac.cpp \
    games/Mario_coin/mario_coin.cpp \
    gamesmethod.cpp \
    main.cpp \
    learn_soft.cpp \
    serial_thread.cpp

HEADERS += \
    games/G_Log_CoJeMensie/my_item.h \
    games/G_Log_CoJeMensie/vecie_mensie.h \
    games/G_Log_tiene/animal.h \
    games/G_Log_tiene/check_box.h \
    games/G_Log_tiene/my_button.h \
    games/G_Log_tiene/tiene.h \
    games/Mario_coin/coin.h \
    games/Mario_coin/hrac.h \
    games/Mario_coin/mario_coin.h \
    gamesmethod.h \
    learn_soft.h \
    serial_thread.h \
    settings.h \
    tiene.h

FORMS += \
    learn_soft.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES +=
