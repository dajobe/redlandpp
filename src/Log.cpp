/* -*- Mode: c; c-basic-offset: 2 -*-
 *
 * Log.cpp - Redland C++ Log class
 *
 * Copyright (C) 2008, David Beckett http://www.dajobe.org/
 * 
 * This package is Free Software and part of Redland http://librdf.org/
 * 
 * It is licensed under the following three licenses as alternatives:
 *   1. GNU Lesser General Public License (LGPL) V2.1 or any newer version
 *   2. GNU General Public License (GPL) V2 or any newer version
 *   3. Apache License, V2.0 or any newer version
 * 
 * You may not use this file except in compliance with at least one of
 * the above three licenses.
 * 
 * See LICENSE.html or LICENSE.txt at the top of this package for the
 * complete terms and further detail along with the license texts for
 * the licenses in COPYING.LIB, COPYING and LICENSE-2.0.txt respectively.
 * 
 * 
 */


#ifdef HAVE_CONFIG_H
#include <redlandpp_config.h>
#endif

#include <string>
#include <ostream>

#include <Log.hpp>

namespace Redland {

  using namespace std;

  Log::Log(librdf_log_message* log) throw()
  {
    code = log->code;
    level = log->level;
    facility = log->facility;
    message = string(log->message);

    if(log->locator) {
      uri = NULL; // uri = log->locator->uri;
      if(log->locator->file)
        file = string(log->locator->file);
      line = log->locator->line;
      column = log->locator->column;
      byte = log->locator->byte;
    }
  }


  Log::~Log() throw()
  {
  }


  ostream& operator<< (ostream& os, const Log& log)
  {
    string str= log.message;
    if(log.file.size()  || log.uri != NULL) {
      str += " at ";
      if(log.line >= 0) {
        str +=  "line ";
        str += log.line;
        str += " of ";
      }
      if(log.file.size())
        str += log.file;
    }

    return os << str;
  }

} // namespace Redland