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

from PyQt4 import QtGui, QtCore
import gettext
import pysozlukglobals

_ = gettext.translation('pysozluk-qt', fallback=True).ugettext

class PySozlukTrayIcon(QtGui.QSystemTrayIcon):
    def __init__(self, ui, app):
        QtGui.QSystemTrayIcon.__init__(
            self, QtGui.QIcon(pysozlukglobals.icon_main))
        self.ui = ui
        action_translate = QtGui.QAction(
            QtGui.QIcon(pysozlukglobals.icon_translate),
            _("Translate Clipboard"), self)
        action_configure = QtGui.QAction(
            QtGui.QIcon(pysozlukglobals.icon_configure),
            _("Configure PySozluk-Qt"), self)
        action_exit = QtGui.QAction(
            QtGui.QIcon(pysozlukglobals.icon_exit),
            _("Exit"), self)

        self.menu = QtGui.QMenu()
        self.menu.addAction(action_translate)
        self.menu.addSeparator()
        self.menu.addAction(action_configure)
        self.menu.addSeparator()
        self.menu.addAction(action_exit)

        QtCore.QObject.connect(
            action_exit, QtCore.SIGNAL("triggered()"), app.quit)
        QtCore.QObject.connect(
            action_translate, QtCore.SIGNAL("triggered()"),
            self.translateClipboard)
        QtCore.QObject.connect(self,
            QtCore.SIGNAL("activated(QSystemTrayIcon::ActivationReason)"),
            self.showOrHideUi)

        self.setContextMenu(self.menu)

    def translateClipboard(self):
        cb = QtGui.QApplication.clipboard()
        keyword = cb.text(cb.Selection).toLower()
        #TODO: get result

    def showOrHideUi(self, activationReason):
        if activationReason == self.Trigger:
            self.ui.setVisible(not self.ui.isVisible())
