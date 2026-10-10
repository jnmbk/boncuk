/*
 * boncuk, Qt port of pysozluk (online/offline dictionary)
 * Copyright (C) 2007-2008, boncuk Development Team
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
#include <QSharedMemory>
#include <QStringList>
#include <QDir>
#include <QByteArray>
#include <QTextStream>

#include "mainwindow.h"
#include "console.h"

int main(int argc, char *argv[])
{
#ifdef Q_WS_X11
    bool useGui = getenv("DISPLAY") != 0;
#else
    bool useGui = true;
#endif

    QApplication app(argc, argv, useGui);

    app.setOrganizationName(QString("boncuk"));
    app.setApplicationName(QString("boncuk"));

    QString locale = QLocale::system().name();
    QTranslator translator;
    (void)translator.load(QString(":/boncuk_") + locale);
    app.installTranslator(&translator);

    MainWindow *mainWindow = NULL;
    QSharedMemory sharedMemory("boncuk_shared_instance");

    if (app.arguments().size() > 1) {
        Console *console = new Console();
        console->search();
        delete console;
        return 0;
    } else {
        // check instance for only gui startups
        if (!sharedMemory.create(1)) {
            // Attempt to clean up in case of a crashed instance on Unix
            if (sharedMemory.error() == QSharedMemory::AlreadyExists && sharedMemory.attach()) {
                sharedMemory.detach();
            }
            if (!sharedMemory.create(1)) {
                QTextStream out(stdout);
                out << app.translate("main", "There's an instance of program running\n");
                return 1;
            }
        }
        mainWindow = new MainWindow();
    }

    int exit_code = app.exec();
    if (mainWindow != NULL) {
        delete mainWindow;
    }

    return exit_code;
}

