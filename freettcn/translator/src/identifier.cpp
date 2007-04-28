#include "identifier.h"
#include "tools.h"

using namespace TTCN3;



/** 
 * @brief CIdentifier class constructor.
 * 
 * @param f TTCN-3 module file.
 * @param loc The location of a compiler node in a TTCN-3 source file.
 * @param nameStr TTCN-3 identifier name string.
 */
TTCN3::CIdentifier::CIdentifier(CFile &f, const YYLTYPE &loc, const std::string &nameStr):
  CNode(f, loc), name(nameStr), type(static_cast<yytokentype>(T_ID))
{
  /// @todo To be removed
  printf("Creating identifier: %s\n", Name().c_str());
}

/**
 * @brief CIdentifier class destructor.
 */
TTCN3::CIdentifier::~CIdentifier()
{
  /// @todo To be removed
  printf("Destroying identifier: %s\n", Name().c_str());
}


/**
 * @brief Set type of the identifier.
 *
 * Function sets given identifier type and checks in current namespace if
 * it is not an identifier redeclaration.
 * 
 * @param t Type of identifier to set.
 */
void TTCN3::CIdentifier::Type(const unsigned int t)
{
  // check if it is a redeclaration of already
  // assigned typed identifier
  if (type != T_ID) {
    const YYLTYPE &initLoc = Location();
//     const YYLTYPE &loc = Location();
    char buf[128];
    
    sprintf(buf, "'%s' redefined", Name().c_str());
    yyerror(&initLoc, File(), buf);
    yyerror(&initLoc, File(), "First defined here");
  }
  else {
    type = static_cast<yytokentype>(t);
  }
}

/** 
 * @brief Dump class contents into TTCN-3 source code.
 *
 * Method is used to dump TTCN-3 source code to a file based on information
 * tree described by classes in memory.
 * 
 * @param fdout File descriptor to use.
 */
void TTCN3::CIdentifier::DumpTTCN3(FILE *fdout) const
{
  fprintf(fdout, "ID: %s\n", Name().c_str());
}

/** 
 * @brief Dump class contents into C++ source code.
 *
 * Method is used to translate TTCN-3 source code loaded into memory to
 * a file with C++ code.
 * 
 * @param fdout File descriptor to use.
 */
void TTCN3::CIdentifier::DumpCPP(FILE *fdout) const
{
}



/** 
 * @brief CNamedNode class constructor.
 * 
 * @param f TTCN-3 module file.
 * @param loc The location of a compiler node in a TTCN-3 source file.
 * @param id TTCN-3 node identifier.
 */
TTCN3::CNamedNode::CNamedNode(CFile &f, const YYLTYPE &loc, CIdentifier &id):
  CNode(f, loc), identifier(id)
{
  printf("Creating node: %s\n", Name().c_str());
}

/**
 * @brief CNamedNode class destructor.
 */
TTCN3::CNamedNode::~CNamedNode()
{
  printf("Destroying node: %s\n", Name().c_str());
  
  delete &identifier;
}

