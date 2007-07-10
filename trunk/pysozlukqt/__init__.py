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
from uic.Compiler.qtproxies import QtGui

import sys
import locale
from PyQt4 import QtCore, QtGui, uic
from core import pysozlukCore
from gettext import translation
import pysozlukglobals
import trayicon

locale.setlocale(locale.LC_ALL, "")
_ = translation('pysozluk-qt', fallback=True).ugettext

def retranslateUi(ui):
    ui.label.setText(_("Keyword:"))
    ui.pushButton.setText(_("&Search"))
    ui.menuFile.setTitle(_("&File"))
    ui.menuMode.setTitle(_("&Mode"))
    ui.menuHelp.setTitle(_("&Help"))
    ui.actionAbout_Pysozluk_Qt.setText(_("About &Pysozluk-Qt"))
    ui.actionAbout_Qt.setText(_("About &Qt"))
    ui.actionOffline.setText(_("&Offline"))
    ui.actionSave.setText(_("&Save"))
    ui.actionQuit.setText(_("&Quit"))
    ui.setWindowTitle(_("Pysozluk-Qt"))

def makeConnections(ui, core):
    QtCore.QObject.connect(
        ui.actionAbout_Pysozluk_Qt,QtCore.SIGNAL("activated()"),core.about)
    QtCore.QObject.connect(
        ui.actionAbout_Qt,QtCore.SIGNAL("activated()"),core.aboutQt)
    QtCore.QObject.connect(
        ui.actionOffline,QtCore.SIGNAL("activated()"),core.toggleOffline)
    QtCore.QObject.connect(ui.actionQuit,QtCore.SIGNAL("activated()"),ui.close)
    QtCore.QObject.connect(ui.actionSave,QtCore.SIGNAL("activated()"),core.save)
    QtCore.QObject.connect(ui.pushButton,QtCore.SIGNAL("clicked()"),core.search)
    QtCore.QObject.connect(
        ui.lineEdit,QtCore.SIGNAL("returnPressed()"),core.search)

def main():
    app = QtGui.QApplication(sys.argv)
    app.setOrganizationName("pysozluk-qt")
    app.setApplicationName("pysozluk-qt")
    settings = QtCore.QSettings()
    ui = uic.loadUi(pysozlukglobals.mainWindowFileName)

    #import pycallgraph
    #pycallgraph.start_trace()
    core = pysozlukCore(ui)
    retranslateUi(ui)
    makeConnections(ui, core)
    if settings.contains("windowPosition"):
        ui.move(settings.value("windowPosition").toPoint())

    if QtGui.QSystemTrayIcon.isSystemTrayAvailable() and \
        settings.value("trayIcon", QtCore.QVariant(True)).toBool():
        icon = trayicon.PySozlukTrayIcon(ui, app)
        icon.show()
        if settings.value(
            "minimizeToTrayOnClose", QtCore.QVariant(False)).toBool():
            app.setQuitOnLastWindowClosed(False)
    if not settings.value("startHidden", QtCore.QVariant(False)).toBool():
        ui.show()
    exitCode = app.exec_()
    settings.setValue("windowPosition", QtCore.QVariant(ui.pos()))
    #pycallgraph.stop_trace()
    #pycallgraph.make_dot_graph('pysozluk-qt.png')
    sys.exit(exitCode)

if __name__ == "__main__":
    main()
