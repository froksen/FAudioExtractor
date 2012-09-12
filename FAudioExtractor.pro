#-------------------------------------------------
#
# Project created by QtCreator 2012-09-12T15:34:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FAudioExtractor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        modules/process.cpp \
    soundfile.cpp

HEADERS  += mainwindow.h \
            modules/process.h \
    soundfile.h

FORMS    += mainwindow.ui
