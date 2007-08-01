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
from distutils.command.install import install

def getTranslations():
    return ("tr",)

def getVersion():
    import pysozlukqt.pysozlukglobals
    return pysozlukqt.pysozlukglobals.version

def compileTranslations():
    for i in getTranslations():
        try:
            os.mkdir("po/%s" %  i)
        except OSError:
            pass
        os.system("msgfmt po/%s.po -o po/%s/pysozluk-qt.mo" % (i, i))

class myBuild(build):
    def run(self):
        build.run(self)
        compileTranslations()

class myClean(clean):
    def run(self):
        clean.run(self)
        dirList = os.listdir("po")
        for dir in dirList:
            if os.path.isdir(os.path.join("po", dir)) and dir != ".svn":
                shutil.rmtree(os.path.join("po", dir), ignore_errors = True)

        dirList = ("build",)
        for dir in dirList:
            if os.path.exists(dir):
                shutil.rmtree(dir)

locales = []
for i in getTranslations():
    locales.append(("share/locale/%s/LC_MESSAGES" % i,
            ["po/%s/pysozluk-qt.mo" % i]))

datas = [("share/applications",                ["pysozlukqt/data/pysozluk-qt.desktop"]),
         ("share/icons/hicolor/scalable/apps", ["pysozlukqt/data/pysozluk-qt.svg"])]
datas.extend(locales)

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
          "data/ui/*",
          "data/icons/16x16/*",
          "data/icons/32x32/*",
          "data/icons/64x64/*",
          "data/icons/128x128/*",]},
      data_files = datas,
      scripts = ["scripts/pysozluk-qt"],
      platforms = ["all"],
      cmdclass = {"build" : myBuild,
                  "clean" : myClean}
      )
