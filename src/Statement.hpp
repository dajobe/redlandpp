/* -*- Mode: c; c-basic-offset: 2 -*-
 *
 * Statement.hpp - Redland++ Statement/Triple class
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


#ifndef REDLANDPP_STATEMENT_HH
#define REDLANDPP_STATEMENT_HH

#include <string>

#include <redland.h>

#include <Exception.hpp>
#include <World.hpp>
#include <Uri.hpp>
#include <Node.hpp>
#include <Wrapper.hpp>


namespace Redland {

  using namespace std;

  class Statement {
    public:
      Node* subject;
      Node* predicate;
      Node* object;
      Node* context;

      ~Statement();

    private:
      Statement();
      Statement(World* w, const librdf_statement* s);

    friend class Stream;
    friend ostream& operator<< (ostream& os, const Statement& s);
    friend ostream& operator<< (ostream& os, const Statement* s);
    friend void parseStatementHandler(void *user_data, const librdf_statement *s);
  };


} // namespace Redland


#endif
