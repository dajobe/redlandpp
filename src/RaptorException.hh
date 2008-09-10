#ifndef RAPTOREXCEPTION_H
#define RAPTOREXCEPTION_H

#include <stdexcept>

class RaptorException : std::exception
{
public:
  RaptorException(std::string message);

  ~RaptorException() throw();

  const char* what() const throw();

private:
  std::string message_;
};

#endif
