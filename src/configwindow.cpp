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
#include "configwindow.h"

ConfigWindow::ConfigWindow(QWidget *parent)
    : QDialog(parent)
{
    parentptr = parent;
    setupUi(this);

    connect(this, SIGNAL(accepted()), this, SLOT(writeSettings()));

    if (settings.value("translation/method", 0).toInt() != 1) {
        online_search_enable->setCheckState(Qt::Checked);
    } else {
        online_search_enable->setCheckState(Qt::Unchecked);
    }

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
            QVariant(online_search_enable->isChecked() ? 0 : 1));
    settings.setValue("history/count",
            QVariant(wordcountSpinBox->value()));
    settings.setValue("history/enabled",
            QVariant(history_enable->checkState()));
    settings.setValue("add/enabled",
            QVariant(add_enable->checkState()).toBool());
    applySettings();
}

void ConfigWindow::applySettings() {
    settings.sync();
}
