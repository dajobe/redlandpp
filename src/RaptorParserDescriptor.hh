#ifndef RAPTORPARSERDESCRIPTOR_HH
#define RAPTORPARSERDESCRIPTOR_HH

#include <string>
#include <ostream>

// Parser Descriptor class

class RaptorParserDescriptor {
public:
  std::string name;
  std::string label;
  std::string mime_type;
  std::string uri_string;

  friend std::ostream& operator<< (std::ostream& os, const RaptorParserDescriptor& desc);

protected:
  // protected constructor
  RaptorParserDescriptor(std::string name, std::string label, std::string mime_type, std::string uri_string);

  friend class Raptor;
};

#endif
