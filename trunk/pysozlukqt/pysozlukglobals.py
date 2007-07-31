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

import os

#directories
dataDirectory = "/usr/share/pysozluk-qt"

#file names
databaseFileName = "pysozluk-qt.db"
mainWindowFileName = os.path.join(dataDirectory, "mainWindow.ui")

#absolute paths
database = os.path.join(dataDirectory, databaseFileName)
#icons
#TODO: We should fix this mess, there are two ways to get rid of it
# 1. (very dirty) Assume that person is using KDE, and use KDE 3.5 api to find
#    the current icon directory
# 2. Include Tulliana-2.0 icon set with pysozluk-qt
#TODO: We sholud compile the svg icon to pngs, otherwise pisi package lacks icon
iconPath = "/usr/share/icons/Tulliana-2.0/16x16"
icon_main = "/usr/share/icons/hicolor/scalable/apps/pysozluk-qt.svg"
icon_translate = os.path.join(iconPath, "apps/locale.png")
icon_configure = os.path.join(iconPath, "actions/configure.png")
icon_exit = os.path.join(iconPath, "actions/exit.png")
#other
version = "0.1"

updateServer = 'http://ish.kodzilla.org/pyqtsozluk/'
