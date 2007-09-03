TEMPLATE = app
TARGET = qt4sozluk
VERSION = 0.1_beta1
DEFINES += \
#    QT4SOZLUK_VERSION=\\\"$$VERSION\\\"
    QT4SOZLUK_VERSION=\\\"$$VERSION\\\" \
    QT_NO_DEBUG_OUTPUT

# Input
HEADERS += \
    src/configwindow.h \
    src/console.h \
    src/mainwindow.h \
    src/searchthread.h \
    src/seslisozluk.h \
    src/sqlitedatabase.h
FORMS += \
    ui/configwindow.ui \
    ui/mainwindow.ui
SOURCES += \
    src/configwindow.cpp \
    src/console.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/searchthread.cpp \
    src/seslisozluk.cpp \
    src/sqlitedatabase.cpp
RESOURCES += \
    resources/qt4sozluk.qrc
TRANSLATIONS += \
    resources/qt4sozluk_tr_TR.ts

DESTDIR = bin
OBJECTS_DIR = build
MOC_DIR = build
UI_DIR = build
RCC_DIR = build

QT += \
    network \
    sql
