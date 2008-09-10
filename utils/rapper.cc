// C++ raptor test program

#include <iostream>
#include <string>

#include <Raptor.hh>

using namespace std;


int main(int argc, char *argv[])
{
  Raptor r;
  
  cout << "Initialised Raptor " + r.getVersionString() << endl <<
    r.getShortCopyrightString() << endl;
  
  RaptorUri* uri = r.newUri("http://librdf.org/raptor/raptor.rdf");

  cout << "URI is " << uri << endl;

  std::vector<RaptorParserDescriptor> v=r.getParserDescriptors();
  for (unsigned int i = 0; i < v.size(); i++ ) {
    cout << "Parser " << i << endl << v[i] << endl;
  }

  if (r.isParserName("rdfxml")) {
    cout << "rdfxml IS a parser name\n";
  }

  if (!r.isParserName("foobar")) {
    cout << "foobar IS NOT a parser name\n";
  }

  RaptorParser* parser = r.newParser("rdfxml");

  cout << "Parser is " << parser->getName() << endl;

  parser->parseUri(uri, uri);
  
  return 0;
}
