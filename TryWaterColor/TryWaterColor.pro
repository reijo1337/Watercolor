#-------------------------------------------------
#
# Project created by QtCreator 2016-10-18T22:17:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TryWaterColor
TEMPLATE = app

QMAKE_CXXFLAGS += -fopenmp
LIBS += -fopenmp

SOURCES += main.cpp\
        mainwindow.cpp \
    splat.cpp \
    wet_map.cpp \
    splat_scene.cpp \
    strategy/splat_generator_strategy.cpp

HEADERS  += mainwindow.h \
    splat.h \
    wet_map.h \
    watercolor_types.h \
    splat_scene.h \
    strategy/splat_generator_strategy.h

FORMS    += mainwindow.ui

RESOURCES += \
    background/backgrounds.qrc
