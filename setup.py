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
import shutil
from distutils.core import setup
from distutils.command.build import build
from distutils.command.clean import clean

def getVersion():
    import pysozlukqt.pysozlukglobals
    return pysozlukqt.pysozlukglobals.version

class myBuild(build):
    def run(self):
        build.run(self)
        #TODO: Don't hardcode this
        os.system("lrelease-qt4 pysozlukqt/translations/pysozluk-qt_tr_TR.ts"
            " -qm pysozlukqt/translations/pysozluk-qt_tr_TR.qm")

class myClean(clean):
    def run(self):
        clean.run(self)
        os.remove("pysozlukqt/translations/pysozluk-qt_tr_TR.qm")

setup(name = "pysozluk-qt",
      version = getVersion(),
      description = "Online/offline dictionary",
      long_description = "pysozluk is a lightweight online/offline dictionary "
          "application written in Python with tkinter GUI. This port of "
          "pysozluk looks better than the original (thanks Qt) and is much "
          "faster.",
      license = "GNU General Public License, Version 2",
      author = "pysozluk-qt developers",
      author_email = "pysozluk-qt@googlegroups.com",
      url = "http://pysozluk-qt.wiki.sourceforge.net",
      download_url =
          "http://sourceforge.net/project/showfiles.php?group_id=200295",
      packages = ["pysozlukqt"],
      package_data = {"pysozlukqt": [
          "data/icons/16x16/*",
          "data/icons/32x32/*",
          "data/icons/64x64/*",
          "data/icons/128x128/*",
          "data/pysozluk-qt.svg",
          "translations/*.qm"]},
      data_files = [
          ("share/applications", ["pysozlukqt/data/pysozluk-qt.desktop"]),
          ("share/icons/hicolor/scalable/apps",
          ["pysozlukqt/data/pysozluk-qt.svg"])],
      scripts = ["scripts/pysozluk-qt"],
      platforms = ["all"],
      cmdclass = {"build" : myBuild,
                  "clean" : myClean}
      )
