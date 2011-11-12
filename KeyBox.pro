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
    sitAsyCrypt.cpp \
    sitHashSec.cpp

HEADERS  += mainwindow.h \
    core/sitLog.h \
    core/sitObject.h \
    sitAsyCrypt.h \
    sitHashSec.h


FORMS    += mainwindow.ui










win32:CONFIG(release, debug|release): LIBS += -L$$PWD/cryptopp560/release/ -lcryptopp
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/cryptopp560/debug/ -lcryptopp
else:symbian: LIBS += -lcryptopp
else:unix: LIBS += -L$$PWD/cryptopp560/ -lcryptopp

INCLUDEPATH += $$PWD/cryptopp560
DEPENDPATH += $$PWD/cryptopp560

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/cryptopp560/release/cryptopp.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/cryptopp560/debug/cryptopp.lib
else:unix:!symbian: PRE_TARGETDEPS += $$PWD/cryptopp560/libcryptopp.a












