/*
 * boncuk, qt port of pysozluk (online/offline dictionary)
 * copyright (c) 2007, boncuk development team
 *
 * this program is free software; you can redistribute it and/or modify
 * it under the terms of the gnu general public license as published by
 * the free software foundation; either version 2 of the license, or
 * (at your option) any later version.
 *
 * please read the copying file.
 */

#include <QApplication>
#include <QDebug>
#include <QIcon>
#include <QList>
#include <QListIterator>
#include <QKeyEvent>
#include <QMainWindow>
#include <QMessageBox>
#include <QList>
#include <QCompleter>
#include <QSettings>
#include <QStringList>
#include <QSystemTrayIcon>
#include <QCloseEvent>
#include <QProcess>
#include <QEvent>
#include <QWidget>

#include "configwindow.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);

    setSettings();

    tray = new QSystemTrayIcon(this->windowIcon(), this);

    createMenu();
    searchButton->installEventFilter(this);

    if(settings.value("tray/enabled", true).toBool()) {
        tray->show();
        qApp->setQuitOnLastWindowClosed(
            !settings.value("tray/minimizeOnClose", true).toBool());
    }
    if(settings.value("tray/startMinimized", true).toBool() &&
        settings.value("tray/enabled", true).toBool())
        this->hide();
    else
        this->show();

    if(settings.value("history/enabled").toBool()){
        initCompleter();
    }else{
        completer = NULL;
        history = NULL;
        actionHistoryClear->setEnabled(false);
    }

    guiLanguage = QLocale::system().name();
    guiLanguage.truncate(2);

    searchThread = new SearchThread(this);
    configWindow = new ConfigWindow(this, tray);
    statusBar()->showMessage(tr("Type in a keyword to search"));
    searchButton->setEnabled(0);

    QRegExp searchLineRx("[\\w\\s]*");
    validator = new QRegExpValidator(searchLineRx, this);
    keyword->setValidator(validator);
    keyword->setMaxLength(64);

    connect(
        searchThread, SIGNAL(found(QString, QList< QList<QVariant> > *)),
        this, SLOT(showResults(QString, QList< QList<QVariant> > *)));
    //connect(searchButton, SIGNAL(clicked()), this, SLOT(search()));
    connect(keyword, SIGNAL(textEdited(const QString &)),
            this, SLOT(pressEnterMessage()));
    connect(tray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(showOrHideUi(QSystemTrayIcon::ActivationReason)));
    connect(actionHistoryClear, SIGNAL(activated()),
            this, SLOT(clearHistory()));
    connect(this, SIGNAL(historyChanged(bool)),
            actionHistoryClear, SLOT(setEnabled(bool)));
    connect(actionAbout_Boncuk, SIGNAL(activated()),
            this, SLOT(aboutBoncuk()));
    connect(actionAbout_Qt, SIGNAL(activated()), this, SLOT(aboutQt()));
    connect(actionQuit, SIGNAL(activated()), this, SLOT(exitSlot()));
    connect(actionConfigure, SIGNAL(activated()), configWindow, SLOT(show()));
    connect(actionSearchOn, SIGNAL(activated()), this, SLOT(searchOnline()));
    connect(actionSearchOff, SIGNAL(activated()), this, SLOT(searchOffline()));
}

MainWindow::~MainWindow()
{
    // Bunlar otomatik siliniyor aslında ..
    delete(history);
    delete(menu);
    delete(tray);
    delete(validator);
    delete(completer);
}

