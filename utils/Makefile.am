# -*- Mode: Makefile -*-
#
# Makefile.am - automake file for Redland++ utils
#
# Copyright (C) 2008, David Beckett http://www.dajobe.org/
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

bin_PROGRAMS = rdfprocpp

AM_CPPFLAGS = -DREDLANDPP_INTERNAL @REDLAND_CFLAGS@ -I$(top_srcdir)/src 

rdfprocpp_SOURCES = rdfprocpp.cc
rdfprocpp_LDADD= $(top_builddir)/src/libredlandpp.la

$(top_builddir)/src/libredlandpp.la:
	cd $(top_builddir)/src && $(MAKE) libredlandpp.la
