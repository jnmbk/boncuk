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
#include <QSqlError>
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

    qDebug() << "Boncuk: Using" << dbs->count() << "databases and internet search";
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
    if(!directory.exists()){
        directory.mkpath(QString(HOME_DIR));
        qDebug() << "Creating user database path : " << QString(HOME_DIR);
    }

    QFile file(uri);
    if (file.exists()) {
        qDebug() << "Database file exists : " << uri;
        file.close();
        return;
    }
    file.close();

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", name);
    db.setDatabaseName(uri);
    if (db.isValid()){
        if(!db.open()){
            qDebug() << "Couldn't open database file " << name << "at :" << uri;
            return;
        }
    }else {
        qDebug() << "Db is not valid : " << name << db.lastError().text();
        return;
    }

    QSqlQuery query(db);
    query.exec("CREATE TABLE languages (id, englishname, nativename)");
    query.finish();
    query.exec("CREATE TABLE translations (home, away, word, text)");
    query.finish();
    query.exec("INSERT INTO languages (id, englishname, nativename) VALUES (0, 'English', 'English')");
    query.finish();
    query.exec("INSERT INTO languages (id, englishname, nativename) VALUES (1, 'Turkish', 'Turkce')");
    query.finish();

    qDebug() << "Created Tables for user database, errors : " << query.lastError().text();
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

        if( results->isEmpty() ) {
            qDebug() << word << "not found in database : " << dbs->at(d);
            continue;
        }else{
            qDebug() << word << "Found in Database : " << dbs->at(d);
            break;
        }
    }

    emit found(word, results);
}

void SqliteDatabase::add(QString word, QList<QList<QVariant> > *results)
{
    if(results->isEmpty() || dbs->size()<2) {
        qDebug() << "No new results or No databases to add new results";
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

    QSqlQuery *query = NULL;

    // First db is default db, and its read only
    for(int d=1; d<dbs->size(); d++) {

        QSqlDatabase db = QSqlDatabase::database(dbs->at(d));
        qDebug() << "Adding" << word << "to db : " << dbs->at(d);

        if(!tr.isEmpty()) {
            query = new QSqlQuery(db);
            query->prepare("INSERT INTO translations (home, away, word, text) VALUES (:home, :away, :word, :text)");
            query->bindValue(QString(":home"), QVariant(0));
            query->bindValue(QString(":away"), QVariant(1));
            query->bindValue(QString(":word"), QVariant(word));
            query->bindValue(QString(":text"), QVariant(QStringList(tr).join(" , ")));
            query->exec();
            query->finish();
            db.commit();
            delete query;
            query = NULL;
        }

        if (!en.isEmpty()){
            query = new QSqlQuery(db);
            query->prepare("INSERT INTO translations (home, away, word, text) VALUES (:home, :away, :word, :text)");
            query->bindValue(QString(":home"), QVariant(1));
            query->bindValue(QString(":away"), QVariant(0));
            query->bindValue(QString(":word"), QVariant(word));
            query->bindValue(QString(":text"), QVariant(QStringList(en).join(" , ")));
            query->exec();
            query->finish();
            db.commit();
            delete query;
            query = NULL;
        }
    }

    if (query != NULL)
        delete query;
}

