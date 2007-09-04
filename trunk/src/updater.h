/*
 * qt4sozluk, Qt port of pysozluk (online/offline dictionary)
 * Copyright (C) 2007, qt4sozluk Development Team
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Please read the COPYING file.
 */


#ifndef UPDATER_H
#define UPDATER

#include <QObject>

class QHttp;

class Updater : public QObject
{
    Q_OBJECT

    public:
        Updater(QObject *parent = 0);
        ~Updater();

    private:
        QHttp *http;

    signals:
        void latestVersion(QString);

    private slots:
        void doneRequest(bool);
};

#endif

