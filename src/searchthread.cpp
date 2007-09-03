/************************************************************************
 * qt4sozluk, Qt port of pysozluk (online/offline dictionary)           *
 * Copyright (C) 2007, qt4sozluk Development Team                       *
 *                                                                      *
 * This program is free software; you can redistribute it and/or modify *
 * it under the terms of the GNU General Public License as published by *
 * the Free Software Foundation; either version 2 of the License, or    *
 * (at your option) any later version.                                  *
 *                                                                      *
 * Please read the COPYING file.                                        *
 ************************************************************************/

#include <QDebug>
#include <QSettings>

#include "searchthread.h"

SearchThread::SearchThread(QObject *parent)
    : QThread(parent)
{
    lastSearchWasOffline = true;
    sqliteDatabase = new SqliteDatabase(this,
        "/usr/share/qt4sozluk/qt4sozluk.db");
    sesliSozluk = new SesliSozluk(this);
}

void SearchThread::run()
{
    exec();
}

void SearchThread::search(QString keyword)
{
    QSettings settings;
    this->keyword = keyword;
    qDebug() << isRunning();
    if (!isRunning()) {
        if (settings.value("translation/method", 0).toInt() < 2) {
            connect(
                sqliteDatabase, SIGNAL(found(QList< QList<QVariant> > *)),
                this, SLOT(returnResult(QList< QList<QVariant> > *)));
            sqliteDatabase->search(keyword);
            qDebug() << "offline";
        } else {
            connect(
                sesliSozluk, SIGNAL(found(QList< QList<QVariant> > *)),
                this, SLOT(returnResult(QList< QList<QVariant> > *)));
            sesliSozluk->search(keyword);
            lastSearchWasOffline = false;
            qDebug() << "online";
        }
        start();
    } else {
        sesliSozluk->disconnect();
        sqliteDatabase->disconnect();
        sesliSozluk->~SesliSozluk();
        sqliteDatabase->~SqliteDatabase();
        sesliSozluk = new SesliSozluk(this);
        sqliteDatabase = new SqliteDatabase(this,
            "/usr/share/pysozluk-qt/pysozluk-qt.db");
        if (settings.value("translation/method", 0).toInt() < 2) {
            connect(
                sqliteDatabase, SIGNAL(found(QList< QList<QVariant> > *)),
                this, SLOT(returnResult(QList< QList<QVariant> > *)));
            sqliteDatabase->search(keyword);
            qDebug() << "offline";
        } else {
            connect(
                sesliSozluk, SIGNAL(found(QList< QList<QVariant> > *)),
                this, SLOT(returnResult(QList< QList<QVariant> > *)));
            lastSearchWasOffline = false;
            sesliSozluk->search(keyword);
            qDebug() << "online";
        }
    }
}

void SearchThread::returnResult(QList< QList<QVariant> > *results)
{
    QSettings settings;
    qDebug() << results->isEmpty() << settings.value("translation/method", 0).toInt() << lastSearchWasOffline;
    if (results->isEmpty() &&
        settings.value("translation/method", 0).toInt() == 0 &&
        lastSearchWasOffline) {
        lastSearchWasOffline = false;
        sqliteDatabase->disconnect();
        connect(
            sesliSozluk, SIGNAL(found(QList< QList<QVariant> > *)),
            this, SLOT(returnResult(QList< QList<QVariant> > *)));
        sesliSozluk->search(keyword);
    } else {
        emit found(results);
        lastSearchWasOffline = true;
    }
}
