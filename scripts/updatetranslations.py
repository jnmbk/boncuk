#!/usr/bin/python
# -*- coding: utf-8 -*-

import os

directory = "pysozlukqt"

translateables = ("__init__.py",
        "core.py",
        "mainWindow.py",
        "configWindow.py",
        "trayicon.py")

command = "pylupdate4 "
for file in translateables:
    command += os.path.join(directory, file) + " "
os.system(command + "-ts %s -verbose" % os.path.join(directory, "translations",
    "pysozluk-qt_tr_TR.ts"))
