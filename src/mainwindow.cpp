/*
 * qt4sozluk, qt port of pysozluk (online/offline dictionary)
 * copyright (c) 2007, qt4sozluk development team
 *
 * this program is free software; you can redistribute it and/or modify
 * it under the terms of the gnu general public license as published by
 * the free software foundation; either version 2 of the license, or
 * (at your option) any later version.
 *
 * please read the copyIng file.
 */

#include <QApplication>
#include <QDebug>
#include <QIcon>
#include <QList>
#include <QListIterator>
#include <QMainWindow>
#include <QMessageBox>
#include <QSettings>
#include <QSystemTrayIcon>
#include <QWidget>

#include "configwindow.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QSettings settings;
    setupUi(this);
    this->move(settings.value("global/windowpos").toPoint());

    tray = new QSystemTrayIcon(QIcon(":/qt4sozluk.png"));
    createMenu();

    if(settings.value("tray/enabled").toBool()) {
        tray->show();
        qApp->setQuitOnLastWindowClosed(
            !settings.value("tray/minimizeOnClose").toBool());
    }
    if(settings.value("tray/startMinimized").toBool() &&
        settings.value("tray/enabled").toBool())
        this->hide();
    else
        this->show();

    searchThread = new SearchThread(this);
    configWindow = new ConfigWindow(this, tray);
    resultBrowser->clearHistory();
    statusBar()->showMessage(tr("Type in a keyword to search"));

    connect(
        searchThread, SIGNAL(found(QList< QList<QVariant> > *)),
        this, SLOT(showResults(QList< QList<QVariant> > *)));
    connect(searchButton, SIGNAL(clicked()), this, SLOT(search()));
    connect(keyword, SIGNAL(textEdited(const QString &)),
            this, SLOT(pressEnterMessage()));
    connect(tray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(showOrHideUi(QSystemTrayIcon::ActivationReason)));
    connect(actionAbout_Qt4Sozluk, SIGNAL(activated()),
            this, SLOT(aboutQt4Sozluk()));
    connect(actionAbout_Qt, SIGNAL(activated()), this, SLOT(aboutQt()));
    connect(actionQuit, SIGNAL(activated()), this, SLOT(exitSlot()));
    connect(actionConfigure, SIGNAL(activated()), configWindow, SLOT(show()));
}

void MainWindow::showOrHideUi(
        QSystemTrayIcon::ActivationReason activation_reason)
{
    QSettings sets;
    if(activation_reason == QSystemTrayIcon::Trigger){
        if(this->isVisible()){
          sets.setValue("global/windowpos", QVariant(this->pos()));
          this->setVisible(0);
        }else{
            if(sets.contains("global/windowpos"))
                this->move(sets.value("global/windowpos").toPoint());
            this->setVisible(1);
        }
    }
}

void MainWindow::createMenu()
{
    menu = new QMenu();
    menu->addAction(actionAbout_Qt4Sozluk);
    menu->addAction(actionConfigure);
    menu->addSeparator();
    menu->addAction(actionQuit);
    tray->setContextMenu(menu);
}

void MainWindow::search()
{
    resultBrowser->setHtml(tr("Searching \"%1\"").arg(keyword->text()));
    statusBar()->showMessage(tr("Searching \"%1\"").arg(keyword->text()));
    searchThread->search(keyword->text());
}

void MainWindow::showResults(QList< QList<QVariant> > *results)
{
    if (results->isEmpty()) {
        resultBrowser->setHtml(tr("<b>No results found</b>"));
        statusBar()->showMessage(tr("No results found"));
    }
    else {
        QString resultText;
        QList<QString> en, tr, ge;
        QListIterator< QList<QVariant> > i(*results);

        statusBar()->showMessage(
                this->tr("Found %1 results").arg(results->size()));
        while (i.hasNext()) {
            QList<QVariant> translation = i.next();
            switch (translation[0].toInt()) {
                case 0:
                    tr.append(translation[1].toString());
                    break;
                case 1:
                    en.append(translation[1].toString());
                    break;
                case 2:
                    ge.append(translation[1].toString());
                    break;
            }
        }
        if (!en.isEmpty()) {
            resultText.append(
                QString("<b>%1</b><br />").arg(
                    this->tr("%1 translation of %2").arg(
                        this->tr("English"), keyword->text())));

            for(int i=0; i<en.size();i++) {
                resultText.append(QString("%1. %2<br />").arg(i+1).arg(en[i]));
            }
            resultText.append("<br />");
        }
        if (!tr.isEmpty()) {
            resultText.append(
                QString("<b>%1</b><br />").arg(
                    this->tr("%1 translation of %2").arg(
                        this->tr("Turkish"), keyword->text())));

            for(int i=0; i<tr.size();i++) {
                resultText.append(QString("%1. %2<br />").arg(i+1).arg(tr[i]));
            }
            resultText.append("<br />");
        }
        if (!ge.isEmpty()) {
            resultText.append(
                QString("<b>%1</b><br />").arg(
                    this->tr("%1 translation of %2").arg(
                        this->tr("German"), keyword->text())));

            for(int i=0; i<ge.size();i++) {
                resultText.append(QString("%1. %2<br />").arg(i+1).arg(ge[i]));
            }
            resultText.append("<br />");
        }

        resultBrowser->setHtml(resultText);
    }
}

void MainWindow::aboutQt4Sozluk()
{
    QString aboutText;

    aboutText = tr("C++ version of  PySozluk-Qt") + "\nv" QT4SOZLUK_VERSION
        "\nhttp://pysozluk-qt.wiki.sourceforge.net\n\n" + tr("Developers:")
        + QString::fromUtf8("\nİlker Kesen <ilker.kde at gmail.com>\n"
        "İşbaran Akçayır <isbaran at gmail.com>\n"
        "Uğur Çetin <ugur.jnmbk at gmail.com>\n");

    QMessageBox::about(this, tr("About Qt4Sozluk"), aboutText);
}

void MainWindow::aboutQt()
{
    QMessageBox::aboutQt(this);
}

void MainWindow::pressEnterMessage()
{
    statusBar()->showMessage(tr("Press Enter to begin search"));
}

void MainWindow::exitSlot()
{
    QSettings sets;
    sets.setValue("global/windowpos", QVariant(this->pos()));
    qApp->quit();
}
