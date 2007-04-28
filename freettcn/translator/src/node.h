#ifndef NODE_H
#define NODE_H

#include <string>
#include <list>
#include "types.h"
#include "grammar.tab.h"
#include "exception.h"
#include "file.h"

namespace TTCN3 {
  

  /**
   * @brief TTCN-3 Base Node.
   *
   * Base class for all nodes of the TTCN-3 compiler. One
   * node is one leaf in compiler tree.
   */
  class CNode {
    CFile &file;
    const YYLTYPE location;
  public:
    static unsigned long int refNum;              /**< @brief Counter for detecting not deleted nodes. */
    
    CNode(CFile &f, const YYLTYPE &loc);
    virtual ~CNode();
    
    CFile &File() const { return file; }          /**< @brief Returns a file (TTCN-3 module) in which a node is defined. */
    const YYLTYPE &Location() const { return location; } /**< @brief Returns a location of a node in TTCN-3 module. */
    
    virtual void DumpTTCN3(FILE *fdout) const = 0; /**< @brief Dump class contents into TTCN-3 source code. */
    virtual void DumpCPP(FILE *fdout) const = 0;  /**< @brief Dump class contents into C++ source code. */
  };
  
}

#endif /* NODE_H */
