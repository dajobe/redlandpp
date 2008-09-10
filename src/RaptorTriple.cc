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


RaptorLiteralNode::RaptorLiteralNode(std::string nvalue, std::string nlanguage, RaptorUri* ndatatype) : value(nvalue), language(nlanguage), datatype(ndatatype)
{
}


std::string RaptorLiteralNode::makeStr()
{
  std::string s = "\"" + value + "\"";
  if(language.length() > 0)
    s.append("@" + language);
  if(datatype != NULL)
    s.append("^^<" + datatype->str() + ">");

  return s;
}


RaptorUriNode::RaptorUriNode(RaptorUri* nvalue) : value(nvalue)
{
}


std::string RaptorUriNode::makeStr()
{
  return "<" + value->str() + ">";
}


RaptorBlankNode::RaptorBlankNode(const char* nid) : id(nid)
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
  RaptorNode* node=NULL;
  
  switch(type) {
    case RAPTOR_IDENTIFIER_TYPE_RESOURCE:
      {
        RaptorUri* uri=new RaptorUri(r, (raptor_uri*)object);
        node=new RaptorUriNode(uri);
      }
      break;
      
    case RAPTOR_IDENTIFIER_TYPE_ANONYMOUS:
      node=new RaptorBlankNode((const char*)object);
      break;
      
    case RAPTOR_IDENTIFIER_TYPE_LITERAL:
      {
        RaptorUri* datatype_uri=NULL;
        if(datatype != NULL)
          datatype_uri=new RaptorUri(r, datatype);
        std::string language_str;
        if(language != NULL)
          language_str=(const char*)language;

        node=new RaptorLiteralNode((const char*)object,
                                   language_str, datatype_uri);
      }
      break;
      
    case RAPTOR_IDENTIFIER_TYPE_UNKNOWN:
    case RAPTOR_IDENTIFIER_TYPE_PREDICATE:
    case RAPTOR_IDENTIFIER_TYPE_ORDINAL:
    case RAPTOR_IDENTIFIER_TYPE_XML_LITERAL:
    default:
      break;
  }

  return node;
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
