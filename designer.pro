QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cur_game.cpp \
    database.cpp \
    main.cpp \
    mainwindow.cpp \
    money.cpp \
    pass_recovery.cpp \
    registration.cpp \
    shop.cpp \
    users_list.cpp

HEADERS += \
    cur_game.h \
    database.h \
    mainwindow.h \
    money.h \
    pass_recovery.h \
    registration.h \
    shop.h \
    users_list.h

FORMS += \
    cur_game.ui \
    mainwindow.ui \
    money.ui \
    pass_recovery.ui \
    registration.ui \
    shop.ui \
    users_list.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
