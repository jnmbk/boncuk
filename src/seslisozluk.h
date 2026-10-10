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

#ifndef SESLISOZLUK_H
#define SESLISOZLUK_H

#include <QList>
#include <QVariant>
#include <QObject>

class QNetworkAccessManager;
class QNetworkReply;
class QString;

class SesliSozluk : public QObject
{
    Q_OBJECT

    public:
        SesliSozluk(QObject *parent);
        ~SesliSozluk();
        void search(QString word);

    signals:
        void found(QString, QList< QList<QVariant> >);

    private:
        QNetworkAccessManager *manager;

        void convertToTurkishWeb(QString *);
        QString word;

    private slots:
        void continueSearch(QNetworkReply* reply);
};

#endif
