/* -*- Mode: c; c-basic-offset: 2 -*-
 *
 * Statement.hpp - Redland++ Statement/Triple class interface
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

#ifndef REDLANDPP_STATEMENT_HPP
#define REDLANDPP_STATEMENT_HPP

#include <string>

#include <redland.h>

#include "redlandpp/Exception.hpp"
#include "redlandpp/World.hpp"
#include "redlandpp/Uri.hpp"
#include "redlandpp/Node.hpp"
#include "redlandpp/Wrapper.hpp"

namespace Redland {

  class Statement : public Wrapper<librdf_statement> {
  public:
    Node* subject()   { return subject_; }
    Node* predicate() { return predicate_; }
    Node* object()    { return object_; }
    Node* context()   { return context_; }

    const Node* subject()   const { return subject_; }
    const Node* predicate() const { return predicate_; }
    const Node* object()    const { return object_; }
    const Node* context()   const { return context_; }

    ~Statement();

    librdf_statement* statement() const;

  private:
    World* world_;
    Node* subject_;
    Node* predicate_;
    Node* object_;
    Node* context_;
    
    Statement();
    Statement(World* w, const librdf_statement* s);

    friend class Stream;
    friend std::ostream& operator<< (std::ostream& os, const Statement& s);
    friend std::ostream& operator<< (std::ostream& os, const Statement* s);
    friend void parseStatementHandler(void *user_data, const librdf_statement *s);
  };

} // namespace Redland

#endif
