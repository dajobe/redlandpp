/* -*- Mode: c; c-basic-offset: 2 -*-
 *
 * Stream.cpp - Redland C++ Stream class
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

#include <redland.h>

#include <redland.h>

#include <World.hpp>
#include <Stream.hpp>
#include <Stream.hpp>


namespace Redland {

  using namespace std;

  Stream::Stream(World* w, librdf_stream* s)
    : Redland::Wrapper<librdf_stream>((redland_object_free*)librdf_free_stream,
                                    s),
    world_(w)
  {
  }
  

  Stream::~Stream()
  {
  }


  const string Stream::str()
    throw()
  {
    return "Stream";
  }

  ostream& operator<< (ostream& os, const Stream& stream)
  {
    return os << ((Stream&)stream).str();
  }


  Statement* Stream::get() const
  {
    Statement* s=NULL;

    librdf_statement* st;
    st = librdf_stream_get_object(obj_);
    if(st != NULL)
      s = new Statement(world_, st);

    return s;
  }
  
  
  bool Stream::next() const 
  {
    return (librdf_stream_next(obj_) != 0);
  }
  
} // namespace Redland
