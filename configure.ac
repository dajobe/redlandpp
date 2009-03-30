dnl -*- Mode: autoconf -*-
dnl
dnl configure.ac - autoconf file for Redland++
dnl (Process this file with autoconf to produce a configure script.)
dnl
dnl Copyright (C) 2008 David Beckett http://www.dajobe.org/
dnl 
dnl This package is Free Software and part of Redland http://librdf.org/
dnl 
dnl It is licensed under the following three licenses as alternatives:
dnl   1. GNU Lesser General Public License (LGPL) V2.1 or any newer version
dnl   2. GNU General Public License (GPL) V2 or any newer version
dnl   3. Apache License, V2.0 or any newer version
dnl 
dnl You may not use this file except in compliance with at least one of
dnl the above three licenses.
dnl 
dnl See LICENSE.html or LICENSE.txt at the top of this package for the
dnl complete terms and further detail along with the license texts for
dnl the licenses in COPYING.LIB, COPYING and LICENSE-2.0.txt respectively.
dnl 
dnl 


AC_INIT(Redland++, 0.1.0, http://bugs.librdf.org/, redlandpp)
AC_PREREQ(2.50)
AC_CONFIG_SRCDIR(src/Redland.cpp)
AC_CONFIG_SRCDIR(redlandpp/Redland.hpp)

AM_INIT_AUTOMAKE([1.7 check-news std-options -Wall])
AM_CONFIG_HEADER(src/redlandpp_config.h)
AM_MAINTAINER_MODE

release_version=no
AC_ARG_ENABLE(release, [  --enable-release        Turn on optimizations (for maintainer).  ], \
 if test "$enableval" = "yes"; then \
	  release_version=yes
fi;)	

AM_CONDITIONAL(RELEASE_VERSION, test $release_version = yes)
if test "$USE_MAINTAINER_MODE" = yes -a $release_version = no; then 
  CFLAGS=`echo $CFLAGS | sed -e "s/-O[A-Za-z0-9]*//"`
  CXXFLAGS=`echo $CXXFLAGS | sed -e "s/-O[A-Za-z0-9]*//"`
  CPPFLAGS=`echo $CPPFLAGS | sed -e "s/-O[A-Za-z0-9]*//"`
fi


dnl Checks for programs.
AC_CANONICAL_HOST
AM_SANITY_CHECK

AC_LANG([C++])

AC_PROG_CXX

m4_undefine([AC_PROG_F77])
m4_defun([AC_PROG_F77],[])
AC_PROG_LIBTOOL
AC_PROG_INSTALL

# Find a tar command for 'make dist'
AC_CHECK_PROGS(TAR, gnutar gtar tar)
AC_CHECK_PROGS(PERL, perl)
AC_CHECK_PROGS(PKG_CONFIG, pkg-config)

AM_MISSING_PROG(ACLOCAL, aclocal, $missing_dir)
AM_MISSING_PROG(AUTOCONF, autoconf, $missing_dir)
AM_MISSING_PROG(AUTOMAKE, automake, $missing_dir)
AM_MISSING_PROG(AUTOHEADER, autoheader, $missing_dir)


dnl compiler checks

AC_DEFUN([REDLAND_CXX_TRY_FLAG], [
  AC_MSG_CHECKING([whether $CXX supports $1])
  redland_save_CXXFLAGS="$CXXFLAGS"
  CXXFLAGS="$CXXFLAGS $1"
  AC_COMPILE_IFELSE([ ], [redland_cxx_flag=yes], [redland_cxx_flag=no])
  CXXFLAGS="$redland_save_CXXFLAGS"
  if test "X$redland_cxx_flag" = "Xyes"; then
    ifelse([$2], , :, [$2])
  else
    ifelse([$3], , :, [$3])
  fi
  AC_MSG_RESULT($redland_cxx_flag)
])

possible_warnings="-Wall -Wextra \
-Wshadow -Wpointer-arith -Wredundant-decls -Wswitch-enum \
-Wsign-compare -Wwrite-strings \
-Wpacked -Wmissing-format-attribute -Wpointer-arith -Wcast-align -Winit-self \
-Wunsafe-loop-optimizations \
-Wno-missing-field-initializers -Wno-unused-parameter \
-Wformat-security \
-Woverloaded-virtual"

warning_cflags=
if test "$USE_MAINTAINER_MODE" = yes; then
  AC_MSG_CHECKING(for supported $CXX warning flags)
  AC_MSG_RESULT($warning_cflags)
  for warning in $possible_warnings; do
    REDLAND_CXX_TRY_FLAG([$warning], [warning_cflags="$warning_cflags $warning"])
  done
  AC_MSG_CHECKING($CXX supports warning flags)
  AC_MSG_RESULT($warning_cflags)
fi

dnl Checks for libraries.
REDLAND_MIN_VERSION=1.0.8
if $PKG_CONFIG redland --exists; then
  :
else
  AC_MSG_ERROR(Redland is not installed - see http://librdf.org/ to get a version newer than $REDLAND_MIN_VERSION)
fi

REDLAND_VERSION=`$PKG_CONFIG redland --modversion 2>/dev/null`
if $PKG_CONFIG redland --atleast-version=$REDLAND_MIN_VERSION; then
  :
else
  AC_MSG_ERROR(Installed redland $REDLAND_VERSION is too old - need $REDLAND_MIN_VERSION)
fi

REDLAND_CFLAGS="`$PKG_CONFIG redland --cflags` $LIBRDF_EXTERNAL_CPPFLAGS"
REDLAND_LIBS="`$PKG_CONFIG redland --libs` $LIBRDF_EXTERNAL_LIBS"
AC_SUBST(REDLAND_CFLAGS)
AC_SUBST(REDLAND_LIBS)


dnl Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS(redland.h)

dnl Checks for typedefs, structures, and compiler characteristics.

dnl need to change quotes to allow square brackets
changequote(<<, >>)dnl
version_major=`echo $VERSION | sed -e 's/^\([^\.]*\)\.\([^\.]*\)\.\(.*\)$/\1/'`
version_minor=`echo $VERSION | sed -e 's/^\([^\.]*\)\.\([^\.]*\)\.\(.*\)$/\2/'`
version_release=`echo $VERSION | sed -e 's/^\([^\.]*\)\.\([^\.]*\)\.\(.*\)$/\3/'`
changequote([, ])dnl

version_decimal=`expr $version_major \* 10000 + $version_minor \* 100 + $version_release`

AC_DEFINE_UNQUOTED(REDLANDPP_VERSION_MAJOR, $version_major, [Major version number])
AC_DEFINE_UNQUOTED(REDLANDPP_VERSION_MINOR, $version_minor, [Minor version number])
AC_DEFINE_UNQUOTED(REDLANDPP_VERSION_RELEASE, $version_release, [Release version number])
AC_DEFINE_UNQUOTED(REDLANDPP_VERSION_DECIMAL, $version_decimal, [Release version as a decimal])


# Libtool versioning
#
# CURRENT
#      The most recent interface number that this library implements.
# 
# REVISION
#      The implementation number of the CURRENT interface.
# 
# AGE
#      The difference between the newest and oldest interfaces that this
#      library implements.  In other words, the library implements all the
#      interface numbers in the range from number `CURRENT - AGE' to
#      `CURRENT'.
#
# Rules:
#  1. Start with version information of `0:0:0' for each libtool library.
#
#  2. Update the version information only immediately before a public
#     release of your software.  More frequent updates are unnecessary,
#     and only guarantee that the current interface number gets larger
#     faster.
#
#  3. If the library source code has changed at all since the last
#     update, then increment REVISION (`C:R:A' becomes `C:r+1:A').
#
#  4. If any interfaces have been added, removed, or changed since the
#     last update, increment CURRENT, and set REVISION to 0.
#
#  5. If any interfaces have been added since the last public release,
#     then increment AGE.
#
#  6. If any interfaces have been removed since the last public release,
#     then set AGE to 0.
#
# syntax: CURRENT[:REVISION[:AGE]]
REDLANDPP_LIBTOOL_VERSION=0:0:0
AC_SUBST(REDLANDPP_LIBTOOL_VERSION)


dnl Checks for library functions.

abs_top_builddir=`pwd`
AC_SUBST(abs_top_builddir)

if test "$USE_MAINTAINER_MODE" = yes; then
  REDLAND_CFLAGS="$REDLAND_CFLAGS $warning_cflags"
fi


AC_CONFIG_FILES([Makefile
src/Makefile
redlandpp/Makefile
utils/Makefile
redlandpp.pc])

AC_OUTPUT

AC_MSG_RESULT([
Redland++ build summary:
  Redland version: $REDLAND_VERSION
])
