#ifndef RAPTORWORLD_HH
#define RAPTORWORLD_HH

#include <RaptorException.hh>
#include <RaptorUri.hh>
#include <RaptorParserDescriptor.hh>
#include <RaptorParser.hh>

#include <raptor.h>

#include <string>
#include <ostream>
#include <vector>

// Raptor World class

class Raptor {
public:
  // default constructor
  Raptor();
  
  // destructor
  ~Raptor();

  raptor_world* getWorld();

  /* Constants */
  const std::string getShortCopyrightString() const;
  const std::string getCopyrightString() const;
  const std::string getVersionString() const;
  int getVersionMajor() const;
  int getVersionMinor() const;
  int getVersionRelease() const;
  int getVersionDecimal() const;
  const std::string getLicenseString() const;
  const std::string getHomeUrlString() const;

  //const std::string getXmlNamespaceUri() const;
  //const std::string getRdfNamespaceUri() const;
  //const std::string getRdfSchemaNamespaceUri() const;
  //const std::string getXmlschemaDatatypesNamespaceUri() const;
  //const std::string getOwlNamespaceUri() const;


  // parser information
  // (raptor_parsers_enumerate, raptor_parsers_enumerate_v2, 
  // raptor_syntaxes_enumerate, raptor_syntaxes_enumerate_v2)
  RaptorParserDescriptor getParserDescriptor(const unsigned int counter) throw(RaptorException);
  std::vector<RaptorParserDescriptor> getParserDescriptors();
  // (raptor_syntax_name_check, raptor_syntax_name_check_v2)
  bool isParserName(const std::string name);
  // (raptor_guess_parser_name, raptor_guess_parser_name_v2)
  const std::string guessParserName(RaptorUri* uri, const std::string mime_type, const std::string buffer, const std::string identifier);
  
  // raptor_new_parser
  RaptorParser* newParser(const std::string);

  // URI constructors
  RaptorUri* newUri(const std::string);

protected:
  
private:
  // C object
  raptor_world* world_;
};

#endif
