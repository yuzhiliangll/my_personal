#-------------------------------------------------
#
# Project created by QtCreator 2024-06-27T15:56:19
#
#-------------------------------------------------

QT       += core gui network widgets xml multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Client
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        widget.cpp \
    myclientsocket.cpp \
    signup.cpp \
    account.cpp \
    netcon.cpp \
    afterlogin.cpp \
    musiclist.cpp \
    musicplayer.cpp \
    rotatewidget.cpp \
    http.cpp \
    listwidget.cpp \
    downloadtask.cpp

HEADERS += \
        widget.h \
    myclientsocket.h \
    signup.h \
    account.h \
    netcon.h \
    afterlogin.h \
    musiclist.h \
    musicplayer.h \
    rotatewidget.h \
    http.h \
    listwidget.h \
    downloadtask.h

FORMS += \
        widget.ui \
    signup.ui \
    account.ui \
    netcon.ui \
    afterlogin.ui \
    musicplayer.ui \
    rotatewidget.ui \
    http.ui \
    listwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc
