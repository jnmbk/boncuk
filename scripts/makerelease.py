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

import os, sys

appName = "pysozluk-qt"
helpText = """
    Automated distribution maker for %s

      usage: python trunk/scripts/makerelease.py <srcVersion>
    example: python trunk/scripts/makerelease.py 0.1_alpha1
    
    Note: You must run this script from svn root""" % (appName)

def tagandtar(srcVersion):
    srcTag = "%s-%s" % (appName, srcVersion)
    print "Tagging trunk"
    os.system("svn cp -q trunk tags/%s" % srcTag)
    print "Exporting tag"
    os.system("svn export -q tags/%s %s" % (srcTag, srcTag))
    print "Compressing"
    os.system("tar jcf %s.tar.bz2 %s" % (srcTag, srcTag))
    #TODO: make other distribution packages here
    print "Cleaning"
    os.system("rm -fr %s" % srcTag)
    print "We're ready for release now"

if __name__ == "__main__":
    try:
        tagandtar(sys.argv[1])
    except IndexError:
        print helpText
        sys.exit(1)
