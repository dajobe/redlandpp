/* -*- Mode: c; c-basic-offset: 2 -*-
 *
 * Node.hpp - Redland++ Node classes
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


#ifndef REDLANDPP_NODE_HH
#define REDLANDPP_NODE_HH

#include <string>

#include <redland.h>

#include <Exception.hpp>
#include <World.hpp>
#include <Uri.hpp>
#include <Wrapper.hpp>


namespace Redland {

  using namespace std;

  class Node: public Wrapper<librdf_node> {
    public:
      Node(World* world);

      virtual ~Node()=0;
    
      const string str();

    protected:
      World* world_;

    private:
      virtual string makeStr() = 0;
      string str_;

    friend ostream& operator<< (ostream& os, const Node& node);
  };

  Node* makeNode(World* world, librdf_node* n);


  class LiteralNode: public Node {
    public:
      string value;
      string language;
      Uri* datatype;

      LiteralNode::LiteralNode(World* w, librdf_node* n);

      LiteralNode(World* world, string value, string language, Uri* datatype=NULL);
    private:
      string makeStr();
  };


  class UriNode: public Node {
    public:
      Uri* value;

      UriNode(World* w, Uri* nvalue);
      UriNode(World* w, librdf_node* n);

    private:
      string makeStr();
  };


  class BlankNode: public Node {
    public:
      string id;

      BlankNode(World* w, const char* id);
      BlankNode(World* w, librdf_node* n);

    private:
      string makeStr();
  };


} // namespace Redland


#endif
