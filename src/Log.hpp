/* -*- Mode: c; c-basic-offset: 2 -*-
 *
 * Log.hpp - Redland++ Log class interface
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

#ifndef REDLANDPP_LOG_HPP
#define REDLANDPP_LOG_HPP

#include <string>
#include <redland.h>

namespace Redland {

  class Log {
  public:
    Log(librdf_log_message *log) throw();

    ~Log() throw();

    std::string str() throw();

    int code; ///< Error code

    librdf_log_level    level;
    librdf_log_facility facility;

    std::string message;

    // Fields from raptor_locator* locator:

    void* uri; // Uri *uri;

    std::string file;

    int line;
    int column;
    int byte;  

  private:
    friend std::ostream& operator<< (std::ostream& os, const Log& o);
  };

} // namespace Redland

#endif
