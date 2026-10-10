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
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QList>
#include <QString>
#include <QRegularExpression>
#include <QVariant>
#include <QSettings>
#include "seslisozluk.h"

#define SESLISOZLUKHOSTNAME "www.seslisozluk.net"

SesliSozluk::SesliSozluk(QObject *parent)
    : QObject(parent)
{
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(continueSearch(QNetworkReply*)));
}

SesliSozluk::~SesliSozluk()
{
}

void SesliSozluk::convertToTurkishWeb(QString *word)
{
    word->replace(QString::fromUtf8("ı"), "%C4%B1");
    word->replace(QString::fromUtf8("İ"), "%C4%B0");
    word->replace(QString::fromUtf8("ö"), "%C3%B6");
    word->replace(QString::fromUtf8("Ö"), "%C3%96");
    word->replace(QString::fromUtf8("ç"), "%C3%A7");
    word->replace(QString::fromUtf8("Ç"), "%C3%87");
    word->replace(QString::fromUtf8("ş"), "%C5%9F");
    word->replace(QString::fromUtf8("Ş"), "%C5%9E");
    word->replace(QString::fromUtf8("ğ"), "%C4%9F");
    word->replace(QString::fromUtf8("Ğ"), "%C4%9E");
    word->replace(QString::fromUtf8("ü"), "%C3%BC");
    word->replace(QString::fromUtf8("Ü"), "%C3%9C");
    word->replace(" ", "+");
}

void SesliSozluk::search(QString keyword)
{
    word = keyword;
    convertToTurkishWeb(&keyword);
    QNetworkRequest request(QUrl(QString("http://") + SESLISOZLUKHOSTNAME + "/?word=" + keyword + "&lang=tr-en-de"));
    request.setRawHeader("Cookie", "compact_view=1");
    qDebug() << "Request URL:" << request.url().toString();
    manager->get(request);
}

void SesliSozluk::continueSearch(QNetworkReply* reply)
{
    if(reply->error() != QNetworkReply::NoError){
        qDebug() << "Error getting internet result: " << reply->errorString();
        reply->deleteLater();
        return;
    }

    QList< QList<QVariant> > results;
    QString text = QString::fromUtf8(reply->readAll());
    reply->deleteLater();

    QRegularExpression dlRegex("<h2 class=\"h2-sozluk-anlami[^>]*>(.*?)sözlükte anlamı</h2>(.*?)</dl>", QRegularExpression::DotMatchesEverythingOption);
    QRegularExpressionMatchIterator dlIt = dlRegex.globalMatch(text);
    
    while (dlIt.hasNext()) {
        QRegularExpressionMatch dlMatch = dlIt.next();
        QString header = dlMatch.captured(1);
        QString dlContent = dlMatch.captured(2);
        
        header.remove(QRegularExpression("<[^>]+>"));
        header = header.trimmed();
        QString langName = header.section(' ', -1);
        
        int lang = -1;
        if (langName == QString::fromUtf8("Türkçe")) {
            lang = 0;
        } else if (langName == QString::fromUtf8("İngilizce")) {
            lang = 1;
        } else if (langName == QString::fromUtf8("Almanca")) {
            lang = 2;
        }
        
        if (lang != -1) {
            QRegularExpression aRegex("<a\\s+[^>]*class=\"definition-link\"[^>]*>(.*?)</a>", QRegularExpression::DotMatchesEverythingOption);
            QRegularExpressionMatchIterator aIt = aRegex.globalMatch(dlContent);
            
            while (aIt.hasNext()) {
                QRegularExpressionMatch aMatch = aIt.next();
                QString content = aMatch.captured(1);
                content.remove(QRegularExpression("<[^>]+>"));
                content = content.replace(QRegularExpression("\\s+"), " ").trimmed();
                
                QList<QVariant> list;
                list << QVariant(lang) << QVariant(content);
                if (!results.contains(list)) {
                    results << list;
                }
            }
        }
    }

    emit found(word, results);
}

