#-------------------------------------------------
#
# Project created by QtCreator 2011-11-04T10:40:56
#
#-------------------------------------------------

QT       += core gui

TARGET = KeyBox
TEMPLATE = app


SOURCES += main.cpp \
    mainwindow.cpp \
    Qsit/QsitSecretLineEdit.cpp \
    core/mbilog.cpp

HEADERS  += mainwindow.h \
    core/sitLog.h \
    Qsit/QsitSecretLineEdit.h \
    core/mbilogConfig.h \
    core/mbilog.h


FORMS    += mainwindow.ui \
    loginUser.ui

macx: LIBS += -L$$PWD/cryptopp560/ -lcryptopp

INCLUDEPATH += $$PWD/cryptopp560
DEPENDPATH += $$PWD/cryptopp560

macx: PRE_TARGETDEPS += $$PWD/cryptopp560/libcryptopp.a








