/* -*- Mode: c; c-basic-offset: 2 -*-
 *
 * Parser.cpp - Redland C++ Parser class
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

#include <Exception.hpp>
#include <World.hpp>
#include <Wrapper.hpp>
#include <Stream.hpp>
#include <Parser.hpp>

namespace Redland {

  using namespace std;

  Parser::Parser(World* w, const string n)
    throw(Exception)
    : Redland::Wrapper<librdf_parser>((redland_object_free*)librdf_free_parser,
                                      NULL),
      world_(w),
      name_(n)
  {
    obj_ = librdf_new_parser(w->cobj(), name_.c_str(), NULL, NULL);
    if (obj_ == NULL)
      throw Exception("Failed to create parser " + name_);

    w->reset_error();
  }


  Parser::Parser(World* w, Uri* uri, string mime_type, 
                 const string buffer, const string identifier)
    throw(Exception)
    : Redland::Wrapper<librdf_parser>((redland_object_free*)librdf_free_parser,
                                      NULL),
    world_(w)
  {
    const char* mime_type_c=NULL;
    if (mime_type.size() > 0)
      mime_type_c = mime_type.c_str();

    const unsigned char* buffer_c=NULL;
    if (buffer.size() > 0)
      buffer_c = (const unsigned char*)buffer.c_str();
    const unsigned char* identifier_c=NULL;
    if (identifier.size() > 0)
      identifier_c = (const unsigned char*)identifier.c_str();

    const char* name_str;
    name_str = librdf_parser_guess_name(mime_type_c, buffer_c, identifier_c);
    if (name_str == NULL)
      throw Exception("Failed to guess parser for content");

    name_ = name_str;
    
    obj_ = librdf_new_parser(w->cobj(), name_.c_str(), NULL, NULL);
    if (obj_ == NULL)
      throw Exception("Failed to create parser for content");
  }


  librdf_parser* Parser::parser() const
  {
    return obj_;
  }


  Parser::~Parser()
  {
  }

  const string Parser::name() const
  {
    return name_;
  }


  const string Parser::str() const
  {
    return "Parser " + name();
  }


  ostream& operator<< (ostream& os, const Parser& p)
  {
    return os << p.str();
  }


  ostream& operator<< (ostream& os, const Parser* p)
  {
    return os << p->str();
  }


  Stream* Parser::parseString(string s, Uri* uri, Uri* base_uri = NULL)
    throw(Exception)
  {
    librdf_stream *stream;
    stream = librdf_parser_parse_string_as_stream(obj_,
                                                  (const unsigned char*)s.c_str(),
                                                  base_uri->cobj());
    world_->check_and_throw();
    if(stream == NULL)
      throw Exception("Failed to parse string");

    return new Stream(world_, stream);
  }


  Stream* Parser::parseUri(Uri* uri, Uri* base_uri = NULL)
    throw(Exception)
  {
    librdf_uri* buri = (base_uri != NULL) ? base_uri->cobj() : NULL;
    librdf_stream* stream;
    stream = librdf_parser_parse_as_stream(obj_, uri->cobj(), buri);
    world_->check_and_throw();
    if(stream == NULL)
      throw Exception("Failed to parse URI " + uri->str());

    return new Stream(world_, stream);
  }


} // namespace Redland
