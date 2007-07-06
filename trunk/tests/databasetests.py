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

import pysozlukqt.database

import unittest

class databaseTestCase(unittest.TestCase):
    def testSearch(self):
        keywords = ('tavşan', 'sinek', 'aslf', 'aşsdaüğ', 'ağaç')
        db = pysozlukqt.database.pysozlukDatabase(databaseFile = "/usr/share/pysozluk-qt/pysozluk.db")
        for keyword in keywords:
            translations = db.search(keyword, threaded = False)
            for translation in translations:
                self.assert_(type(translation.text) == type(unicode()))

suite = unittest.makeSuite(databaseTestCase)
unittest.TextTestRunner(verbosity=2).run(suite)
