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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QList>
#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QVariant>
#include <QSettings>
#include <QElapsedTimer>
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
class QKeyEvent;
class QStringListModel;

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = 0);
        ~MainWindow();
        QSettings settings;
        ConfigWindow *configWindow;
        QString guiLanguage;

        void createMenu();
        void initCompleter();
        void setSettings();

    public slots:
        void showResults(QString, QList< QList<QVariant> >);
        void on_actionHistoryClear_triggered();
        void search();
        void showOrHideUi(QSystemTrayIcon::ActivationReason);
        void on_actionQuit_triggered();

    signals:
        void historyChanged(bool);

    protected:
        void keyPressEvent(QKeyEvent *);
        void closeEvent(QCloseEvent *);
        bool eventFilter(QObject *obj, QEvent *ev);

    private:
        QMenu *menu;
        QElapsedTimer time;
        QCompleter *completer;
        QSystemTrayIcon *tray;
        QStringListModel *history;
        SearchThread *searchThread;
        QValidator *validator;
        /* set fatd to 'add/enabled's value to override global settings
         * and not add a word to user databases */
        int fatd;

    private slots:
        void on_actionAbout_Boncuk_triggered();
        void on_actionAbout_Qt_triggered();
        void pressEnterMessage();
        void writeHistory();
        QString prettyResult(QList<QString>, QString);
};



#endif
