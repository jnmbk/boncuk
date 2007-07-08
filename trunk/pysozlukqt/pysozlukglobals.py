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

#other
version = "0.1"

updateServer = 'http://ish.kodzilla.org/pyqtsozluk/'