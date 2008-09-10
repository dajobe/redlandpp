# -*- Mode: Makefile -*-
#
# Makefile.am - automake file for raptor++
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


pkginclude_HEADERS = \
Raptor.hh \
RaptorWorld.hh \
RaptorException.hh \
RaptorParser.hh \
RaptorParserDescriptor.hh \
RaptorTriple.hh \
RaptorUri.hh

AM_CXXFLAGS = -DREDLANDPP_INTERNAL @REDLAND_CFLAGS@
AM_LDFLAGS = @REDLAND_LIBS@ -version-info @REDLANDPP_LIBTOOL_VERSION@

lib_LTLIBRARIES = libredlandpp.la

libredlandpp_la_SOURCES = \
RaptorWorld.cc \
RaptorException.cc \
RaptorParser.cc \
RaptorParserDescriptor.cc \
RaptorTriple.cc \
RaptorUri.cc

