#-------------------------------------------------
#
# Project created by QtCreator 2014-07-22T10:15:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Akadi
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    imagebox.cpp \
    imagetrim.cpp \
    helpinfobox.cpp

HEADERS  += mainwindow.h \
    imagebox.h \
    imagetrim.h \
    helpinfobox.h

FORMS    += mainwindow.ui \
    helpinfobox.ui

RESOURCES += \
    ressource.qrc
