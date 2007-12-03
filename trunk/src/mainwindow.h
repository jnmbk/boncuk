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
#include <QStringListModel>
#include <QVariant>
#include <QSettings>
#include <QWidget>

#include "searchthread.h"
#include "ui_mainwindow.h"
#include "configwindow.h"

class QString;
class QProcess;
class QCompleter;
class QCloseEvent;
class QMenu;
class QValidator;

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = 0);
        ~MainWindow();
        QSystemTrayIcon *tray;
        QSettings settings;
        QMenu *menu;
        QCompleter *completer;
        ConfigWindow *configWindow;
        QStringListModel *history;

        void closeEvent(QCloseEvent *);
        void createMenu();
        void initCompleter();

    public slots:
        void showResults(QList< QList<QVariant> > *);
        void clearHistory();
        void search();
        void showOrHideUi(QSystemTrayIcon::ActivationReason);
        void exitSlot();

    signals:
        void historyChanged(bool);

    private:
        SearchThread *searchThread;
        QValidator *validator;
        void writeHistory();

    private slots:
        void aboutQt4Sozluk();
        void aboutQt();
        void pressEnterMessage();
};



#endif
