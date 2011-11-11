#-------------------------------------------------
#
# Project created by QtCreator 2011-11-04T10:40:56
#
#-------------------------------------------------

QT       += core gui

TARGET = KeyBox
TEMPLATE = app


SOURCES += main.cpp \
mainwindow.cpp

HEADERS  += mainwindow.h \
    core/sitLog.h \
    core/sitObject.h


FORMS    += mainwindow.ui

macx: LIBS += -L$$PWD/cryptopp560/ -lcryptopp

INCLUDEPATH += $$PWD/cryptopp560
DEPENDPATH += $$PWD/cryptopp560

macx: PRE_TARGETDEPS += $$PWD/cryptopp560/libcryptopp.a
