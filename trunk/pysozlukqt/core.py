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
import os

from database import pysozlukDatabase
from online import onlineDatabase
import config
import pysozlukglobals

class searcherThread(QtCore.QThread):
    def __init__(self, keyword, settings):
        QtCore.QThread.__init__(self)
        self.keyword = keyword
        self.settings = settings

    def run(self):
        if self.settings.value("offline", QtCore.QVariant(False)).toBool():
            self.database = pysozlukDatabase()
        else:
            self.database = onlineDatabase()
        QtCore.QObject.connect(self.database, QtCore.SIGNAL("found"),
            self.formatTranslation)
        self.database.search(self.keyword)
        self.exec_()

    def formatTranslation(self, translation):
        turkish = []
        english = []
        tr = "<b>%s</b><br>" % QtGui.QApplication.translate("MainWindow",
                "Turkish translation of %s") % self.keyword
        en = "<b>%s</b><br>" % QtGui.QApplication.translate("MainWindow",
                "English translation of %s") % self.keyword
        result = ""

        if translation:
            for var in translation:
                if var.lang == 1 and not var.text in english:
                    english.append(var.text)
                elif var.lang == 0 and not var.text in turkish:
                    turkish.append(var.text)
            if turkish:
                for text in turkish:
                    tr += "%d. %s<br>" % (turkish.index(text)+1, text)
                tr += "<br>"
                result += tr

            if english:
                for text in english:
                    en += "%d. %s<br>" % (english.index(text)+1, text)
                result += en
            self.sendResult(result)
        else:
            self.sendResult(
                "<b>%s</b>" % QtGui.QApplication.translate("MainWindow",
                    "Cannot find \"%s\"") % self.keyword)

    def sendResult(self, result):
        self.emit(QtCore.SIGNAL("finishedSearching"), result)


class pysozlukCore:
    def __init__(self, ui):
        self.ui = ui
        self.settings = QtCore.QSettings()
        self.ui.actionOffline.setChecked(
            self.settings.value("offline", QtCore.QVariant(False)).toBool())
        self.searcherThread = None

    def search(self):
        #TODO: This should display country flags
        keyword = unicode(self.ui.lineEdit.text())
        if self.searcherThread and self.searcherThread.isRunning():
            self.searcherThread.terminate()
        self.searcherThread = searcherThread(keyword, self.settings)
        self.ui.textBrowser.clearHistory()
        self.ui.textBrowser.setHtml(
            "<b>%s</b>" % QtGui.QApplication.translate(
                "searching \"%s\"") % keyword)
        QtCore.QObject.connect(self.searcherThread,
            QtCore.SIGNAL("finishedSearching"),
            self.ui.textBrowser.setHtml)
        self.searcherThread.start()

    def about(self):
        QtGui.QMessageBox.about(self.ui,
            QtGui.QApplication.translate("AboutWindow", "About Pysozluk-Qt"),
            "Pysozluk-Qt v%s\n" % pysozlukglobals.version +\
            "http://pysozluk-qt.wiki.sourceforge.net\n\n" +\
            QtGui.QApplication.translate("AboutWindow", "Developers:") + "\n"+\
            u"İlker Kesen <ilker.kde at gmail.com>" + "\n" +\
            u"İşbaran Akçayır <isbaran at gmail.com>" + "\n" +\
            u"Uğur Çetin <ugur.jnmbk at gmail.com>")

    def aboutQt(self):
        QtGui.QMessageBox.aboutQt(self.ui)

    def toggleOffline(self):
        self.settings.setValue("offline",
            QtCore.QVariant(self.ui.actionOffline.isChecked()))

    def save(self):
        if not self.ui.textBrowser.toPlainText():
            QtGui.QMessageBox.warning(self.ui,
                QtGui.QApplication.translate("MainWindow", "Warning"),
                QtGui.QApplication.translate("MainWindow",
                    "If you want to save a description,"
                    " you must search a keyword."))
        else:
            #TODO: Add HTML and Plain Text file filters
            file_path = QtGui.QFileDialog.getSaveFileName(
                self.ui, QtGui.QApplication.translate("MainWindow", "Save"),
                os.getenv("HOME"), "All Files (*)")
            if file_path:
                if str(file_path).endswith(".html"):
                    description = self.ui.textBrowser.toHtml()
                else:
                    description = self.ui.textBrowser.toPlainText()

                file = open(str(file_path), "w")
                file.write(unicode(description) + "\n")
                file.close()

    def configure(self):
        configUi = config.ConfigWindow(self.ui)
        configUi.show()
