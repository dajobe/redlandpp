/* -*- Mode: c; c-basic-offset: 2 -*-
 *
 * Storage.cpp - Redland C++ Storage classes
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
#include "redlandpp/Storage.hpp"
#include "redlandpp/World.hpp"
#include "redlandpp/Wrapper.hpp"


namespace Redland {

  using namespace std;

  void Storage::init()
    throw(Exception)
  {
    const char* storage_name_str = storage_name_.c_str();

    const char* name_str = NULL;
    if(name_.size() > 0)
      name_str = name_.c_str();

    const char* options_str = NULL;
    if(options_.size() > 0)
      options_str = options_.c_str();
    
    obj_ = librdf_new_storage(world_->cobj(), storage_name_str, name_str,
                              options_str);
    if (obj_ == NULL)
      throw Exception("Failed to create storage " + storage_name_ + " with name " + name_ + " and options " + options_);

    world_->reset_error();
  }
  

  Storage::Storage(World* w, const string& sn, const string& n,
                   const string& opts)
    throw(Exception)
    : Redland::Wrapper<librdf_storage>((redland_object_free*)librdf_free_storage,
                                       NULL),
      world_(w),
      storage_name_(sn),
      name_(n),
      options_(opts)
  {
    init();
  }


  Storage::Storage(World& w, const string& sn, const string& n,
                   const string& opts)
    throw(Exception)
    : Redland::Wrapper<librdf_storage>((redland_object_free*)librdf_free_storage,
                                       NULL),
      world_(&w),
      storage_name_(sn),
      name_(n),
      options_(opts)
  {
    init();
  }


  Storage::~Storage()
  {
  }


  const string Storage::name() const
  {
    return name_;
  }


  const string Storage::str() const
  {
    return "Storage " + name();
  }


  ostream& operator<< (ostream& os, const Storage& p)
  {
    return os << p.str();
  }


  ostream& operator<< (ostream& os, const Storage* p)
  {
    return os << p->str();
  }


  MemoryStorage::MemoryStorage(World* w, const string n, const string opts)
    throw(Exception)
    : Storage(w, "memory", n, opts)
  {
  }

  MemoryStorage::MemoryStorage(World& w, const string n, const string opts)
    throw(Exception)
    : Storage(&w, "memory", n, opts)
  {
  }

  MemoryStorage::~MemoryStorage()
  {
  }

} // namespace Redland
