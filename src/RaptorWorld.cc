#include <RaptorWorld.hh>

// Raptor World class

// FIXME - internal function - should not be used
extern "C" 
{
  raptor_world* raptor_world_instance(void);
}

Raptor::Raptor()
{
  // FIXME: This code should be
  //   world_ = raptor_new_world();
  // but the internals do not all use the world object yet
  // and creating any parser typically crashes the application.
  raptor_init();
  world_ = raptor_world_instance();
}


Raptor::~Raptor()
{
  if (world_ != NULL) {
    raptor_free_world(world_);
    world_ = NULL;
  }
}


const std::string Raptor::getShortCopyrightString() const
{
  return raptor_short_copyright_string;
}

const std::string Raptor::getCopyrightString() const
{
  return raptor_copyright_string;
}

const std::string Raptor::getVersionString() const
{
  return raptor_version_string;
}

const int Raptor::getVersionMajor() const
{
  return raptor_version_major;
}

const int Raptor::getVersionMinor() const
{
  return raptor_version_minor;
}

const int Raptor::getVersionRelease() const
{
  return raptor_version_release;
}

const int Raptor::getVersionDecimal() const
{
  return raptor_version_decimal;
}

const std::string Raptor::getLicenseString() const
{
  return raptor_license_string;
}

const std::string Raptor::getHomeUrlString() const
{
  return raptor_home_url_string;
}


raptor_world* Raptor::getWorld()
{
  return world_;
}


RaptorParserDescriptor Raptor::getParserDescriptor(const unsigned int counter) throw(RaptorException)
{
  const char* name_p = NULL;
  const char* label_p = NULL;
  const char* mime_type_p = NULL;
  const unsigned char* uri_string_p = NULL;
  int rc = raptor_syntaxes_enumerate_v2(world_, counter, &name_p, &label_p,
                                        &mime_type_p, &uri_string_p);
  if (rc)
    throw RaptorException("No such parser with counter");

  std::string name;
  std::string label;
  std::string mime_type;
  std::string uri_string;
  if (name_p != NULL)
    name = name_p;
  if (label_p != NULL)
    label = label_p;
  if (mime_type_p != NULL)
    mime_type = mime_type_p;
  if (uri_string_p != NULL)
    uri_string = (const char*)uri_string_p;

  RaptorParserDescriptor d(name, label, mime_type, uri_string);
  
  return d;
}


std::vector<RaptorParserDescriptor> Raptor::getParserDescriptors() 
{
  std::vector<RaptorParserDescriptor> v;
  int i = 0;
  
  while (true) {
    try {
      RaptorParserDescriptor d = getParserDescriptor(i++);
      // Always adds in constant time
      v.push_back(d);
    }
    catch (RaptorException& e) {
      break;
    }
  }

  return v;
}


bool Raptor::isParserName(const std::string name) 
{
  return (raptor_syntax_name_check_v2(world_, name.c_str()) != 0);
}


const std::string guessParserName(RaptorUri& uri,
                                  const std::string mime_type,
                                  const std::string buffer,
                                  const std::string identifier)
{
  const char* mime_type_c = NULL;
  if(mime_type.length() > 0)
    mime_type_c = mime_type.c_str();
  
  const unsigned char* buffer_c = NULL;
  size_t buffer_len_c=0;
  if(buffer.length() > 0) {
    buffer_c = (const unsigned char*)buffer.c_str();
    buffer_len_c = buffer.length();
  }
  const unsigned char* identifier_c = NULL;
  if(identifier.length() > 0)
    identifier_c = (const unsigned char*)identifier.c_str();

  return raptor_guess_parser_name(uri.getUri(), mime_type_c,
                                  buffer_c, buffer_len_c, identifier_c);
}

RaptorUri Raptor::newUri(const std::string str)
{
  return RaptorUri::RaptorUri(this, str);
}

RaptorParser Raptor::newParser(const std::string name)
{
  return RaptorParser::RaptorParser(this, name);
}
