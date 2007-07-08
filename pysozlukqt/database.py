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

"""pysozluk database api"""

from PyQt4 import QtCore
from pysqlite2 import dbapi2 as sqlite
import pysozlukglobals

class Translation:
    """Holds translation information of a word"""
    def __init__(self, inittext):
        self.lang, self.word, self.text = inittext

class pysozlukDatabase(QtCore.QObject):
    """This class provides some methods to search words and read a pysozluk database file"""

    def __init__(self, databaseFile = pysozlukglobals.database):
        """Initialise database"""
        QtCore.QObject.__init__(self)
        self.readDatabase(databaseFile)

    def search(self, keyword, dicts = "all", threaded = True):
        """Search given keyword

        keyword is a string,
        dicts is a list of dictionary indexes to search in,
        if threaded is True emits "found" signal with translations
        if not, just returns translations
        """
        if dicts == "all":
            dicts = []
            for dict in self.languages:
                dicts.append(dict[0])

        query = "select home, word, text from translations where word = ?"
        dictlist = ""
        if dicts:
            dictlist += " and ("
        i=0
        while i < len(dicts):
            dictlist += " home = %d" % dicts[i]
            if i != len(dicts) - 1:
                dictlist += " or"
            i+=1
        if dicts:
            dictlist += " )"
        cur = self.con.cursor()

        cur.execute(query, (keyword,))
        result = cur.fetchall()
        results = []
        for i in result:
            results.append(Translation(i))
        if threaded:
            self.emit(QtCore.SIGNAL("found"), results)
        else:
            return results

    def readDatabase(self, databaseFile):
        """Reads dictionary information from given database"""
        self.con = sqlite.connect(databaseFile)
        cur = self.con.cursor()

        query = "select id, englishname, nativename from languages"
        cur.execute(query)
        self.languages = cur.fetchall()
