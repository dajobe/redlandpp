#ifndef RAPTORPARSER_HH
#define RAPTORPARSER_HH

#include <string>
#include <vector>

// Parser class

class RaptorParser {
public:
  // public destructor
  RaptorParser::~RaptorParser();

  // public methods
  // raptor_get_name
  const std::string RaptorParser::getName() const;
  // raptor_get_label
  const std::string RaptorParser::getLabel() const;

  const std::string str() const;

  friend std::ostream& operator<< (std::ostream& os, const RaptorParser& parser);
  
  raptor_parser* RaptorParser::getParser() const;

  int parseStart(RaptorUri& uri);
  int parseChunk(std::string buffer, bool isEnd);

  //int parseFileStream(FILE* stream, std::string filename, RaptorUri& base_uri);
  int parseFile(RaptorUri& uri, RaptorUri& base_uri);
  int parseUri(RaptorUri& uri, RaptorUri& base_uri);
  void parseAbort();

protected:
  // protected constructor
  RaptorParser::RaptorParser(Raptor* r, const std::string name) throw(RaptorException);
  RaptorParser::RaptorParser(Raptor* r, RaptorUri& uri, std::string mime_type, const std::string buffer, const std::string identifier) throw(RaptorException);

private:
  Raptor* raptor_;
  
  // C object
  raptor_parser* parser_;

  std::vector<const raptor_statement*>* triples_;

  friend class Raptor;
  friend void parseStatementHandler(void *user_data, const raptor_statement *statement);
};

#endif
