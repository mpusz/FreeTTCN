#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include "node.h"

namespace TTCN3 {
  
  /**
   * @brief TTCN-3 Identifier Node.
   *
   * Class contains all information about TTCN-3 Identifier
   * (it stores names of variables, structs, functions, etc.).
   */
  class CIdentifier : public CNode {
    const std::string name;
    yytokentype type;
    
  public:
    CIdentifier(CFile &f, const YYLTYPE &loc, const std::string &nameStr);
    ~CIdentifier();
    
    const std::string &Name() const { return name; } /**< @brief Returns a name of the identifier. */
    
    void Type(const unsigned int t);
    yytokentype Type() const { return type; }     /**< @brief Returns a type of the identifier. */
    
    void DumpTTCN3(FILE *fdout) const;
    void DumpCPP(FILE *fdout) const;
  };


  /**
   * @brief TTCN-3 Named Node.
   *
   * Class that handles all compiler nodes that have names.
   * It contains an identifier that is automatically inserted
   * into current namespace.
   */
  class CNamedNode : public CNode {
    CIdentifier &identifier;
  public:
    CNamedNode(CFile &f, const YYLTYPE &loc, CIdentifier &id);
    ~CNamedNode();
    
    const std::string &Name() const { return identifier.Name(); } /**< @brief Returns a name of the identifier. */
  };

}

#endif /* IDENTIFIER_H */
