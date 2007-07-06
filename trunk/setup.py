# -*- coding: utf-8 -*-
#
# pysozluk-qt, Qt port of pysozluk (online/offline dictionary)
# Copyright (C) 2007, pysozluk-qt Development Team
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

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
