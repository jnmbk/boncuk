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
#include "sqlitedatabase.h"

SqliteDatabase::SqliteDatabase(QObject *parent, QString databaseFile)
    : QObject(parent)
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isValid()) {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(databaseFile);
        db.open();
    }
}

void SqliteDatabase::search(QString word)
{
    QSqlQuery query;
    QList< QList<QVariant> > *results = new QList< QList<QVariant> >;

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
    qDebug() << "Returning" << results->size() << "result(s)";
    emit found(word, results);
}

void SqliteDatabase::add(QString word, QList<QList<QVariant> > *results)
{
    if(results->isEmpty()){
        qDebug() << "Resultset is empty, not adding to database: " << word << "\n";
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

    qDebug() << "Number of TR translations fetched : " << tr.count() << "\n";
    qDebug() << "Number of EN translations fetched : " << en.count() << "\n";
    qDebug() << "Number of DU translations fetched : " << ge.count() << "\n";

    QSqlQuery query;

    if (!tr.isEmpty()){
        query.prepare("INSERT INTO translations (home, away, word, text) VALUES (:home, :away, :word, :text)");
        query.bindValue(QString(":home"), QVariant(0));
        query.bindValue(QString(":away"), QVariant(1));
        query.bindValue(QString(":word"), QVariant(word));
        query.bindValue(QString(":text"), QVariant(QStringList(tr).join(" , ")));
        query.exec();
    }
    if (!en.isEmpty()){
        query.prepare("INSERT INTO translations (home, away, word, text) VALUES (:home, :away, :word, :text)");
        query.bindValue(QString(":home"), QVariant(1));
        query.bindValue(QString(":away"), QVariant(0));
        query.bindValue(QString(":word"), QVariant(word));
        query.bindValue(QString(":text"), QVariant(QStringList(en).join(" , ")));
        query.exec();
    }

    qDebug() << "Added to database" << results->size() << "result(s)";
}

