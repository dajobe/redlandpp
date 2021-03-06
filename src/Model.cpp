/* -*- Mode: c; c-basic-offset: 2 -*-
 *
 * Model.cpp - Redland C++ Model class
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
#include "redlandpp/Storage.hpp"
#include "redlandpp/Stream.hpp"
#include "redlandpp/Model.hpp"


namespace Redland {

  using namespace std;


  void Model::init(const string opts)
    throw(Exception)
  {
    const char* options_str = NULL;
    if(opts.size() > 0)
      options_ = opts.c_str();

    obj_ = librdf_new_model(world_->cobj(), storage_->cobj(), options_str);
    if (obj_ == NULL)
      throw Exception("Failed to create model with storage " + storage_->str());

    world_->reset_error();
  }


  Model::Model(World* w, Storage* s, const string opts)
    throw(Exception)
    : Redland::Wrapper<librdf_model>((redland_object_free*)librdf_free_model,
                                     NULL),
      world_(w),
      storage_(s)
  {
    init(opts);
  }


  Model::Model(World& w, Storage& s, const string opts)
    throw(Exception)
    : Redland::Wrapper<librdf_model>((redland_object_free*)librdf_free_model,
                                     NULL),
      world_(&w),
      storage_(&s)
  {
    init(opts);
  }


  Model::~Model()
  {
  }


  const string Model::str() const
  {
    return "Model over storage " + storage_->str();
  }


  ostream& operator<< (ostream& os, const Model& p)
  {
    return os << p.str();
  }


  ostream& operator<< (ostream& os, const Model* p)
  {
    return os << p->str();
  }


  void Model::add(Statement* s) throw(Exception)
  {
    if(s == NULL)
      throw Exception("Cannot add NULL statement");

    int rc=librdf_model_add_statement(cobj(), s->statement());
    if(rc)
      throw Exception("Failed to add statement");
  }


  void Model::add(Stream* st) throw(Exception)
  {
    if(st == NULL)
      throw Exception("Cannot add statements from NULL stream");

    int rc=librdf_model_add_statements(cobj(), st->cobj());
    if(rc)
      throw Exception("Failed to add statements from stream");
  }

  // FIXME: unfortunately not const because librdf_model_size isn't
  int Model::size()
  {
    return librdf_model_size(cobj());
  }


} // namespace Redland
