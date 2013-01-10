#-------------------------------------------------
#
# Project created by QtCreator 2012-12-28T10:26:43
#
#-------------------------------------------------

QT       += core gui
QT       += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = microseismic-data-analysis
TEMPLATE = app

TRANSLATIONS += language.ts

SOURCES += main.cpp\
        mainwindow.cpp \
    coordsyswidget.cpp

HEADERS  += mainwindow.h \
    coordsyswidget.h

LIBS += -lglut32
