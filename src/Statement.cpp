/* -*- Mode: c; c-basic-offset: 2 -*-
 *
 * World.cpp - Redland C++ World class
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

  Node* makeNode(World* w, librdf_node* n) 
  {
    Node* node=NULL;
    
    switch(librdf_node_get_type(n)) {
      case LIBRDF_NODE_TYPE_RESOURCE:
        {
          Uri* uri=new Uri(w, librdf_node_get_uri(n));
          node=new UriNode(w, uri);
        }
        break;

      case LIBRDF_NODE_TYPE_BLANK:
        node=new BlankNode(w, (const char*)librdf_node_get_blank_identifier(n));
        break;

      case LIBRDF_NODE_TYPE_LITERAL:
        {
          char* language=librdf_node_get_literal_value_language(n);
          string language_str;
          if(language != NULL)
            language_str=(const char*)language;
          librdf_uri* datatype=librdf_node_get_literal_value_datatype_uri(n);
          Uri* datatype_uri=NULL;
          if(datatype != NULL)
            datatype_uri=new Uri(w, datatype);

          node=new LiteralNode(w,
                               (const char*)librdf_node_get_literal_value(n),
                               language_str, datatype_uri);
        }
        break;

      case LIBRDF_NODE_TYPE_UNKNOWN:
      default:
        break;
    }

    return node;
  }


  Statement::Statement(World* world, const librdf_statement* s)
  {
    subject=makeNode(world, librdf_statement_get_predicate((librdf_statement*)s));
    predicate=makeNode(world, librdf_statement_get_predicate((librdf_statement*)s));
    object=makeNode(world, librdf_statement_get_object((librdf_statement*)s));
  }


  ostream& operator<< (ostream& os, const Statement& statement)
  {
    return os << "["  << statement.subject->str()
              << ", " << statement.predicate->str()
              << ", " << statement.object->str()
              << "]";
  }

} // namespace Redland
