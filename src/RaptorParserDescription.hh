#ifndef RAPTORPARSERDESCRIPTION_HH
#define RAPTORPARSERDESCRIPTION_HH

#include <string>
#include <ostream>

// Parser Description class

class RaptorParserDescription {
public:
  std::string name;
  std::string label;
  std::string mime_type;
  std::string uri_string;

protected:
  // protected constructor
  RaptorParserDescription(std::string name, std::string label, std::string mime_type, std::string uri_string);

  friend class Raptor;
  friend std::ostream& operator<< (std::ostream& os, const RaptorParserDescription& desc);
};

#endif
