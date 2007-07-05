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
