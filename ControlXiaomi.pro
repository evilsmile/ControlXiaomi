#-------------------------------------------------
#
# Project created by QtCreator 2014-07-30T13:43:55
#
#-------------------------------------------------

QT       += core gui
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ControlXiaomi
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    filesender.cpp \
    hacker.cpp

HEADERS  += mainwindow.h \
    filesender.h \
    hacker.h \
    config.h

FORMS    += mainwindow.ui
