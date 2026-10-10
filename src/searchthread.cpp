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
    searchType = None;
    sqliteDatabase = new SqliteDatabase(this, "");

    sesliSozluk = new SesliSozluk(this);
}

SearchThread::~SearchThread()
{
    wait();
    quit();
}

void SearchThread::run()
{
    exec();
}

SearchType SearchThread::currentSearch()
{
    return searchType;
}

void SearchThread::search(QString keyword)
{
    QSettings settings;
    this->keyword = keyword;
    
    mergedResults.clear();

    sqliteDatabase->disconnect(this);
    sesliSozluk->disconnect(this);

    connect(
        sqliteDatabase, SIGNAL(found(QString, QList< QList<QVariant> >)),
        this, SLOT(offlineResultReady(QString, QList< QList<QVariant> >)));
        
    connect(
        sesliSozluk, SIGNAL(found(QString, QList< QList<QVariant> >)),
        this, SLOT(onlineResultReady(QString, QList< QList<QVariant> >)));

    qDebug() << "SearchThread is Running : " << isRunning();
    if (!isRunning()) {
        start();
    }
    
    qDebug() << "Performing an Offline search";
    searchType = SQLITE;
    sqliteDatabase->search(keyword);
    
    // 1 indicates "Offline only" in the legacy settings, 
    // so we skip online search only if user explicitly forced offline.
    if (settings.value("translation/method", 0).toInt() != 1) {
        searchType = SESLI; // Note: technically this type gets overwritten, but we don't strictly rely on it.
        qDebug() << "Searching Online asynchronously";
        sesliSozluk->search(keyword);
    }
}

void SearchThread::offlineResultReady(QString word, QList< QList<QVariant> > results)
{
    if (word != keyword) return; // Stale check
    
    mergedResults = results;
    emit found(word, mergedResults); 
}

void SearchThread::onlineResultReady(QString word, QList< QList<QVariant> > results)
{
    if (word != keyword) return;
    
    QSettings settings;
    bool newResultsAdded = false;
    QList< QList<QVariant> > newTranslations;
    
    for (int i = 0; i < results.size(); ++i) {
        if (!mergedResults.contains(results[i])) {
            mergedResults.append(results[i]);
            newTranslations.append(results[i]);
            newResultsAdded = true;
        }
    }
    
    if (newResultsAdded) {
        emit found(word, mergedResults);
        
        if (settings.value("add/enabled", true).toBool()) {
            sqliteDatabase->add(word, newTranslations);
        }
    } else if (mergedResults.isEmpty()) {
        // If offline was also empty, ensure we emit empty again so UI knows online finished empty too
        emit found(word, mergedResults);
    }
}

