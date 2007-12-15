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

##ifndef TRAYICON_H
#define TRAYICON_H

#include <QSystemTrayIcon>

class QAction;
class QMenu;
class MainWindow;

class TrayIcon : public QSystemTrayIcon
{
    Q_OBJECT

    public:
        TrayIcon(MainWindow *);
        ~TrayIcon();

    public slots:
        void openConfigure();
        void showOrHideUi( QSystemTrayIcon::ActivationReason );
        void exitClicked();

    private:
        QMenu *trayIconMenu;
        QAction *action_configure;
        QAction *action_exit;

        MainWindow *mainw;
};

#endif
