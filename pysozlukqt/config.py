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

import configWindow

class ConfigWindow(QtGui.QDialog, configWindow.Ui_ConfigWindow):
    def __init__(self, parent=None):
        QtGui.QDialog.__init__(self, parent)
        self.setupUi(self)

        QtCore.QObject.connect(self, QtCore.SIGNAL("accepted()"),
            self.writeSettings)
        settings = QtCore.QSettings()

        self.translation_method.setCurrentIndex(settings.value(
            "translation/method", QtCore.QVariant(0)).toInt()[0])
        if settings.value("tray/enabled", QtCore.QVariant(True)).toBool():
            self.trayIcon_enable.setCheckState(QtCore.Qt.Checked)
        else:
            self.trayIcon_enable.setCheckState(QtCore.Qt.Unchecked)
        if settings.value("tray/minimizeonclose",
                QtCore.QVariant(True)).toBool():
            self.trayIcon_minimizeOnClose.setCheckState(QtCore.Qt.Checked)
        else:
            self.trayIcon_minimizeOnClose.setCheckState(QtCore.Qt.Unchecked)
        if settings.value("tray/rememberlaststate",
            QtCore.QVariant(True)).toBool():
            self.trayIcon_rememberLast.setCheckState(QtCore.Qt.Checked)
        else:
            self.trayIcon_rememberLast.setCheckState(QtCore.Qt.Unchecked)
        self.advanced_debugLevel.setValue(settings.value(
            "debuglevel", QtCore.QVariant(2)).toInt()[0])

    def writeSettings(self):
        settings = QtCore.QSettings()
        settings.setValue("translation/method",
            QtCore.QVariant(self.translation_method.currentIndex()))
        settings.setValue("tray/enabled",
            QtCore.QVariant(bool(self.trayIcon_enable.checkState())))
        settings.setValue("tray/minimizeonclose",
            QtCore.QVariant(bool(self.trayIcon_minimizeOnClose.checkState())))
        settings.setValue("tray/rememberlaststate",
            QtCore.QVariant(bool(self.trayIcon_rememberLast.checkState())))
        settings.setValue("debuglevel",
            QtCore.QVariant(self.advanced_debugLevel.value()))
