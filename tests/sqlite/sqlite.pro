QT += testlib sql
TARGET = test_sqlite
TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
macx {
    QMAKE_LIBS_OPENGL -= -framework AGL
    QMAKE_LIBS_OPENGL_ES2 -= -framework AGL
    LIBS -= -framework AGL
}

INCLUDEPATH += ../../src
SOURCES += test_sqlite.cpp ../../src/sqlitedatabase.cpp
HEADERS += ../../src/sqlitedatabase.h
RESOURCES += ../../resources/boncuk.qrc
