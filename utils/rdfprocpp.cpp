/* -*- Mode: c; c-basic-offset: 2 -*-
 *
 * rdfprocpp.cpp - Redland C++ Utility
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


#include <iostream>
#include <string>

#include "redlandpp/Redland.hpp"

using namespace std;

using namespace Redland;


int main(int argc, char *argv[])
{
  World world;

  cout << "Initialised " << world << endl;

  MemoryStorage storage(world);
  
  Model model(world, storage);
  
  cout << "Redland is " + world.shortCopyrightString() << endl;

  Uri uri(&world, "http://librdf.org/raptor/raptor.rdf");

  cout << "URI is " << uri << endl;

#if 0
  std::vector<RaptorParserDescription> v=r.getParserDescriptions();
  for (unsigned int i = 0; i < v.size(); i++ ) {
    cout << "Parser " << i << endl << v[i] << endl;
  }

  if (r.isParserName("rdfxml")) {
    cout << "rdfxml IS a parser name\n";
  }

  if (!r.isParserName("foobar")) {
    cout << "foobar IS NOT a parser name\n";
  }
#endif

  Parser parser(&world, string("rdfxml"));

  cout << "Parser is " << parser << endl;

#if 0
  try {
    Stream* s = parser.parseUri(&uri, NULL);
    while(true) {
      Statement* st=s->get();
      if(st == NULL)
        break;
      cout << "Triple " << st << endl;
      s->next();
      delete st;
    }
    delete s;
  }
  catch (Exception &e) {
    cerr << "parseUri(" << uri << ") failed with exception " << e.what() << endl;
  }
#endif

  try {
    Stream* s=parser.parseUri(&uri, NULL);
    model.add(s);
    delete s;
  }
  catch (Exception &e) {
    cerr << "parseUri(" << uri << ") failed with exception " << e.what() << endl;
  }

  cout << "Model has " << model.size() << " triples" << endl;

  return 0;
}
