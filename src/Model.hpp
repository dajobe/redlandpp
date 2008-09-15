/* -*- Mode: c; c-basic-offset: 2 -*-
 *
 * Model.cpp - Redland C++ Model class interface
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


#ifndef REDLANDPP_MODEL_HH
#define REDLANDPP_MODEL_HH


#ifdef HAVE_CONFIG_H
#include <redlandpp_config.h>
#endif

#include <World.hpp>
#include <Exception.hpp>
#include <Wrapper.hpp>
#include <Stream.hpp>
#include <Uri.hpp>


namespace Redland {

  using namespace std;

  class Model : public Wrapper<librdf_model> {
    public:
    Model(World* w, Storage* s, const string opts) throw(Exception);

    ~Model();

    // public methods
    const string str() const;

    librdf_model* model() const;

  protected:
    World* world_;

  private:
    Storage* storage_;
    string options_;

    friend ostream& operator<< (ostream& os, const Model& p);
    friend ostream& operator<< (ostream& os, const Model* p);
  };


} // namespace Redland

#endif
