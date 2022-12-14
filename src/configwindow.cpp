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

#include <QtCore>
#include <QDialog>
#include <QWidget>
#include <QApplication>
#include <QSettings>
#include <QVariant>
#include <QKeyEvent>
#include <QSystemTrayIcon>
#include "configwindow.h"

ConfigWindow::ConfigWindow(QWidget *parent, QSystemTrayIcon *tptr)
    : QDialog(parent)
{
    trayptr = tptr;
    parentptr = parent;
    setupUi(this);

    connect(this, SIGNAL(accepted()), this, SLOT(writeSettings()));

    translation_method->setCurrentIndex(
            settings.value("translation/method").toInt());

    /* Always check values that user can change */
    if (settings.value("history/count", 100).toInt() < 1)
        settings.setValue("history/count", QVariant(100));

    if(settings.value("history/enabled", QVariant(true)).toBool() == 1){
        history_enable->setCheckState(Qt::Checked);
        wordcountSpinBox->setValue(settings.value("history/count", 100).toInt());
    }else{
        wordcountSpinBox->setValue(settings.value("history/count", 100).toInt());
        wordcountSpinBox->setEnabled(false);
    }

    if (settings.value("add/enabled", QVariant(true)).toBool() == 1)
        add_enable->setCheckState(Qt::Checked);

    if (settings.value("tray/minimizeOnClose", QVariant(true)).toBool() == 1)
        trayIcon_minimizeOnClose->setCheckState(Qt::Checked);

    if (settings.value("tray/startMinimized", QVariant(true)).toBool() == 1){
        trayIcon_startMinimized->setCheckState(Qt::Checked); }

    if (settings.value("tray/enabled", QVariant(true)).toBool()){
        trayIcon_enable->setCheckState(Qt::Checked);
    }else{
        trayIcon_enable->setCheckState(Qt::Unchecked); 
        stateSync(0);
    }

    connect(trayIcon_enable, SIGNAL(stateChanged(int)),
        this, SLOT(stateSync(int)));
    connect(history_enable, SIGNAL(stateChanged(int)),
        this, SLOT(slotHistorySync(int)));
}

void ConfigWindow::keyPressEvent( QKeyEvent *event )
{
    if( event->key() == Qt::Key_Escape )
        this->close();
    QWidget::keyPressEvent(event);
}

void ConfigWindow::stateSync(int state)
{
    trayIcon_minimizeOnClose->setEnabled(state);
    trayIcon_startMinimized->setEnabled(state);
}

void ConfigWindow::slotHistorySync(int state)
{
    if(state == 0)
        this->wordcountSpinBox->setEnabled(false);
    else
        this->wordcountSpinBox->setEnabled(true);
}

void ConfigWindow::writeSettings() {
    settings.setValue("translation/method",
            QVariant(translation_method->currentIndex()));
    settings.setValue("tray/enabled",
            QVariant(trayIcon_enable->checkState()).toBool());
    settings.setValue("tray/minimizeOnClose",
            QVariant(trayIcon_minimizeOnClose->checkState()).toBool());
    settings.setValue("tray/startMinimized",
            QVariant(trayIcon_startMinimized->checkState()).toBool());
    settings.setValue("history/count",
            QVariant(wordcountSpinBox->value()));
    settings.setValue("history/enabled",
            QVariant(history_enable->checkState()));
    settings.setValue("add/enabled",
            QVariant(add_enable->checkState()).toBool());
    applySettings();
}

void ConfigWindow::applySettings() {
    if(trayIcon_enable->checkState() == Qt::Unchecked) {
        parentptr->show();
        trayptr->hide();
        qApp->setQuitOnLastWindowClosed(true);
    } else if(trayIcon_enable->checkState() == Qt::Checked) {
        trayptr->show();
        if (settings.value("tray/minimizeOnClose").toBool())
            qApp->setQuitOnLastWindowClosed(false);
        else qApp->setQuitOnLastWindowClosed(true);
    }
    settings.sync();
}
