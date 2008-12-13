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
#include <QProcess>
#include <QStringList>
#include <QDir>
#include <QByteArray>
#include <QTextStream>

#include "mainwindow.h"
#include "console.h"

#ifdef Q_OS_UNIX
bool check_instance(char **argv)
{
    /*! Checks if any instances are running
    @return Returns true if theres an instance of program,
    or there's been an error while reading process list
    @return Returns false otherwise
    */

    QProcess *instancecheck = new QProcess;
    QStringList env = instancecheck->systemEnvironment().filter("USER");
    instancecheck->setReadChannelMode(QProcess::SeparateChannels);
    instancecheck->start("ps", QStringList() << "-U" << env.first().split("=").last() << "-x");

    if(!instancecheck->waitForFinished()) {
        instancecheck->close();
        delete instancecheck;
        return true;
    }

    QByteArray result = instancecheck->readAllStandardOutput();
    instancecheck->close();
    delete instancecheck;

    if( result.count( QByteArray(argv[0]).prepend(" ") ) <= 1 ){
        return false;
    }else{
        return true;
    }
    return 0;
}
#endif

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

    MainWindow *mainWindow = NULL;

    if (app.arguments().size() > 1) {
        Console *console = new Console();
        console->search();
        delete console;
        return 0;
    } else {
#ifdef Q_OS_UNIX
        // check instance for only gui startups
        if(!check_instance(argv)){
            mainWindow = new MainWindow();
        }else {
            QTextStream out(stdout);
            out << app.translate("main", "There's an instance of program running\n");
            app.exit(1);
        }
#else
        mainWindow = new MainWindow();
#endif
    }

    int exit_code = app.exec();
    if (mainWindow != NULL) {
        delete mainWindow;
    }

    return exit_code;
}

