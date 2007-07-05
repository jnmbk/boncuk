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

import os
from distutils.core import setup

#compile translations
locales = []
translations = ["tr"]
for i in translations:
    try:
        os.mkdir("po/%s" %  i)
    except:
        pass
    os.system("msgfmt po/%s.po -o po/%s/pysozluk-qt.mo" % (i, i))
    locales.append(('share/locale/%s/LC_MESSAGES' % i, ['po/%s/pysozluk-qt.mo' % i]))

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
      version = "0.1",
      description = "Online/offline Turkish<->English dictionary.",
      license = "GNU General Public License, Version 2",
      author = "pysozluk-qt developers",
      author_email = "pysozluk-qt@googlegroups.com",
      url = "http://code.google.com/p/pysozluk-qt",
      packages = ["pysozlukqt"],
      data_files = datas,
      scripts = ['scripts/pysozluk-qt']
      )
