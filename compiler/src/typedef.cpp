#include "typedef.h"

using namespace TTCN3;



/** 
 * @brief CTypeDef class constructor.
 * 
 * @param f TTCN-3 module file.
 * @param loc The location of a compiler node in a TTCN-3 source file.
 * @param id TTCN-3 node identifier.
 * @param mod TTCN-3 module in witch altstep is defined.
 */
TTCN3::CTypeDef::CTypeDef(CFile &f, const YYLTYPE &loc, CIdentifier &id, CModule &mod):
  CDefinition(f, loc, id, mod)
{
}


/**
 * @brief CTypeDef class destructor.
 */
TTCN3::CTypeDef::~CTypeDef()
{
}
