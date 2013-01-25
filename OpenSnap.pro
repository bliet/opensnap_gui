#-------------------------------------------------
#
# Project created by QtCreator 2013-01-23T20:46:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenSnap
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    action.cpp \
    parameter.cpp

HEADERS  += mainwindow.h \
    action.h \
    parameter.h \
    edge.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    README.md
