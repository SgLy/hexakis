#-------------------------------------------------
#
# Project created by QtCreator 2016-01-11T22:41:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = gui
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ../lib/block.cpp \
    ../lib/board.cpp \
    ../lib/util.cpp \
    ../lib/normal_game.cpp

HEADERS  += mainwindow.h \
    ../lib/block.h \
    ../lib/board.h \
    ../lib/util.h \
    consts.h \
    ../lib/normal_game.h \
    color_table.h

FORMS    += mainwindow.ui

RESOURCES += \
    gui.qrc
