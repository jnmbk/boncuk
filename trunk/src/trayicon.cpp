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


#include <QApplication>
#include <QSystemTrayIcon>
#include <QSettings>
#include <QAction>
#include <QMenu>
#include <QIcon>

#include "trayicon.h"
#include "configwindow.h"
#include "mainwindow.h"

TrayIcon::TrayIcon(MainWindow *ptr)
{
    mainw = ptr;
    action_configure = new QAction( QIcon(":/configure.png"), "Configure", this );
    connect(action_configure, SIGNAL(triggered()), this, SLOT(openConfigure()));
    action_exit = new QAction( QIcon(":/exit.png"), "Exit", this );
    connect(action_exit, SIGNAL(triggered()), this, SLOT(exitClicked()));
    connect(this, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(showOrHideUi(QSystemTrayIcon::ActivationReason)));

    trayIconMenu = new QMenu();
    trayIconMenu->addAction(action_configure);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(action_exit);

    this->setContextMenu(trayIconMenu);
    this->setIcon(QIcon(":/boncuk.png"));
}

void TrayIcon::~TrayIcon()
{
    if(cw)
        delete(cw);
    delete(action_configure);
    delete(action_exit);
    delete(trayIconMenu);
}

void TrayIcon::exitClicked()
{
    mainw->exitSlot();
    mainw->deleteLater();
    emit destroyed();
    qApp->quit();
}

void TrayIcon::showOrHideUi(QSystemTrayIcon::ActivationReason activation_reason)
{
    QSettings sets;
    if(activation_reason == QSystemTrayIcon::Trigger){
        if(mainw->isVisible()){
            sets.setValue("mainWindow/pos", QVariant(mainw->pos()));
            mainw->setVisible(0);
        }else{
            if(sets.contains("mainWindow/pos"))
                mainw->move(sets.value("mainWindow/pos").toPoint());
            mainw->setVisible(1);
        }
    }
}

void TrayIcon::openConfigure()
{
    cw = new ConfigWindow();
    cw->show();
}

