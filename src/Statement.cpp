/* -*- Mode: c; c-basic-offset: 2 -*-
 *
 * Statement.cpp - Redland C++ Statement class
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
#include <Statement.hpp>


namespace Redland {

  class LiteralNode;
  class UriNode;
  class BlankNode;
  
  using namespace std;

  Statement::Statement(World* w, const librdf_statement* s)
    : Redland::Wrapper<librdf_statement>((redland_object_free*)librdf_free_statement,
                                         (librdf_statement*)s),
    world_(w)
  {
    subject = makeNode(world_,
                       librdf_statement_get_predicate((librdf_statement*)s));
    predicate = makeNode(world_,
                         librdf_statement_get_predicate((librdf_statement*)s));
    object = makeNode(world_,
                      librdf_statement_get_object((librdf_statement*)s));
    context = NULL;
  }


  librdf_statement* statement() const
  {
    return obj_;
  }
  

  Statement::~Statement()
  {
    if(subject != NULL)
      delete subject;
    if(predicate != NULL)
      delete predicate;
    if(object != NULL)
      delete object;
    if(context != NULL)
      delete context;
  }


  ostream& operator<< (ostream& os, const Statement& s)
  {
    return os << "["  << s.subject->str()
              << ", " << s.predicate->str()
              << ", " << s.object->str()
              << "]";
  }

  ostream& operator<< (ostream& os, const Statement* s)
  {
    return os << "["  << s->subject->str()
              << ", " << s->predicate->str()
              << ", " << s->object->str()
              << "]";
  }


} // namespace Redland
