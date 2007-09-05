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

#include <QDebug>
#include <QHttp>
#include <QList>
#include <QString>
#include <QTextCodec>
#include <QVariant>
#include <QVariant>
#include "seslisozluk.h"

SesliSozluk::SesliSozluk(QObject *parent = 0)
    : QObject(parent)
{
    http = new QHttp(this);
    http->setHost("www.seslisozluk.com");
    connect(http, SIGNAL(done(bool)), this, SLOT(continueSearch()));
}

void SesliSozluk::convertToTurkishWeb(QString *word)
{
    word->replace(QString::fromUtf8("ı"), "%FD");
    word->replace(QString::fromUtf8("İ"), "%DD");
    word->replace(QString::fromUtf8("ö"), "%F6");
    word->replace(QString::fromUtf8("Ö"), "%D6");
    word->replace(QString::fromUtf8("ç"), "%E7");
    word->replace(QString::fromUtf8("Ç"), "%C7");
    word->replace(QString::fromUtf8("ş"), "%FE");
    word->replace(QString::fromUtf8("Ş"), "%DE");
    word->replace(QString::fromUtf8("ğ"), "%F0");
    word->replace(QString::fromUtf8("Ğ"), "%D0");
    word->replace(QString::fromUtf8("ü"), "%FC");
    word->replace(QString::fromUtf8("Ü"), "%DC");
    word->replace(" ", "%20");
}

void SesliSozluk::search(QString keyword)
{
    convertToTurkishWeb(&keyword);
    http->get(QString("/?word=%1").arg(keyword));
}

void SesliSozluk::continueSearch()
{
    QList< QList<QVariant> > *results = new QList< QList<QVariant> >;
    QTextCodec *codec = QTextCodec::codecForName("ISO 8859-9");
    QString text;
    QStringList data;
    int i, j, turkish, english, german;

    text = codec->toUnicode(http->readAll());

    //now we can parse it
    text.remove(0, text.indexOf('>', text.indexOf("double_click_zone")) + 1);
    text.remove(text.indexOf("</table>"), text.size());
    text.replace("&nbsp;", " ");
    if (text.count('<') != text.count('>')){
        emit found(results);
        return; //this will happen when we have a really bad syntax error
    }
    do {
        i = text.indexOf('<');
        text.remove(i, text.indexOf('>') - i + 1);
        j = text.indexOf('<');
        if (j != -1 && j!= 0) {
            data << text.left(j).simplified();
            text.remove(0, j);
        }
    } while(i != -1);

    // html parsing is done

    qDebug() << data;
    turkish = data.indexOf("1.", data.indexOf("Turkish Translation"));
    english = data.indexOf("1.", data.indexOf("English Translation"));
    german = data.indexOf("1.", data.indexOf("German Translation"));

    if (turkish != -1)
        *results << pick(0,
                    data.mid(turkish, data.indexOf("", turkish) - turkish));
    if (english != -1)
        *results << pick(1,
                data.mid(english, data.indexOf("", english) - english));
    if (german != -1)
        *results << pick(2,
                    data.mid(german, data.indexOf("", german) - german));
    qDebug() << turkish << data.indexOf("", turkish) << english <<
        data.indexOf("", english) << german << data.indexOf("", german);

    emit found(results);
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
