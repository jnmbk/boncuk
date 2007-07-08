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
from distutils.core import setup

def getVersion():
    import pysozlukqt.pysozlukglobals
    return pysozlukqt.pysozlukglobals.version

#compile translations
locales = []
translations = ["tr"]
for i in translations:
    try:
        os.mkdir("po/%s" %  i)
    except:
        pass
    os.system("msgfmt po/%s.po -o po/%s/pysozluk-qt.mo" % (i, i))
    locales.append(('share/locale/%s/LC_MESSAGES' % i,
                    ['po/%s/pysozluk-qt.mo' % i]))

#extract database
if not os.path.exists("data/pysozluk-qt.db"):
    os.system("tar xjf data/pysozluk-qt.db.bz2 -C data/")

datas = [('share/pysozluk-qt',                 ['data/pysozluk-qt.db']),
         ('share/applications',                ['data/pysozluk-qt.desktop']),
         ('share/icons/hicolor/scalable/apps', ['data/pysozluk-qt.svg']),
         ('share/pysozluk-qt/flags',           ['data/en.gif', 'data/tr.gif']),
         ('share/pysozluk-qt',                 ['pysozlukqt/mainWindow.ui'])]
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
      data_files = datas,
      scripts = ['scripts/pysozluk-qt'],
      )
