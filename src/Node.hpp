/* -*- Mode: c; c-basic-offset: 2 -*-
 *
 * Node.hpp - Redland++ Node classes interfaces
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

  class Node: public Wrapper<librdf_node> {
  public:
    Node(World* world);
    virtual ~Node();

    const std::string& str() const;

  protected:
    World* world_;

    virtual const std::string makeStr() const { return ""; };

  private:
    mutable std::string str_;

    friend std::ostream& operator<< (std::ostream& os, const Node& node);
  };

  Node* makeNode(World* world, librdf_node* n) throw(Exception);


  class LiteralNode: public Node {
  public:
    LiteralNode(World* w, librdf_node* n) throw(Exception);
    LiteralNode(World* world, std::string value, std::string language, Uri* datatype=NULL) throw(Exception);
    ~LiteralNode();

  private:
    const std::string makeStr() const;

    std::string value_;
    std::string language_;
    Uri* datatype_;
  };


  class UriNode: public Node {
  public:
    UriNode(World* w, Uri* u) throw();
    UriNode(World* w, librdf_node* n) throw(Exception);
    ~UriNode();

  private:
    const std::string makeStr() const;
    
    Uri* value_;
  };


  class BlankNode: public Node {
  public:
    BlankNode(World* w, const char* id) throw();
    BlankNode(World* w, librdf_node* n) throw();

  private:
    const std::string makeStr() const;
    
    std::string id_;
  };

} // namespace Redland

#endif
