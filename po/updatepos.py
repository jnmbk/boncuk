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

os.system("xgettext --add-comments"
       " --no-wrap --files-from=app.fil"
       " --language=Python --output=pysozluk-qt.pot")
for lang in ["tr"]:
    os.system("msgmerge --backup=off -U %s.po pysozluk-qt.pot" % lang)
