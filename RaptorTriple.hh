#ifndef RAPTORTRIPLE_HH
#define RAPTORTRIPLE_HH

#include <string>

class RaptorNode
{
public:
  const std::string str();

private:
  virtual std::string makeStr() = 0;
  std::string str_;

friend std::ostream& operator<< (std::ostream& os, const RaptorNode& node);
};


class RaptorLiteralNode: public RaptorNode
{
public:
  std::string value;
  std::string language;
  RaptorUri* datatype;

  RaptorLiteralNode(std::string value, std::string language, RaptorUri* datatype=NULL);

  std::string makeStr();
};

  
class RaptorUriNode: public RaptorNode 
{
public:
  RaptorUri* value;

  RaptorUriNode(RaptorUri* value);

  std::string makeStr();
};
  

class RaptorBlankNode: public RaptorNode 
{
public:
  std::string id;

  RaptorBlankNode(const char* id);

  std::string makeStr();
};
  

class RaptorTriple
{
public:
  RaptorNode* subject;
  RaptorNode* predicate;
  RaptorNode* object;
  RaptorNode* context;

private:
  RaptorTriple();
  RaptorTriple(Raptor* r, const raptor_statement*);

friend std::ostream& operator<< (std::ostream& os, const RaptorTriple& triple);
friend void parseStatementHandler(void *user_data, const raptor_statement *statement);
};

#endif
