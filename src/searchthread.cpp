/*
 * boncuk, qt port of pysozluk (online/offline dictionary)
 * copyright (c) 2007, boncuk development team
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
        DATABASE_LOCATION);

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

    qDebug() << "SearchThread is Running : " << isRunning();
    if (!isRunning()) {
        if (settings.value("translation/method", 0).toInt() < 2) {
            connect(
                sqliteDatabase, SIGNAL(found(QString, QList< QList<QVariant> > *)),
                this, SLOT(returnResult(QString, QList< QList<QVariant> > *)));
            qDebug() << "Performing an Offline search";
            sqliteDatabase->search(keyword);
        } else {
            connect(
                sesliSozluk, SIGNAL(found(QString, QList< QList<QVariant> > *)),
                this, SLOT(returnResult(QString, QList< QList<QVariant> > *)));
            sesliSozluk->search(keyword);
            lastSearchWasOffline = false;
            qDebug() << "Searching Online";
        }
        start();
    } else {
        sesliSozluk->disconnect();
        sqliteDatabase->disconnect();

        if (settings.value("translation/method", 0).toInt() < 2) {
            connect(
                sqliteDatabase, SIGNAL(found(QString, QList< QList<QVariant> > *)),
                this, SLOT(returnResult(QString, QList< QList<QVariant> > *)));
            qDebug() << "Performing an offline search";
            sqliteDatabase->search(keyword);
        } else {
            connect(
                sesliSozluk, SIGNAL(found(QString, QList< QList<QVariant> > *)),
                this, SLOT(returnResult(QString, QList< QList<QVariant> > *)));
            lastSearchWasOffline = false;
            sesliSozluk->search(keyword);
            qDebug() << "Searching online";
        }
    }
}

void SearchThread::returnResult(QString word, QList< QList<QVariant> > *results)
{
    QSettings settings;
    if (results->isEmpty() && settings.value("translation/method", 0).toInt() == 0 && lastSearchWasOffline) {
        lastSearchWasOffline = false;
        sqliteDatabase->disconnect(this);
        connect(
            sesliSozluk, SIGNAL(found(QString, QList< QList<QVariant> > *)),
            this, SLOT(returnResult(QString, QList< QList<QVariant> > *)));
        sesliSozluk->search(keyword);
    } else {
        if(!lastSearchWasOffline && settings.value("add/enabled", true).toBool())
            sqliteDatabase->add(word, results);
        emit found(word, results);
        lastSearchWasOffline = true;
    }
}

