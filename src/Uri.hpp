/* -*- Mode: c; c-basic-offset: 2 -*-
 *
 * Exception.hpp - Redland++ Exception class
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


#ifndef REDLANDPP_URI_HH
#define REDLANDPP_URI_HH

#include <string>
#include <ostream>

#include <redland.h>

namespace Redland {

  using namespace std;

  class Uri : Wrapper<librdf_uri> {
    public:
      // public destructor
      ~Uri();

      // public methods
      const string str() const;

      librdf_uri* uri() const;

      Uri(World* world, const string str) throw(Exception);
      Uri(World* world, librdf_uri* uri) throw(Exception);

    protected:

    private:
      World* world_;

      friend ostream& operator<< (ostream& os, const Uri& uri);
      friend ostream& operator<< (ostream& os, const Uri* uri);
  };


} // namespace Redland


#endif
