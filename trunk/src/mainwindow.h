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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QList>
#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QVariant>
#include <QWidget>

#include "searchthread.h"
#include "ui_mainwindow.h"
#include "configwindow.h"
#include "updater.h"

class QString;
class QProcess;
class QMenu;
class QValidator;

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = 0);
        ~MainWindow();
        QSystemTrayIcon *tray;
        QMenu *menu;
        ConfigWindow *configWindow;
        Updater *update;

        void createMenu();

    public slots:
        void showResults(QList< QList<QVariant> > *);
        void search();
        void showOrHideUi(QSystemTrayIcon::ActivationReason);
        void printLatest(QString);
        void openProjectHomePage();

    private:
        SearchThread *searchThread;
        QProcess *myProc;
        QValidator *validator;

    private slots:
        void aboutQt4Sozluk();
        void aboutQt();
        void pressEnterMessage();
        void exitSlot();
};

#endif
