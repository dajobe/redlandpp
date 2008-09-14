// C++ raptor test program

#include <iostream>
#include <string>

#include <Redland.hpp>

using namespace std;

using namespace Redland;


int main(int argc, char *argv[])
{
  World* red= new World();

  cout << "Initialised Redland " << red << endl;

#if 0  
  cout << "Initialised Raptor " + r.getVersionString() << endl <<
    r.getShortCopyrightString() << endl;
#endif

  Uri* uri = new Uri(red, "http://librdf.org/raptor/raptor.rdf");

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

  Parser* parser = new Parser(red, string("rdfxml"));

  cout << "Parser is " << parser << endl;

  try {
    Stream* s = parser->parseUri(uri, NULL);
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
    cout << "parseUri(" << uri << ") failed with exception " << e.what() << endl;
  }

  delete parser;

  delete uri;
  
  delete red;

  return 0;
}
