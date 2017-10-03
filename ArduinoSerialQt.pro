#-------------------------------------------------
#
# Project created by QtCreator 2017-10-03T11:50:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ArduinoSerialQt
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    readworker.cpp \
    arduino-serial/arduino-serial-lib.c

HEADERS  += mainwindow.h \
    readworker.h \
    arduino-serial/arduino-serial-lib.h

FORMS    += mainwindow.ui