void MainWindow::initCompleter()
{
    QStringList stringList;
    int size = settings.beginReadArray("historydata");

    for(int i=0; i < size; ++i) {
       settings.setArrayIndex(i);
       stringList.append(settings.value("key").toString());
    }

    settings.endArray();
    history = new QStringListModel( stringList );

    completer = new QCompleter(history, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    keyword->setCompleter(completer);

    if( size <= 0 )
        actionHistoryClear->setEnabled(false);

    qDebug() << "History initialized for" << size << "words";
}

void MainWindow::setSettings()
{
    if(settings.contains("mainWindow/pos"))
        this->move(settings.value("mainWindow/pos").toPoint());

    if(settings.contains("mainWindow/geo"))
        this->resize(settings.value("mainWindow/geo").toSize());
    else {
        this->resize(400, 300);
        settings.setValue("mainWindow/geo", QVariant(QSize(400, 300)));
    }
    // ara sürümdeki count=0 hatası için workaround
    if(settings.value("history/count", 100).toInt() < 1)
        settings.setValue("history/count", QVariant(100));
    if(!settings.contains("add/enabled"))
        settings.setValue("add/enabled", QVariant(false));
    if(!settings.contains("history/enabled"))
        settings.setValue("history/enabled", QVariant(true));
    settings.setValue("fatdb", QVariant(-1));
}

void MainWindow::clearHistory()
{
    if(completer){
        history->setStringList(QStringList());
        settings.remove("historydata");
        statusBar()->showMessage(tr("History deleted"), 2000);
        emit historyChanged(false);
    }
}

void MainWindow::keyPressEvent( QKeyEvent *event )
{
    if( event->key() == Qt::Key_Escape ){
        if( settings.value("tray/enabled").toBool() &&
            settings.value("tray/minimizeOnClose").toBool() ){
            this->close();
        }else
            QWidget::keyPressEvent(event);
    }else if((event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) && searchButton->isEnabled() && keyword->hasFocus()){
        search();
    }else
        QWidget::keyPressEvent(event);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    settings.setValue("mainWindow/pos", QVariant(this->pos()));
    settings.setValue("mainWindow/geo", QVariant(this->size()));
    event->accept();
}

void MainWindow::showOrHideUi(
        QSystemTrayIcon::ActivationReason activation_reason)
{
    if(activation_reason == QSystemTrayIcon::Trigger) {
        if(this->isVisible()) {
          settings.setValue("mainWindow/pos", QVariant(this->pos()));
          settings.setValue("mainWindow/geo", QVariant(this->size()));
          this->hide();
        } else {
            this->move(settings.value("mainWindow/pos").toPoint());
            this->resize(settings.value("mainWindow/geo").toSize());
            keyword->setSelection(0, (keyword->text()).size());
            this->show();
        }
    }
}

void MainWindow::createMenu()
{
    // popup menu for tray
    menu = new QMenu();
    menu->addAction(actionAbout_Boncuk);
    menu->addAction(actionConfigure);
    menu->addSeparator();
    menu->addAction(actionQuit);
    tray->setContextMenu(menu);

    // popup menu for search button
    smenu = new QMenu();
    smenu->addAction(actionSearchOn);
    smenu->addSeparator();
    smenu->addAction(actionSearchOff);
    searchButton->setMenu(smenu);
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == searchButton && searchButton->isEnabled()){
        qApp->setDoubleClickInterval(0);
        if(event->type() == QEvent::MouseButtonPress){
            time.restart();
            return true;
        }else if(event->type() == QEvent::MouseButtonRelease){
            if(qApp->doubleClickInterval() < time.elapsed() && time.elapsed() < 800){
                search();
                return true;
            }else{
                searchButton->showMenu();
                return true;
            }
        }else if(event->type() == QEvent::MouseButtonDblClick){
            searchButton->showMenu();
            return false;
        }else
            return false;
    }else
        return QMainWindow::eventFilter(obj, event);
}

void MainWindow::search()
{
    if(settings.value("history/enabled").toBool()){
        if( history == NULL ){
            initCompleter();
        }

        QStringList list( history->stringList() );

        if(list.size() >= settings.value("history/count", 100).toInt()){
            while(list.size() >= settings.value("history/count", 100).toInt()){
                list.removeLast();
            }
        }

        list.append(keyword->text());

        history->setStringList( list.toSet().toList() );
        writeHistory();
        emit historyChanged(true);
    }

    resultBrowser->setHtml(tr("Searching \"%1\"").arg(keyword->text()));
    statusBar()->showMessage(tr("Searching \"%1\"").arg(keyword->text()));
    searchThread->search(keyword->text());
    keyword->setSelection(0, (keyword->text()).size());
}

void MainWindow::searchOnline()
{
    int old_method = settings.value("translation/method", 0).toInt();
    // set dont add to database value
    settings.setValue("fatdb", QVariant(settings.value("add/enabled").toInt()));

    settings.setValue("translation/method", QVariant(2));
    settings.sync();
    search();
    settings.setValue("translation/method", QVariant(old_method));
}

