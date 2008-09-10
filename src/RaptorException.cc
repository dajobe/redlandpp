#include <RaptorException.hh>

// RaptorException class

RaptorException::RaptorException(std::string message)
{
  message_ = message;
}
  

RaptorException::~RaptorException() throw()
{
}
  

const char* RaptorException::what() const throw()
{
  return message_.c_str();
}
