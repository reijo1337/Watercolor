#-------------------------------------------------
#
# Project created by QtCreator 2016-10-18T22:17:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TryWaterColor
TEMPLATE = app

QMAKE_LIBS+=-static -lgomp -lpthread

QMAKE_CXXFLAGS+=-fopenmp

SOURCES += main.cpp\
        mainwindow.cpp \
    splat.cpp \
    wet_map.cpp \
    pulsator.cpp \
    splat_scene.cpp \
    update_manager.cpp \
    strategy/splat_generator_strategy.cpp

HEADERS  += mainwindow.h \
    splat.h \
    wet_map.h \
    pulsator.h \
    pulsator_singleton.h \
    watercolor_types.h \
    splat_scene.h \
    update_manager.h \
    strategy/splat_generator_strategy.h

FORMS    += mainwindow.ui
