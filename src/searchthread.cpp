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
#include <iostream>

SearchThread::SearchThread(QObject *parent)
    : QThread(parent)
{
    lastSearchWasOffline = true;
    sqliteDatabase = new SqliteDatabase(this,
        DATABASE_LOCATION);

    sesliSozluk = new SesliSozluk(this);

    QSettings settings;
    if(settings.value("add/enabled", true).toBool()){
        connect(sesliSozluk, SIGNAL(found(QString, QList< QList<QVariant> > *)),
        sqliteDatabase, SLOT(add(QString, QList< QList<QVariant> > *)));
    }
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
                sqliteDatabase, SIGNAL(found(QString, QList< QList<QVariant> > *)),
                this, SLOT(returnResult(QString, QList< QList<QVariant> > *)));
            sqliteDatabase->search(keyword);
            qDebug() << "offline";
        } else {
            connect(
                sesliSozluk, SIGNAL(found(QString, QList< QList<QVariant> > *)),
                this, SLOT(returnResult(QString, QList< QList<QVariant> > *)));
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
            DATABASE_LOCATION);
        if (settings.value("translation/method", 0).toInt() < 2) {
            connect(
                sqliteDatabase, SIGNAL(found(QString, QList< QList<QVariant> > *)),
                this, SLOT(returnResult(QString, QList< QList<QVariant> > *)));
            sqliteDatabase->search(keyword);
            qDebug() << "offline";
        } else {
            connect(
                sesliSozluk, SIGNAL(found(QString, QList< QList<QVariant> > *)),
                this, SLOT(returnResult(QString, QList< QList<QVariant> > *)));
            if(settings.value("add/enabled", true).toBool()){
                connect(sesliSozluk, SIGNAL(found(QString, QList< QList<QVariant> > *)),
                sqliteDatabase, SLOT(add(QString, QList< QList<QVariant> > *)));
            }
            lastSearchWasOffline = false;
            sesliSozluk->search(keyword);
            qDebug() << "online";
        }
    }
}

void SearchThread::returnResult(QString word, QList< QList<QVariant> > *results)
{
    QSettings settings;
    if (results->isEmpty() && settings.value("translation/method", 0).toInt() == 0 && lastSearchWasOffline) {
        qDebug() << "word not found in database, searching net : searchthread.cpp - returnResult\n";
        lastSearchWasOffline = false;
        if(!sqliteDatabase->disconnect(this)){
            qDebug() << "sqlitedatabase disconnect failed: searchthread.cpp - returnResult \n";
        }
        connect(
            sesliSozluk, SIGNAL(found(QString, QList< QList<QVariant> > *)),
            this, SLOT(returnResult(QString, QList< QList<QVariant> > *)));
        sesliSozluk->search(keyword);
    } else {
        if(!lastSearchWasOffline)
            sqliteDatabase->add(word, results);
        emit found(word, results);
        lastSearchWasOffline = true;
    }
}
