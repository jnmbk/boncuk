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
import pysozlukglobals

class PySozlukTrayIcon(QtGui.QSystemTrayIcon):
    def __init__(self, ui):
        QtGui.QSystemTrayIcon.__init__(self, QtGui.QIcon(pysozlukglobals.icon))
        self.ui = ui
        
