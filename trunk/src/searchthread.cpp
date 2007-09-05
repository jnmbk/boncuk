/*
 * qt4sozluk, qt port of pysozluk (online/offline dictionary)
 * copyright (c) 2007, qt4sozluk development team
 *
 * this program is free software; you can redistribute it and/or modify
 * it under the terms of the gnu general public license as published by
 * the free software foundation; either version 2 of the license, or
 * (at your option) any later version.
 *
 * please read the copyIng file.
 */

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
        delete sesliSozluk;
        delete sqliteDatabase;
        sesliSozluk = new SesliSozluk(this);
        sqliteDatabase = new SqliteDatabase(this,
            "/usr/share/qt4sozluk/qt4sozluk.db");
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
