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

#ifndef SQLITEDATABASE_H
#define SQLITEDATABASE_H

#include <QList>
#include <QObject>
#include <QVariant>
#include <QStringList>

class QString;

class SqliteDatabase : public QObject
{
    Q_OBJECT

    public:
        SqliteDatabase(QObject *parent, QString databaseFile);
        ~SqliteDatabase();
        void search(QString word);

        // make more than one db connections
        QStringList dbs;

    private:
        void addDb(QString, QString);
        void createDb(QString, QString);

    signals:
        void found(QString, QList< QList<QVariant> >);

    public slots:
        void add(QString, QList<QList<QVariant> >);

};

#endif
