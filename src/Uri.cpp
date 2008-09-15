/* -*- Mode: c; c-basic-offset: 2 -*-
 *
 * Uri.cpp - Redland C++ Uri class
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

#include <Exception.hpp>

#include <World.hpp>
#include <Uri.hpp>

namespace Redland {

  using namespace std;

  Uri::Uri(World* w, const std::string s) throw(Exception)
    : Redland::Wrapper<librdf_uri>((redland_object_free*)librdf_free_uri,
                                   NULL),
    world_(w)
  {
    obj_ = librdf_new_uri(world_->world(), (const unsigned char*)s.c_str());
    if(obj_ == NULL)
      throw Exception("Failed to create uri " + s);
  }
  
  Uri::Uri(World* w, librdf_uri* u) throw(Exception)
    : Redland::Wrapper<librdf_uri>((redland_object_free*)librdf_free_uri,
                                   NULL),
    world_(w)
  {
    obj_ = librdf_new_uri_from_uri(u);
    if(obj_ == NULL)
      throw Exception("Failed to create uri from uri");
  }
  
  
  Uri::~Uri()
  {
  }
  
  
  librdf_uri* Uri::uri() const
  {
    return (librdf_uri*)obj_;
  }
    
  
  const std::string Uri::str() const
  {
    return (const char*)librdf_uri_as_string(obj_);
  }
  
  
  std::ostream& operator<< (std::ostream& os, const Uri& uri)
  {
    return os << uri.str();
  }
  
  std::ostream& operator<< (std::ostream& os, const Uri* uri)
  {
    return os << uri->str();
  }

} // namespace Redland

