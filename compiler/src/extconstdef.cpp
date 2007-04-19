#include "extconstdef.h"

using namespace TTCN3;



/** 
 * @brief CExtConstDef class constructor.
 * 
 * @param f TTCN-3 module file.
 * @param loc The location of a compiler node in a TTCN-3 source file.
 * @param id TTCN-3 node identifier.
 * @param mod TTCN-3 module in witch altstep is defined.
 */
TTCN3::CExtConstDef::CExtConstDef(CFile &f, const YYLTYPE &loc, CIdentifier &id, CModule &mod):
  CDefinition(f, loc, id, mod)
{
}


/**
 * @brief CExtConstDef class destructor.
 */
TTCN3::CExtConstDef::~CExtConstDef()
{
}
