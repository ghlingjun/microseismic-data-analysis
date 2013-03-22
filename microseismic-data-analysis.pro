#-------------------------------------------------
#
# Project created by QtCreator 2012-12-28T10:26:43
#
#-------------------------------------------------

QT       += core gui
QT       += opengl
QT       += sql
QT       += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = microseismic-data-analysis
TEMPLATE = app

TRANSLATIONS += language.ts

SOURCES += main.cpp\
        mainwindow.cpp \
    coordsyswidget.cpp \
    coordwidget.cpp \
    datamodel.cpp \
    readconfig.cpp \
    dbconn.cpp

HEADERS  += mainwindow.h \
    coordsyswidget.h \
    coordwidget.h \
    datamodel.h \
    connection.h \
    connection.h \
    readconfig.h \
    dbconn.h

LIBS += -lglut32

RESOURCES += \
    microseismic-data-analysis.qrc

OTHER_FILES += \
    microseismic.sql \
    config/dbconn.xml
