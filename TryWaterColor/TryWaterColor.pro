#-------------------------------------------------
#
# Project created by QtCreator 2016-10-18T22:17:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TryWaterColor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    splat.cpp \
    wet_map.cpp \
    pulsator.cpp \
    splat_scene.cpp

HEADERS  += mainwindow.h \
    splat.h \
    wet_map.h \
    pulsator.h \
    pulsator_singleton.h \
    watercolor_types.h \
    splat_scene.h

FORMS    += mainwindow.ui
