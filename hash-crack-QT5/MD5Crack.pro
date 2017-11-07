#-------------------------------------------------
#
# Project created by QtCreator 2014-06-02T09:41:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MD5Crack
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mythread.cpp

HEADERS  += mainwindow.h \
    mythread.h

FORMS    += mainwindow.ui

QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

OTHER_FILES +=

RESOURCES += \
    Images.qrc
