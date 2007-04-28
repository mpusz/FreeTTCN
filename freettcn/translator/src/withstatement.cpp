#include "withstatement.h"

using namespace TTCN3;



/** 
 * @brief CWithStatement class constructor.
 * 
 * @param f TTCN-3 module file.
 * @param loc The location of a compiler node in a TTCN-3 source file.
 */
TTCN3::CWithStatement::CWithStatement(CFile &f, const YYLTYPE &loc):
  CNode(f, loc)
{
}


/**
 * @brief CWithStatement class destructor.
 */
TTCN3::CWithStatement::~CWithStatement()
{
}
