#!/usr/bin/python
# -*- coding: utf-8 -*-
#
# pysozluk-qt, Qt port of pysozluk (online/offline dictionary)
# Copyright (C) 2007, pysozluk-qt Development Team
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# Please read the COPYING file.

import sys
import locale
from PyQt4 import QtCore, QtGui
from core import pysozlukCore
from gettext import translation

from mainWindow import Ui_MainWindow
import pysozlukglobals
import trayicon

locale.setlocale(locale.LC_ALL, "")
_ = translation('pysozluk-qt', fallback=True).ugettext

def makeConnections(ui, core, app):
    QtCore.QObject.connect(
        ui.actionAbout_Pysozluk_Qt,QtCore.SIGNAL("activated()"),core.about)
    QtCore.QObject.connect(
        ui.actionAbout_Qt,QtCore.SIGNAL("activated()"),core.aboutQt)
    QtCore.QObject.connect(ui.actionQuit,QtCore.SIGNAL("activated()"),app.quit)
    QtCore.QObject.connect(ui.actionSave,QtCore.SIGNAL("activated()"),core.save)
    QtCore.QObject.connect(ui.pushButton,QtCore.SIGNAL("clicked()"),core.search)
    QtCore.QObject.connect(
        ui.lineEdit,QtCore.SIGNAL("returnPressed()"),core.search)

class MainWindow(QtGui.QMainWindow, Ui_MainWindow):
    def __init__(self):
        QtGui.QMainWindow.__init__(self)
        self.setupUi(self)

    def retranslateUi(self, MainWindow):
        self.label.setText(_("Keyword:"))
        self.pushButton.setText(_("&Search"))
        self.menuFile.setTitle(_("&File"))
        self.menuHelp.setTitle(_("&Help"))
        self.actionAbout_Pysozluk_Qt.setText(_("About &PySozluk-Qt"))
        self.actionAbout_Qt.setText(_("About &Qt"))
        self.actionConfigure.setText(_("&Configure PySozluk-Qt"))
        self.actionOffline.setText(_("&Offline"))
        self.actionSave.setText(_("&Save"))
        self.actionQuit.setText(_("&Quit"))
        self.setWindowTitle(_("Pysozluk-Qt"))

def main():
    app = QtGui.QApplication(sys.argv)
    app.setOrganizationName("pysozluk-qt")
    app.setApplicationName("pysozluk-qt")
    settings = QtCore.QSettings()
    ui = MainWindow()
    ui.textBrowser.clearHistory() #this decreases memory usage

    #import pycallgraph
    #pycallgraph.start_trace()
    core = pysozlukCore(ui)
    ui.show() #dirty workaround for KDE startup notifier(should be shown later)
    makeConnections(ui, core, app)
    if settings.contains("windowPosition"):
        ui.move(settings.value("windowPosition").toPoint())

    if QtGui.QSystemTrayIcon.isSystemTrayAvailable() and \
        settings.value("tray/enabled", QtCore.QVariant(True)).toBool():
        icon = trayicon.PySozlukTrayIcon(ui, app, settings)
        icon.show()
        if settings.value(
            "tray/minimizeOnClose", QtCore.QVariant(True)).toBool():
            app.setQuitOnLastWindowClosed(False)
        if settings.value("tray/startHidden", QtCore.QVariant(False)).toBool():
            ui.hide()
    exitCode = app.exec_()
    settings.setValue("windowPosition", QtCore.QVariant(ui.pos()))
    #pycallgraph.stop_trace()
    #pycallgraph.make_dot_graph('pysozluk-qt.png')
    sys.exit(exitCode)

if __name__ == "__main__":
    main()
