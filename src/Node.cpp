/* -*- Mode: c; c-basic-offset: 2 -*-
 *
 * World.cpp - Redland C++ Statement class
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

#include <Exception.hpp>

#include <redland.h>

#include <World.hpp>
#include <Statement.hpp>
#include <Node.hpp>

namespace Redland {

  using namespace std;

  Node::Node(World* w)
    : Redland::Wrapper<librdf_node>((redland_object_free*)librdf_free_node,
                                    NULL),
    world_(w)
  {
  }
  

  ostream& operator<< (ostream& os, const Node& node)
  {
    return os << node.str_;
  }


  const string Node::str()
  {
    if(str_.length() == 0)
      str_ = makeStr();
    return str_;
  }


  LiteralNode::LiteralNode(World* w, string nvalue, string nlanguage,
                           Uri* ndatatype)
    : Node(w), value(nvalue), language(nlanguage), datatype(ndatatype)
  {
    librdf_uri* duri=NULL;
    if(datatype != NULL)
      duri=ndatatype->uri();
    
    obj_=librdf_new_node_from_typed_literal(w->world(),
                                            (const unsigned char*)&nvalue,
                                            (const char*)&nlanguage,
                                            duri);
  }


  string LiteralNode::makeStr()
  {
    string s = "\"" + value + "\"";
    if(language.length() > 0)
      s.append("@" + language);
    if(datatype != NULL)
      s.append("^^<" + datatype->str() + ">");

    return s;
  }


  UriNode::UriNode(World* w, Uri* nvalue) 
    : Node(w), value(nvalue)
  {
  }


  string UriNode::makeStr()
  {
    return "<" + value->str() + ">";
  }


  BlankNode::BlankNode(World* w, const char* nid)
    : Node(w), id(nid)
  {
  }


  string BlankNode::makeStr()
  {
    return "_:" + id;
  }


} // namespace Redland
