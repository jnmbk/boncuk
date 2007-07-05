# -*- coding: utf-8 -*-
#
# Copyright (C) 2007, pysozluk-qt Development Team
#
# This program is free software; you can redistribute it and/or modify it under
# the terms of the GNU General Public License as published by the Free
# Software Foundation; either version 2 of the License, or (at your option)
# any later version.
#
# Please read the COPYING file.
#

import sys
import locale
from PyQt4 import QtCore, QtGui, uic
from core import pysozlukCore
from gettext import translation
import pysozlukglobals

locale.setlocale(locale.LC_ALL, "C")
_ = translation('pysozluk-qt', fallback=True).ugettext


def main():
    app = QtGui.QApplication(sys.argv)
    app.setOrganizationName("pysozluk-qt")
    app.setApplicationName("pysozluk-qt")
    settings = QtCore.QSettings()
    formclass = uic.loadUiType(pysozlukglobals.mainWindowFileName)[0]

    class mainWindow(formclass):
        parent = None

        def retranslateUi(self, mw):
            self.label.setText(_("Keyword:"))
            self.pushButton.setText(_("&Search"))
            self.menuFile.setTitle(_("&File"))
            self.menuMode.setTitle(_("&Mode"))
            self.menuHelp.setTitle(_("&Help"))
            self.actionAbout_Pysozluk_Qt.setText(_("About &Pysozluk-Qt"))
            self.actionAbout_Qt.setText(_("About &Qt"))
            self.actionOffline.setText(_("&Offline"))
            self.actionSave.setText(_("&Save"))
            self.actionQuit.setText(_("&Quit"))
        def makeConnections(self, core):
            QtCore.QObject.connect(self.actionAbout_Pysozluk_Qt,QtCore.SIGNAL("activated()"),core.about)
            QtCore.QObject.connect(self.actionAbout_Qt,QtCore.SIGNAL("activated()"),core.aboutQt)
            QtCore.QObject.connect(self.actionOffline,QtCore.SIGNAL("activated()"),core.toggleOffline)
            QtCore.QObject.connect(self.actionQuit,QtCore.SIGNAL("activated()"),core.quitApp)
            QtCore.QObject.connect(self.parent, QtCore.SIGNAL("destroyed"), core.quitApp)
            QtCore.QObject.connect(self.actionSave,QtCore.SIGNAL("activated()"),core.save)
            QtCore.QObject.connect(self.pushButton,QtCore.SIGNAL("clicked()"),core.search)
            QtCore.QObject.connect(self.lineEdit,QtCore.SIGNAL("returnPressed()"),core.search)

    ui = mainWindow()
    ui.parent = QtGui.QMainWindow()
    ui.setupUi(ui.parent)
    #import pycallgraph
    #pycallgraph.start_trace()
    core = pysozlukCore(ui)
    ui.makeConnections(core)
    ui.parent.setWindowTitle(_("Pysozluk-Qt"))
    if settings.contains("windowposition"):
        ui.move(settings.value("windowposition").toPoint())
    ui.parent.show()
    #app.exec_()
    #pycallgraph.stop_trace()
    #pycallgraph.make_dot_graph('pysozluk-qt.png')
    sys.exit(app.exec_())

if __name__ == "__main__":
    main()
