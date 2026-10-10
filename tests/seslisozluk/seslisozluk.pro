QT += testlib network
TARGET = test_seslisozluk
TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle

INCLUDEPATH += ../../src
SOURCES += test_seslisozluk.cpp ../../src/seslisozluk.cpp
HEADERS += ../../src/seslisozluk.h

