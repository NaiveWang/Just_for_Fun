#-------------------------------------------------
#
# Project created by QtCreator 2017-12-26T16:00:11
#
#-------------------------------------------------

QT       += core gui
QT       += opengl
QT       += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GOLSimulator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    goldisplayer.cpp \
    golcore.cpp \
    gollog.cpp \
    golcontrolpanel.cpp \
    golchart.cpp

HEADERS  += mainwindow.h \
    goldisplayer.h \
    golcore.h \
    gollog.h \
    golcontrolpanel.h \
    golchart.h

FORMS    += mainwindow.ui
