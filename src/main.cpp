/*
 * boncuk, Qt port of pysozluk (online/offline dictionary)
 * Copyright (C) 2007, boncuk Development Team
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
#include <QProcess>
#include <QByteArray>

#include <iostream>

#include "mainwindow.h"
#include "console.h"

bool check_instance( char ** );

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
    translator.load(QString(":/boncuk_") + locale);
    app.installTranslator(&translator);

    if (app.arguments().size() > 1) {
        Console *console = new Console();
        console->search();
    } else {
        // check instance for only gui startups
        if(!check_instance(argv)){
            MainWindow *mainWindow = new MainWindow();
        }else{
            //FIXME Exit message is hardcoded in english
            std::cout << "There's an instance of program running\n";
            exit(1);
        }
    }

    return app.exec();
}

bool check_instance(char **argv)
{
    /*! Checks if any instances are running
    @return Returns true if theres an instance of program,\
    or there's been an error while reading process list
    @return Returns 0 otherwise
    */

    QProcess instancecheck;
    instancecheck.start("ps", QStringList() << "au");
    if(!instancecheck.waitForStarted())
        return 1;

    QByteArray result;

    while( instancecheck.waitForReadyRead() )
        result += instancecheck.readAll();

    if( result.count(argv[0]) <= 1 ){
        return 0;
    }else{
        return 1;
    }

    return 0;
}

