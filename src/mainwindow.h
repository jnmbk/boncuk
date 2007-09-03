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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QList>
#include <QMainWindow>
#include <QVariant>
#include <QSystemTrayIcon>
#include "searchthread.h"
#include "ui_mainwindow.h"
#include <QWidget>
#include <QMenu>

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = 0);
        QSystemTrayIcon *tray;
        QMenu *menu;
        void createMenu();
        void connectActions();

    public slots:
        void showResults(QList< QList<QVariant> > *);
        void search();
        void showOrHideUi(QSystemTrayIcon::ActivationReason);

    private:
        SearchThread *searchThread;

    private slots:
        void aboutQt4Sozluk();
        void aboutQt();
        void configure();
        void pressEnterMessage();
        void exitSlot();
};

#endif
