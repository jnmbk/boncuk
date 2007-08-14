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
from debugger import Debugger

debugger = Debugger()

#directories
dataDirectory = "data"

#absolute paths
database = os.path.join(dataDirectory, "pysozluk-qt.db")

#icons
iconDir = os.path.join(dataDirectory, "icons")
iconSize = {"small":"16x16", "medium":"32x32", "big":"64x64", "huge":"128x128"}
def getIcon(iconName, size="small"):
    debugger.debug("requested icon: %s, size: %s" %  (iconName, size))
    try:
        size = iconSize[size]
    except KeyError:
        debugger.critical(
            "icon size isn't valid. Valid sizes are:%s" % str(iconSize))
        return None
    iconFile = os.path.join(iconDir, size, iconName + ".png")
    if not os.path.exists(iconFile):
        debugger.critical("icon doesn't exist")
    return iconFile

#other
version = "0.2_beta1"

updateServer = 'http://ish.kodzilla.org/pyqtsozluk/'
