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

"""pysozluk database api"""

from PyQt4 import QtCore, QtSql
import pysozlukglobals

class Language:
    tr, en = range(2)

class Translation:
    """Holds translation information of a word"""
    def __init__(self, inittext):
        self.lang, self.word, self.text = inittext

class pysozlukDatabase(QtCore.QObject):
    """This class provides some methods to search words
    and read a pysozluk database file"""

    def __init__(self, databaseFile = pysozlukglobals.database):
        """Initialise database"""
        QtCore.QObject.__init__(self)
        db = QtSql.QSqlDatabase.database()
        if not db.isValid():
            db = QtSql.QSqlDatabase.addDatabase("QSQLITE")
            db.setDatabaseName(databaseFile)
            db.open()

    def search(self, keyword, threaded = True):
        """Search given keyword

        keyword is a string,
        if threaded is True emits "found" signal with translations
        if not, just returns translations
        """

        query = QtSql.QSqlQuery()
        query.prepare(
            "SELECT home, word, text FROM translations WHERE word = :keyword")
        query.bindValue(":keyword", QtCore.QVariant(keyword))
        query.exec_()
        results = []
        while(query.next()):
            results.append(Translation((
                query.value(0).toInt()[0],
                query.value(1).toString(),
                query.value(2).toString())))
        if threaded:
            self.emit(QtCore.SIGNAL("found"), results)
        else:
            return results
