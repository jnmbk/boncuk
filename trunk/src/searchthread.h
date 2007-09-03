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

#ifndef SEARCHTHREAD_H
#define SEARCHTHREAD_H

#include <QThread>
#include "sqlitedatabase.h"
#include "seslisozluk.h"

class SearchThread : public QThread
{
    Q_OBJECT

    public:
        SearchThread(QObject *parent = 0);
        void search(QString);

    signals:
        void found(QList< QList<QVariant>  > *);

    protected:
        void run();

    private:
        QString keyword;
        bool lastSearchWasOffline;
        SesliSozluk *sesliSozluk;
        SqliteDatabase *sqliteDatabase;

    private slots:
        void returnResult(QList< QList<QVariant> > *);
};

#endif
