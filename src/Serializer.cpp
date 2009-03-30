/* -*- Mode: c; c-basic-offset: 2 -*-
 *
 * Serializer.cpp - Redland C++ Serializer class
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

#include <iostream>

#include <redland.h>

#include "redlandpp/Exception.hpp"
#include "redlandpp/World.hpp"
#include "redlandpp/Wrapper.hpp"
#include "redlandpp/Stream.hpp"
#include "redlandpp/Serializer.hpp"

namespace Redland {

  using namespace std;

  Serializer::Serializer(World* w, const string n, string mt = "",
                         Uri* u = NULL)
    throw(Exception)
    : Redland::Wrapper<librdf_serializer>((redland_object_free*)librdf_free_serializer,
                                          NULL),
      world_(w),
      name_(n)
  {
    const char* mt_str = NULL;
    if(mt.size() > 0)
      mt_str=mt.c_str();

    librdf_uri* uri_obj = NULL;
    if(u != NULL)
      uri_obj=u->cobj();
    
    obj_ = librdf_new_serializer(w->cobj(), name_.c_str(), mt_str, uri_obj);
    if (obj_ == NULL)
      throw Exception("Failed to create serializer " + name_);

    w->reset_error();
  }

  librdf_serializer* Serializer::serializer() const
  {
    return obj_;
  }


  Serializer::~Serializer()
  {
  }

  const string Serializer::name() const
  {
    return name_;
  }


  const string Serializer::str() const
  {
    return "Serializer " + name();
  }


  ostream& operator<< (ostream& os, const Serializer& p)
  {
    return os << p.str();
  }


  ostream& operator<< (ostream& os, const Serializer* p)
  {
    return os << p->str();
  }




} // namespace Redland
