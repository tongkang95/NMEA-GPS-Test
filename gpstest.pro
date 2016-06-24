#-------------------------------------------------
#
# Project created by QtCreator 2015-12-02T16:16:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gpstest
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp\
        qextserial/qextserialport.cpp

HEADERS  += dialog.h \
        qextserial/qextserialport_global.h \
        qextserial/qextserialport.h

win32 {
     SOURCES += qextserial/qextserialport_win.cpp
}

unix {
     SOURCES += qextserial/qextserialport_unix.cpp
}

FORMS    += dialog.ui
