#include <RaptorException.hh>
#include <RaptorWorld.hh>
#include <RaptorUri.hh>

// RaptorUri class

RaptorUri::RaptorUri(Raptor* r, const std::string str) throw(RaptorException)
{
  raptor_ = r;
  uri_ = raptor_new_uri_v2(raptor_->getWorld(),
                           (const unsigned char*)str.c_str());
  if(uri_ == NULL)
    throw RaptorException("Failed to create uri " + str);
}

RaptorUri::RaptorUri(Raptor* r, raptor_uri* uri) throw(RaptorException)
{
  raptor_ = r;
  uri_ = raptor_uri_copy_v2(raptor_->getWorld(), uri);
  if(uri_ == NULL)
    throw RaptorException("Failed to create uri from uri");
}


RaptorUri::~RaptorUri()
{
  if (uri_) {
    raptor_free_uri_v2(raptor_->getWorld(), uri_); uri_ =NULL; 
  }
  raptor_ = NULL;
}


raptor_uri* RaptorUri::getUri() const
{
  return uri_;
}
  

const std::string RaptorUri::str() const
{
  return (const char*)raptor_uri_as_string_v2(raptor_->getWorld(), uri_);
}


std::ostream& operator<< (std::ostream& os, const RaptorUri& uri)
{
  std::string s;
  s = (char*)raptor_uri_as_string_v2(uri.raptor_->getWorld(), uri.uri_);
  return os << s;
}
