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

#include <QDebug>
#include <QList>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <QVariant>
#include <QStringList>
#include <QSettings>
#include <QFile>
#include <QDir>
#include "sqlitedatabase.h"

#define HOME_DIR QDir::homePath()+"/.boncuk"

SqliteDatabase::SqliteDatabase(QObject *parent, QString databaseFile)
    : QObject(parent)
{
    QSettings settings;
    // keeps database names
    dbs = new QStringList("default");

    QSqlDatabase db = QSqlDatabase::database("default");
    if (!db.isValid()) {
        db = QSqlDatabase::addDatabase("QSQLITE", "default");
        db.setDatabaseName(databaseFile);
        db.open();
    }

    if(settings.value("add/enabled", true).toBool() && dbs->size()<2){
        createDb("userdb", QString(HOME_DIR)+"/boncuk.db");
        addDb("userdb", QString(HOME_DIR)+"/boncuk.db");
    }
}

SqliteDatabase::~SqliteDatabase()
{
    delete dbs;
}

void SqliteDatabase::addDb(QString name, QString uri)
{
    dbs->append(name);
    QSqlDatabase db = QSqlDatabase::database(name);

    if(!db.isValid()){
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", name);
        db.setDatabaseName(uri);
        db.open();
    }
}

void SqliteDatabase::createDb(QString name, QString uri)
{
    QDir directory(QString(HOME_DIR));
    if(!directory.exists())
        directory.mkpath(QString(HOME_DIR));

    QFile file(uri);
    if(file.exists())
        return;
    file.close();

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", name);
    db.setDatabaseName(uri);
    if(!db.open())
        qDebug() << "Couldn't open db file" << name << uri;

    QSqlQuery query(db);
    query.exec("CREATE TABLE languages (id, englishname, nativename)");
    query.exec("CREATE TABLE translations(home,away,word,text)");
    query.finish();
    db.commit();
}

void SqliteDatabase::search(QString word)
{
    QList< QList<QVariant> > *results = new QList< QList<QVariant> >;

    for(int d=0; d<dbs->size(); d++)
    {
        QSqlQuery query(QSqlDatabase::database(dbs->at(d)));
        query.prepare(
            "SELECT home, text FROM translations WHERE word = :keyword");
        query.bindValue(QString(":keyword"), QVariant(word));
        query.exec();

        while (query.next()) {
            QList<QVariant> list;
            list.append(query.value(0));
            list.append(query.value(1));
            results->append(list);
        }

        if (query.isActive())
            query.clear();

        if( d==0 && results->isEmpty() ){
            continue;
        }
    }
    // FIXME
    // little buggy, if we have more than 2 db's,
    // and they both have same word, will add same word twice ..
    emit found(word, results);
}

void SqliteDatabase::add(QString word, QList<QList<QVariant> > *results)
{
    if(results->isEmpty() || dbs->size()<2){
        return;
    }

    QString resultText;
    QList<QString> en, tr, ge;
    QListIterator< QList<QVariant> > i(*results);

    while (i.hasNext()) {
        QList<QVariant> translation = i.next();
        switch (translation[0].toInt()) {
            case 0:
                tr.append(translation[1].toString());
                break;
            case 1:
                en.append(translation[1].toString());
                break;
            case 2:
                ge.append(translation[1].toString());
                break;
        }
    }

    for(int d=1; d<dbs->size(); d++){

        QSqlDatabase db = QSqlDatabase::database(dbs->at(d));
        QSqlQuery query(db);

        if(!tr.isEmpty()){
            query.prepare("INSERT INTO translations (home, away, word, text) VALUES (:home, :away, :word, :text)");
            query.bindValue(QString(":home"), QVariant(0));
            query.bindValue(QString(":away"), QVariant(1));
            query.bindValue(QString(":word"), QVariant(word));
            query.bindValue(QString(":text"), QVariant(QStringList(tr).join(" , ")));
            if(query.exec()){
                if(query.isActive())
                    query.finish();
                db.commit();
            }
        }

        if (!en.isEmpty()){
            query.prepare("INSERT INTO translations (home, away, word, text) VALUES (:home, :away, :word, :text)");
            query.bindValue(QString(":home"), QVariant(1));
            query.bindValue(QString(":away"), QVariant(0));
            query.bindValue(QString(":word"), QVariant(word));
            query.bindValue(QString(":text"), QVariant(QStringList(en).join(" , ")));
            if(query.exec()){
                if(query.isActive())
                    query.finish();
                db.commit();
            }
        }
    }
}

