#include <RaptorException.hh>
#include <RaptorWorld.hh>
#include <RaptorUri.hh>
#include <RaptorTriple.hh>

// RaptorNode and subclasses. RaptorTriple

std::ostream& operator<< (std::ostream& os, const RaptorNode& node)
{
  return os << node.str_;
}


const std::string RaptorNode::str()
{
  str_ = makeStr();
  return str_;
}


RaptorLiteralNode::RaptorLiteralNode(std::string value, std::string language, RaptorUri* datatype) : value(value), language(language), datatype(datatype)
{
}


std::string RaptorLiteralNode::makeStr()
{
  std::string str = "\"" + value + "\"";
  if(language.length() > 0)
    str.append("@" + language);
  if(datatype != NULL)
    str.append("^^<" + datatype->str() + ">");

  return str;
}


RaptorUriNode::RaptorUriNode(RaptorUri* value) : value(value)
{
}


std::string RaptorUriNode::makeStr()
{
  return "<" + value->str() + ">";
}


RaptorBlankNode::RaptorBlankNode(const char* id) : id(id)
{
}


std::string RaptorBlankNode::makeStr()
{
  return "_:" + id;
}


RaptorNode* identifier_to_node(Raptor* r,
                               const void* object,
                               raptor_identifier_type type,
                               raptor_uri *datatype,
                               const unsigned char *language)
{
  switch(type) {
    case RAPTOR_IDENTIFIER_TYPE_RESOURCE:
      RaptorUri* uri=new RaptorUri(r, (raptor_uri*)object);
      return new RaptorUriNode(uri);
      break;
      
    case RAPTOR_IDENTIFIER_TYPE_ANONYMOUS:
      return new RaptorBlankNode((const char*)object);
      break;
      
    case RAPTOR_IDENTIFIER_TYPE_LITERAL:
    {
      RaptorUri* datatype_uri=NULL;
      if(datatype != NULL)
        datatype_uri=new RaptorUri(r, datatype);
      std::string language_str;
      if(language != NULL)
        language_str=(const char*)language;

      return new RaptorLiteralNode((const char*)object,
                                   language_str, datatype_uri);
    }
      break;
      
    default:
      break;
  }
}


RaptorTriple::RaptorTriple(Raptor* r, const raptor_statement* statement)
{
  subject=identifier_to_node(r, statement->subject,
                             statement->subject_type,
                             NULL, NULL);
  predicate=identifier_to_node(r, statement->predicate, 
                               RAPTOR_IDENTIFIER_TYPE_RESOURCE,
                               NULL, NULL);
  object=identifier_to_node(r, statement->object,
                            statement->object_type,
                            statement->object_literal_datatype,
                            statement->object_literal_language);
}


std::ostream& operator<< (std::ostream& os, const RaptorTriple& triple)
{
  return os << "["  << triple.subject->str()
            << ", " << triple.predicate->str()
            << ", " << triple.object->str()
            << "]";
}
