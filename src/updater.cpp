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

#include <iostream>

#include <QByteArray>
#include <QHttp>
#include "updater.h"

Updater::Updater(QObject *parent)
    : QObject(parent)
{
    QHttpRequestHeader header("GET", "/qtsozluk/latest.txt");
    header.setValue("Host", "ish.kodzilla.org");
    http = new QHttp(this);
    http->setHost("ish.kodzilla.org");
    http->request(header);
    connect(http, SIGNAL(done(bool)), this, SLOT(doneRequest(bool)));
}

Updater::~Updater()
{
    http->close();
    delete(http);
}

void Updater::doneRequest(bool error)
{
    QByteArray text = http->readAll();
    if(error){
        std::cout << "There happened an error while getting latest version";
        return;
    }
    text.chop(1); // qbytearray has a newline at the end

    emit latestVersion(QString(text));
}
