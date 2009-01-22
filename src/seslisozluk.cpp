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
#include <QHttp>
#include <QHttpRequestHeader>
#include <QList>
#include <QString>
#include <QRegExp>
#include <QTextCodec>
#include <QVariant>
#include <QVariant>
#include <QSettings>
#include "seslisozluk.h"

SesliSozluk::SesliSozluk(QObject *parent = 0)
    : QObject(parent)
{
    http = new QHttp(this);
    http->setHost("www.seslisozluk.com");
    connect(http, SIGNAL(done(bool)), this, SLOT(continueSearch(bool)));
}

SesliSozluk::~SesliSozluk()
{
    http->close();
    delete(http);
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
    QHttpRequestHeader header;
    word = keyword;
    convertToTurkishWeb(&keyword);
    header.setRequest("GET", QString("/?word=%1").arg(keyword));
    header.setValue("Cookie", "compact_view=1");
    header.setValue("Host", "www.seslisozluk.com");
    qDebug() << "Header:" << header.toString();
    http->request(header);
}

void SesliSozluk::continueSearch(bool err)
{
    if(err){
        qDebug() << "Error getting internet result: " << http->errorString();
        return;
    }

    QList< QList<QVariant> > *results = new QList< QList<QVariant> >;
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QString text;
    QStringList data;
    int i, j, turkish, english, german;

    text = codec->toUnicode(http->readAll());
    // qDebug() << "HTML:" << text;

    //now we can parse it
    text.remove(0, text.indexOf('>', text.indexOf("tabsResult")) + 1);
    text.remove(text.indexOf(" <!-- <div id=translations -->"), text.size());
    if (text.count('<') != text.count('>')){
        emit found(word, results);
        return; //this will happen when we have a really bad syntax error
    }
    do {
        /* remove all html tags like <div>, </div> */
        i = text.indexOf('<');
        text.remove(i, text.indexOf('>') - i + 1);
        j = text.indexOf('<');
        if (j != -1 && j!= 0) {
            data << text.left(j).simplified();
            text.remove(0, j);
        }
    } while(i != -1);

    // html parsing is done

    qDebug() << "RESULTS :" << data << '\n';
    turkish = data.indexOf("1.", data.indexOf(QRegExp(QString::fromUtf8("^Türkçe.*"))));
    english = data.indexOf("1.", data.indexOf(QRegExp(QString::fromUtf8("^İngilizce.*"))));
    german = data.indexOf("1.", data.indexOf(QRegExp(QString::fromUtf8("^Almanca.*"))));

    if (turkish != -1)
        *results << pick(0,
                    data.mid(turkish, data.indexOf("", turkish) - turkish));
    if (english != -1)
        *results << pick(1,
                data.mid(english, data.indexOf("", english) - english));
    if (german != -1)
        *results << pick(2,
                    data.mid(german, data.indexOf("", german) - german));
    // qDebug() << turkish << data.indexOf("", turkish) << english << data.indexOf("", english) << german << data.indexOf("", german);

    emit found(word, results);
}

QList< QList<QVariant> > SesliSozluk::pick(int lang, QList<QString> text)
{
    QList< QList<QVariant> > translations;

    for(int i = 1; i < text.size(); i+=2) {
        QList<QVariant> list;
        list << QVariant(lang) << QVariant(text[i]);
        translations << list;
    }

    return translations;
}
