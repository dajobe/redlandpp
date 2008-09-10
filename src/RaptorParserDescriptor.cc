#include <RaptorParserDescriptor.hh>

#include <string>
#include <ostream>

// RaptorParserDescriptor class

RaptorParserDescriptor::RaptorParserDescriptor(std::string name, std::string label, std::string mime_type, std::string uri_string)
  : name(name), label(label), mime_type(mime_type), uri_string(uri_string)
{
}


std::ostream& operator<< (std::ostream& os, const RaptorParserDescriptor& desc) 
{
  return os << "  Name "  << desc.name << std::endl 
            << "  Label " << desc.label << std::endl 
            << "  Type "  << desc.mime_type << std::endl
            << "  URI "   << desc.uri_string << std::endl;
}