void MainWindow::searchOffline()
{
    int old_ = settings.value("translation/method", 0).toInt();
    settings.setValue("fatdb", QVariant(settings.value("add/enabled").toInt()));

    settings.setValue("translation/method", QVariant(1));
    settings.sync();
    search();
    settings.setValue("translation/method", QVariant(old_));
}

void MainWindow::showResults(QString, QList< QList<QVariant> > *results)
{
    if (results->isEmpty()) {
        // Search again with lowercase characters if search string is composed of uppercase characters
        //TODO update db with all lower case, or make insensitive searches in db
        if (keyword->text() != keyword->text().toLower()) {
            keyword->setText(keyword->text().toLower());
            qDebug() << "lowering case...";
            this->search();
        } else {
            resultBrowser->setHtml(tr("<b>No results found</b>"));
            statusBar()->showMessage(tr("No results found"));
        }
    }
    else {
        QString resultText;
        QList<QString> eng, trq, ger;
        QListIterator< QList<QVariant> > i(*results);

        statusBar()->showMessage(
                this->tr("Found %1 results").arg(results->size()));
        while (i.hasNext()) {
            QList<QVariant> translation = i.next();
            switch (translation[0].toInt()) {
                case 0:
                    trq.append(translation[1].toString());
                    break;
                case 1:
                    eng.append(translation[1].toString());
                    break;
                case 2:
                    ger.append(translation[1].toString());
                    break;
            }
        }

        if (guiLanguage == QString("tr")){
            resultText.append(prettyResult( eng, tr("English")));
            resultText.append(prettyResult( ger, tr("German")));
            resultText.append(prettyResult( trq, tr("Turkish")));
        }else{
            resultText.append(prettyResult( trq, tr("Turkish")));
            resultText.append(prettyResult( eng, tr("English")));
            resultText.append(prettyResult( ger, tr("German")));
        }

        resultBrowser->setHtml(resultText);
    }
    delete results;
}

QString MainWindow::prettyResult( QList<QString> lang, QString text )
{
    QString resultText("");
    if(!lang.isEmpty()){
        resultText.append(
            QString("<b>%1</b><br />").arg(
                this->tr("%1 translation of %2").arg(text, keyword->text())));
        for(int i=0; i<lang.size(); i++){
            resultText.append(QString("%1. %2<br />").arg(i+1).arg(lang[i]));
        }
        resultText.append("<br />");
    }
    return resultText;
}


void MainWindow::aboutBoncuk()
{
    QString aboutText = QString::fromUtf8((tr("Boncuk %1 - online/offline dictionary\n\
This software is released under the terms of GPL v2.\n\
http://pysozluk-qt.wiki.sourceforge.net\n\n\
Developers:\n\
İlker Kesen <ilker.kde at gmail.com>\n\
İşbaran Akçayır <isbaran at gmail.com>\n\
Uğur Çetin <ugur.jnmbk at gmail.com>\n").arg(BONCUK_VERSION)).toAscii().constData());

    QMessageBox::about(this, tr("About Boncuk"), aboutText);
}

void MainWindow::aboutQt()
{
    QMessageBox::aboutQt(this);
}

void MainWindow::pressEnterMessage()
{
    statusBar()->showMessage(tr("Press Enter to begin search"));
    if( keyword->text() == "" )
        searchButton->setEnabled(0);
    else
        searchButton->setEnabled(1);
}

void MainWindow::writeHistory()
{
    if(settings.value("history/enabled").toBool()){
        settings.remove("historydata");
        settings.beginWriteArray("historydata");
        for (int i=0; i < history->stringList().size(); ++i) {
            settings.setArrayIndex(i);
            settings.setValue("key", history->stringList().at(i));
        }
        settings.endArray();
        settings.sync();
    }else {
        qDebug() << "History not enabled, not saving ..";
    }
}

void MainWindow::exitSlot()
{
    settings.setValue("mainWindow/pos", QVariant(this->pos()));
    settings.setValue("mainWindow/geo", QVariant(this->size()));
    settings.sync();

    if(searchThread->isRunning())
        searchThread->quit();

    qDebug() << "Bye Bye ..";
    qApp->quit();
}

