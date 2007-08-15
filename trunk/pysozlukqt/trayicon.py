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

from PyQt4 import QtGui
from PyQt4 import QtCore
import pysozlukglobals

from debugger import Debugger

debugger = Debugger()

class PySozlukTrayIcon(QtGui.QSystemTrayIcon):
    def __init__(self, ui, app, settings):
        QtGui.QSystemTrayIcon.__init__(
            self, QtGui.QIcon(pysozlukglobals.getIcon("pysozluk-qt")))
        self.ui = ui
        self.settings = settings
        #action_translate = QtGui.QAction(
        #    QtGui.QIcon(pysozlukglobals.getIcon("locale")),
        #    _("Translate Clipboard"), self)
        action_configure = QtGui.QAction(
            QtGui.QIcon(pysozlukglobals.getIcon("configure")),
            QtGui.QApplication.translate("Tray", "Configure PySozluk-Qt"),
            self)
        action_exit = QtGui.QAction(
            QtGui.QIcon(pysozlukglobals.getIcon("exit")),
            QtGui.QApplication.translate("Tray", "Exit"), self)

        self.menu = QtGui.QMenu()
        #self.menu.addAction(action_translate)
        #self.menu.addSeparator()
        self.menu.addAction(action_configure)
        self.menu.addSeparator()
        self.menu.addAction(action_exit)

        QtCore.QObject.connect(
            action_exit, QtCore.SIGNAL("triggered()"), app.quit)
        #QtCore.QObject.connect(
        #    action_translate, QtCore.SIGNAL("triggered()"),
        #    self.translateClipboard)
        #QtCore.QObject.connect(
        #    action_configure, QtCore.SIGNAL("triggered()"),
        #    self.configure)
        QtCore.QObject.connect(self,
            QtCore.SIGNAL("activated(QSystemTrayIcon::ActivationReason)"),
            self.showOrHideUi)

        self.setContextMenu(self.menu)

    def translateClipboard(self):
        cb = QtGui.QApplication.clipboard()
        keyword = cb.text(cb.Selection).toLower()
        #TODO: get result

    def configure(self):
        #TODO: Configuration window
        pass

    def showOrHideUi(self, activationReason):
        if activationReason == self.Trigger:
            self.settings.setValue("tray/startHidden",
                QtCore.QVariant(self.ui.isVisible()))
            self.ui.setVisible(not self.ui.isVisible())
            debugger.debug(
                "Clicked tray icon, visible = %s" % str(self.ui.isVisible()))
