/*
 * qt4sozluk, Qt port of pysozluk (online/offline dictionary)
 * Copyright (C) 2007, qt4sozluk Development Team
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Please read the COPYING file.
 */

#include <QApplication>
#include <QDebug>
#include <QLocale>
#include <QMainWindow>
#include <QTranslator>
#include <QSettings>

#include "mainwindow.h"
#include "console.h"

int main(int argc, char *argv[])
{
    MainWindow *mainWindow;
    Console *console;

#ifdef Q_WS_X11
    bool useGui = getenv("DISPLAY") != 0;
#else
    bool useGui = true;
#endif

    QApplication app(argc, argv, useGui);

    app.setOrganizationName(QString("qt4sozluk"));
    app.setApplicationName(QString("qt4sozluk"));

    QString locale = QLocale::system().name();
    QTranslator translator;
    translator.load(QString(":/qt4sozluk_") + locale);
    app.installTranslator(&translator);

    if (app.arguments().size() > 1) {
        console = new Console();
        console->search();
    } else {
        mainWindow = new MainWindow();
    }
    return app.exec();
}

