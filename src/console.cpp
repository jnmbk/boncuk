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
#include <QSettings>
#include <QStringList>
#include <QTextStream>
#include "console.h"
#include "searchthread.h"

Console::Console()
{
    searchThread = new SearchThread(this);
    connect(
        searchThread, SIGNAL(found(QString, QList< QList<QVariant> >)),
        this, SLOT(showResults(QString, QList< QList<QVariant> >)));
}

void Console::search()
{
    QString keyword;
    QSettings settings;

    QStringList args = qApp->arguments();
    for (int i=1; i < args.size(); i++) {
        keyword.append(args.at(i));
        if (i < args.size()-1)
            keyword.append(" ");
    }
    qDebug() << "Searching : " << keyword;
    searchThread->search(keyword);

    // 5 sec. internet search timeout
    if (searchThread->currentSearch() == SESLI) {
        searchThread->wait(5000);
        qDebug() << "Time out";
    } else {
        searchThread->wait(500);
    }
}

void Console::showResults(QString /*word*/, QList< QList<QVariant> > results)
{
    QTextStream out(stdout);

    for (int i=0; i < results.size(); i++)
        out << results.at(i).at(1).toString() << '\n';
}

Console::~Console()
{
    if(searchThread->isRunning())
        searchThread->quit();
    delete searchThread;
}
