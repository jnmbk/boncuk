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

from PyQt4 import QtCore, QtNetwork
from database import Translation
from HTMLParser import HTMLParser
import urllib

def convertToTurkishWeb(word):
    turkishCharacters = ((u"ı","%%FD"), (u"İ","%%DD"), (u"ö","%%F6"),
                         (u"Ö","%%D6"), (u"ç","%%E7"), (u"Ç","%%C7"),
                         (u"ş","%%FE"), (u"Ş","%%DE"), (u"ğ","%%F0"),
                         (u"Ğ","%%D0"), (u"ü","%%FC"), (u"Ü","%%DC"))
    for change in turkishCharacters:
        word = word.replace(change[0], change[1])
    return word

class sesliSozlukParser(HTMLParser):
    def reset(self):
        HTMLParser.reset(self)
        self.data = []
        self.traslationTableStarted = False
    def handle_starttag(self, tag, attrs):
        if tag == "table" and\
           (u"class", u"double_click_zone") in attrs:
            self.traslationTableStarted = True
    def handle_data(self, data):
        if self.traslationTableStarted:
            self.data.append(unicode(data, "cp1254", errors="ignore"))
    def handle_endtag(self, tag):
        if self.traslationTableStarted and tag == "table":
            self.traslationTableStarted = False

class onlineDatabase(QtNetwork.QHttp):
    def __init__(self):
        QtNetwork.QHttp.__init__(self)
        self.setHost("www.seslisozluk.com")
        QtCore.QObject.connect(self,
                               QtCore.SIGNAL("requestFinished(int, bool)"),
                               self.continueSearch)

    def search(self, keyword, dicts = "all", threaded = True):
        self.keyword = convertToTurkishWeb(keyword)
        if threaded:
            self.get("/?word=%s" % self.keyword)
        else:
            text = urllib.urlopen("http://www.seslisozluk.com/?word=%s" % self.keyword).read()
            return self.parse(text, threaded = False)

    def continueSearch(self, id, error):
        if self.hasPendingRequests():
            return
        self.parse(str(self.readAll()))

    def parse(self, text, threaded = True):
        parser = sesliSozlukParser()
        parser.feed(text.replace("<link", "")) #remove stupid error caused by javascript
        parser.close()
        tr = parser.data.index("Turkish Translation")
        en = parser.data.index("English Translation")
        langs = [tr,en]

        try:
            de = parser.data.index("German Translation")
        except:
            pass
        else:
            langs.append(de)
        langs.sort()

        ix_tr, ix_en = langs.index(tr), langs.index(en)
        turkish = parser.data[tr+1:self.index(langs, ix_tr)]
        english = parser.data[en+1:self.index(langs, ix_en)]

        turkish = self.pick(self.keyword, turkish, 0)
        english = self.pick(self.keyword, english, 1)

        if threaded:
            self.emit(QtCore.SIGNAL("found"), turkish + english)
        else:
            return turkish + english

    def pick(self, keyword, lang, home):
        translations = []
        try:
            lang.index(u"1.")
        except:
            lang = []
        else:
            lang = lang[lang.index(u"1."):]

        for n in lang:
            try:
                int(n[:n.rfind(u".")])
            except:
                if n != " ":
                    translations.append(Translation((home, keyword, n)))
        return translations

    def index(self, array, index):
        if index != len(array)-1:
            return array[index+1]
        else:
            return None

