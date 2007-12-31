TEMPLATE = app
TARGET = boncuk
VERSION = "0.3"
DATABASE = "/usr/share/boncuk/boncuk.db"
DEFINES += \
    QT_NO_DEBUG_OUTPUT \
    BONCUK_VERSION=\\\"$$VERSION\\\" \
    DATABASE_LOCATION=\\\"$$DATABASE\\\"

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
    resources/boncuk.qrc
TRANSLATIONS += \
    resources/boncuk_tr_TR.ts

DESTDIR = bin
OBJECTS_DIR = build
MOC_DIR = build
UI_DIR = build
RCC_DIR = build

QT += \
    network \
    sql
