#include <RaptorParserDescription.hh>

#include <string>
#include <ostream>

// RaptorParserDescription class

RaptorParserDescription::RaptorParserDescription(std::string pname, std::string plabel, std::string pmime_type, std::string puri_string)
  : name(pname), label(plabel), mime_type(pmime_type), uri_string(puri_string)
{
}


std::ostream& operator<< (std::ostream& os, const RaptorParserDescription& desc) 
{
  return os << "  Name "  << desc.name << std::endl 
            << "  Label " << desc.label << std::endl 
            << "  Type "  << desc.mime_type << std::endl
            << "  URI "   << desc.uri_string << std::endl;
}
