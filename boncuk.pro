TEMPLATE = app
TARGET = boncuk
VERSION = "2.0.0"
macx {
    ICON = resources/boncuk.icns
    QMAKE_LIBS_OPENGL -= -framework AGL
    QMAKE_LIBS_OPENGL_ES2 -= -framework AGL
    LIBS -= -framework AGL
    QMAKE_CXXFLAGS += -Wno-error=implicit-function-declaration
}
win32 {
    RC_ICONS = resources/boncuk.ico
}
DEFINES += \
    BONCUK_VERSION=\\\"$$VERSION\\\"

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

CONFIG += release

# Generate .qm files from .ts
qm.input = TRANSLATIONS
qm.output = $$PWD/resources/${QMAKE_FILE_BASE}.qm
qm.commands = $$[QT_INSTALL_BINS]/lrelease ${QMAKE_FILE_IN} -qm ${QMAKE_FILE_OUT}
qm.CONFIG += no_link target_predeps
QMAKE_EXTRA_COMPILERS += qm

DESTDIR = bin
OBJECTS_DIR = build
MOC_DIR = build
UI_DIR = build
RCC_DIR = build

QT += \
    network \
    sql \
    widgets
