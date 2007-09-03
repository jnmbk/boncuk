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

#ifndef CONSOLE_H
#define CONSOLE_H

#include <QObject>
#include <QList>
#include "searchthread.h"

class QVariant;

class Console : public QObject
{
    Q_OBJECT

    public slots:
        void search();
        void showResults(QList< QList<QVariant> > *);

    private:
        SearchThread *searchThread;
};

#endif
