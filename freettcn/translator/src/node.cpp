#include "node.h"

using namespace TTCN3;



/** 
 * @brief CNode class constructor.
 * 
 * @param f TTCN-3 module file.
 * @param loc The location of a compiler node in a TTCN-3 source file.
 */
TTCN3::CNode::CNode(CFile &f, const YYLTYPE &loc):
  file(f), location(loc)
{
  refNum++;
}

/**
 * @brief CNode class destructor.
 */
TTCN3::CNode::~CNode()
{
  refNum--;
}
