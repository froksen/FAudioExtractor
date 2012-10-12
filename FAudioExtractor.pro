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
        #aboutdialog.cpp \
    soundfile.cpp \
    aboutdialog.cpp

HEADERS  += mainwindow.h \
            modules/process.h \
            #aboutdialog.h \
    soundfile.h \
    aboutdialog.h

TRANSLATIONS    = translations/da_DK.ts \
                  translations/de_DE.ts \
                  translations/es_ES.ts \
                  translations/it_IT.ts \
                  translations/cs_CZ.ts \
                  translations/ro_RO.ts \

FORMS    += mainwindow.ui \
            aboutdialog.ui

RESOURCES += \
    resource.qrc
