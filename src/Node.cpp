/* -*- Mode: c; c-basic-offset: 2 -*-
 *
 * Node.cpp - Redland C++ Node classes
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

#include "redlandpp/Exception.hpp"
#include "redlandpp/Node.hpp"
#include "redlandpp/Statement.hpp"

namespace Redland {

  class World;

  using namespace std;

  Node::Node(World* w)
    : Redland::Wrapper<librdf_node>((redland_object_free*)librdf_free_node,
                                    NULL),
    world_(w)
  {
  }
  
  Node::~Node()
  {
  }


  Node* makeNode(World* w, librdf_node* n)
    throw(Exception)
  {
    Node* node=NULL;
    
    switch(librdf_node_get_type(n)) {
      case LIBRDF_NODE_TYPE_RESOURCE:
        node = new UriNode(w, n);
        break;

      case LIBRDF_NODE_TYPE_BLANK:
        node=new BlankNode(w, n);
        break;

      case LIBRDF_NODE_TYPE_LITERAL:
        node=new LiteralNode(w, n);
        break;

      case LIBRDF_NODE_TYPE_UNKNOWN:
      default:
        break;
    }

    return node;
  }


  ostream& operator<< (ostream& os, const Node& node)
  {
    return os << node.str_;
  }


  const string& Node::str() const
  {
    if(str_.size() == 0)
      str_ = makeStr();
    return str_;
  }


  LiteralNode::LiteralNode(World* w, librdf_node* n)
    throw(Exception)
    : Node(w), datatype_(NULL)
  {
    obj_ = librdf_new_node_from_node(n);

    const char* value_str = (const char*)librdf_node_get_literal_value(n);
    value_ = value_str;
    
    const char* language_str = (const char*)librdf_node_get_literal_value_language(n);
    if(language_str)
      language_ = language_str;
    
    librdf_uri* datatype_uri = librdf_node_get_literal_value_datatype_uri(n);
    if(datatype_uri != NULL)
      datatype_ = new Uri(w, datatype_uri);
  }


  LiteralNode::LiteralNode(World* w, string v, string l, Uri* d)
    throw(Exception)
    : Node(w), value_(v), language_(l), datatype_(d)
  {
    const unsigned char* value_str = (const unsigned char*)value_.c_str();
    
    const char* language_str=NULL;
    if(language_.size() > 0)
      language_str = language_.c_str();

    librdf_uri* datatype_uri=NULL;
    if(datatype_ != NULL)
      datatype_uri = datatype_->cobj();
    
    obj_ = librdf_new_node_from_typed_literal(w->cobj(),
                                              value_str, language_str,
                                              datatype_uri);
    if(obj_ == NULL)
      throw Exception("Failed to create node from literal " + value_);
  }


  LiteralNode::~LiteralNode()
  {
    if(datatype_ != NULL)
      delete datatype_;
  }
  

  const string LiteralNode::makeStr() const
  {
    string s = "\"" + value_ + "\"";
    if(language_.size() > 0)
      s.append("@" + language_);
    if(datatype_ != NULL)
      s.append("^^<" + datatype_->str() + ">");

    return s;
  }


  UriNode::UriNode(World* w, Uri* u) throw()
    : Node(w), value_(u)
  {
  }


  UriNode::UriNode(World* w, librdf_node* n) throw(Exception)
    : Node(w)
  {
    obj_   = librdf_new_node_from_node(n);
    value_ = new Uri(w, librdf_node_get_uri(obj_));
  }


  UriNode::~UriNode()
  {
    if(value_ != NULL)
      delete value_;
  }
  

  const string UriNode::makeStr() const
  {
    return "<" + value_->str() + ">";
  }


  BlankNode::BlankNode(World* w, const char* i)
    throw()
    : Node(w), id_(i)
  {
  }


  BlankNode::BlankNode(World* w, librdf_node* n)
    throw()
    : Node(w)
  {
    const char* id_str = (const char*)librdf_node_get_blank_identifier(n);
    id_ = string(id_str);
  }


  const string BlankNode::makeStr() const
  {
    return "_:" + id_;
  }


} // namespace Redland
