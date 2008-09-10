#include <RaptorException.hh>
#include <RaptorWorld.hh>
#include <RaptorParser.hh>
#include <RaptorTriple.hh>

#include <iostream>

// RaptorParser class

void
parseErrorHandler(void *user_data, raptor_locator* locator, const char *message)
{
  RaptorParser* parser = (RaptorParser*)user_data;
  parser->error_ = new std::string("Error: " + (std::string)message);
}


void
parseWarningHandler(void *user_data, raptor_locator* locator, const char *message)
{
  RaptorParser* parser = (RaptorParser*)user_data;
  parser->error_ = new std::string("Warning: " + (std::string)message);
}


RaptorParser::RaptorParser(Raptor* r, const std::string name)
  throw(RaptorException)
{
  raptor_ = r;
  parser_ = raptor_new_parser_v2(raptor_->getWorld(), name.c_str());
  if (parser_ == NULL)
    throw RaptorException("Failed to create parser " + name);
  triples_ = NULL;
  error_ = NULL;
  
  raptor_set_fatal_error_handler(parser_, this, parseErrorHandler);
  raptor_set_error_handler(parser_, this, parseErrorHandler);
  raptor_set_warning_handler(parser_, this, parseWarningHandler);
}

RaptorParser::RaptorParser(Raptor* r, RaptorUri* uri, 
                           std::string mime_type, 
                           const std::string buffer,
                           const std::string identifier) throw(RaptorException)
{
  raptor_ = r;

  const char* mime_type_c=NULL;
  if (mime_type.length() > 0)
    mime_type_c = mime_type.c_str();
  
  const unsigned char* buffer_c=NULL;
  size_t buffer_len_c=0;
  if (buffer.length() > 0) {
    buffer_c = (const unsigned char*)buffer.c_str();
    buffer_len_c = buffer.length();
  }
  const unsigned char* identifier_c=NULL;
  if (identifier.length() > 0)
    identifier_c = (const unsigned char*)identifier.c_str();

  parser_ = raptor_new_parser_for_content_v2(raptor_->getWorld(), 
                                             uri->getUri(), mime_type_c,
                                             buffer_c, buffer_len_c,
                                             identifier_c);
  if (parser_ == NULL)
    throw RaptorException("Failed to create parser for content");

  raptor_set_fatal_error_handler(parser_, this, parseErrorHandler);
  raptor_set_error_handler(parser_, this, parseErrorHandler);
  raptor_set_warning_handler(parser_, this, parseWarningHandler);
}


RaptorParser::~RaptorParser()
{
  if (parser_) {
    raptor_free_parser(parser_); parser_ =NULL; 
  }
  raptor_ = NULL;
}


raptor_parser* RaptorParser::getParser() const
{
  return parser_;
}


const std::string RaptorParser::getName() const
{
  return raptor_get_name(parser_);
}


const std::string RaptorParser::getLabel() const
{
  return raptor_get_label(parser_);
}


const std::string RaptorParser::str() const
{
  return getLabel() + " (" + getName() + ")";
}


std::ostream& operator<< (std::ostream& os, const RaptorParser& parser)
{
  return os << parser.str();
}
  
int RaptorParser::parseStart(RaptorUri* uri) throw(RaptorException)
{
  int rc= raptor_start_parse(parser_, uri->getUri());
  if(error_ != NULL) {
    std::string* e=error_;
    error_ = NULL;
    throw RaptorException(*e);
  }
  return rc;
}


int RaptorParser::parseChunk(std::string buffer, bool isEnd) throw(RaptorException)
{
  const unsigned char* buffer_c = NULL;
  size_t buffer_len_c = 0;
  if (buffer.length() > 0) {
    buffer_c = (const unsigned char*)buffer.c_str();
    buffer_len_c = buffer.length();
  }

  int rc=raptor_parse_chunk(parser_, buffer_c, buffer_len_c, (int)isEnd);
  if(error_ != NULL) {
    std::string* e=error_;
    error_ = NULL;
    throw RaptorException(*e);
  }

  return rc;
}


int RaptorParser::parseFile(RaptorUri* uri, RaptorUri* base_uri)
  throw(RaptorException)
{
  int rc= raptor_parse_file(parser_, uri->getUri(), base_uri->getUri());
  if(error_ != NULL) {
    std::string* e=error_;
    error_ = NULL;
    throw RaptorException(*e);
  }
  return rc;
}


void parseStatementHandler(void *user_data,
                           const raptor_statement *statement)
{
  RaptorParser* parser=(RaptorParser*)user_data;
  parser->triples_->push_back(statement);

  RaptorTriple t(parser->raptor_, statement);

  std::cout << "Triple " << t << std::endl;
}


int RaptorParser::parseUri(RaptorUri* uri, RaptorUri* base_uri = NULL)
  throw(RaptorException)
{
  triples_ = new std::vector<const raptor_statement*>;
  
  raptor_set_statement_handler(parser_, this, parseStatementHandler);
  raptor_uri* buri=(base_uri != NULL) ? base_uri->getUri() : NULL;
  int rc = raptor_parse_uri(parser_, uri->getUri(), buri);
  raptor_set_statement_handler(parser_, NULL, NULL);

  if(error_ != NULL) {
    std::string* e=error_;
    error_ = NULL;
    throw RaptorException(*e);
  }

  return rc;
}


void RaptorParser::parseAbort()
{
  raptor_parse_abort(parser_);
}

