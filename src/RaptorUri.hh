#ifndef RAPTORURI_HH
#define RAPTORURI_HH

#include <string>
#include <ostream>

#include <raptor.h>

class Raptor;

// Raptor URI class

class RaptorUri
{
public:
  // public destructor
  ~RaptorUri();

  // public methods
  const std::string str() const;

  friend std::ostream& operator<< (std::ostream& os, const RaptorUri& uri);
  
  raptor_uri* getUri() const;
  
  RaptorUri(Raptor* r, raptor_uri* uri) throw(RaptorException);

protected:
  // protected constructor
  RaptorUri(Raptor* r, const std::string str) throw(RaptorException);

private:
  Raptor* raptor_;
  
  // C object
  raptor_uri* uri_;
  
  friend class Raptor;
};

#endif
