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
#include <QList>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <QVariant>
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
    emit found(results);
}
