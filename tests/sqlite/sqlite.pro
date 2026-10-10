QT += testlib sql
TARGET = test_sqlite
TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle

INCLUDEPATH += ../../src
SOURCES += test_sqlite.cpp ../../src/sqlitedatabase.cpp
HEADERS += ../../src/sqlitedatabase.h
RESOURCES += ../../resources/boncuk.qrc
