/*
 * boncuk, Qt port of pysozluk (online/offline dictionary)
 * Copyright (C) 2007, boncuk Development Team
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Please read the COPYING file.
 */

#ifndef CONFIGWONDOW_H
#define CONFIGWONDOW_H

#include <QApplication>
#include <QSettings>
#include "ui_configwindow.h"

class QDialog;
class QWidget;
class QSystemTrayIcon;

class ConfigWindow : public QDialog, private Ui::ConfigWindow
{
    Q_OBJECT

    public:
        ConfigWindow(QWidget *parent = 0, QSystemTrayIcon *tptr = 0);
        QSystemTrayIcon *trayptr;
        QWidget *parentptr;

    public:
        QSettings settings;

    public slots:
        void writeSettings();
        void applySettings();
        void stateSync(int);
};

#endif
