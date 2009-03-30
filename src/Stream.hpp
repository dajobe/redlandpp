/* -*- Mode: c; c-basic-offset: 2 -*-
 *
 * Stream.hpp - Redland++ Stream class interface
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

#ifndef REDLANDPP_STREAM_HH
#define REDLANDPP_STREAM_HH

#include <string>
#include <iterator>

#include <redland.h>

#include <Exception.hpp>
#include <World.hpp>
#include <Wrapper.hpp>
#include <Stream.hpp>
#include <Statement.hpp>

namespace Redland {

  class Stream : public Wrapper<librdf_stream>
  {
  public:
    Stream(World* w, librdf_stream* s);
    ~Stream();

    const std::string str() const throw();

    // redland Statement iterators
    // FIXME: powerfully anti-C++, iterators should be separate
    Statement* get() const;
    bool       next() const;
    
  protected:
    World* world_;

  private:
    friend std::ostream& operator<< (std::ostream& os, const Stream& s);
  };

} // namespace Redland

#endif
