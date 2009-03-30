# -*- Mode: Makefile -*-
#
# Makefile.am - top level automake file for raptorpp
#
# Copyright (C) 2008 David Beckett http://www.dajobe.org/
# 
# This package is Free Software and part of Redland http://librdf.org/
# 
# It is licensed under the following three licenses as alternatives:
#   1. GNU Lesser General Public License (LGPL) V2.1 or any newer version
#   2. GNU General Public License (GPL) V2 or any newer version
#   3. Apache License, V2.0 or any newer version
# 
# You may not use this file except in compliance with at least one of
# the above three licenses.
# 
# See LICENSE.html or LICENSE.txt at the top of this package for the
# complete terms and further detail along with the license texts for
# the licenses in COPYING.LIB, COPYING and LICENSE-2.0.txt respectively.
# 
# 

SUBDIRS= src redlandpp utils

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = redlandpp.pc


EXTRA_DIST=\
ChangeLog \
NEWS \
autogen.sh \
redlandpp.pc.in

# Some people need a little help ;-)
test: check

dist-hook: NEWS
	@for file in README NEWS; do \
          if test -r $(srcdir)/$$file; then \
	    rm -f $(distdir)/$$file; \
	    cp -p $(srcdir)/$$file $(distdir)/$$file; \
	  fi; \
	done
