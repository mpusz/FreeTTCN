#ifndef WITHSTATEMENT_H
#define WITHSTATEMENT_H

#include "node.h"

namespace TTCN3 {
  
  /**
   * @brief TTCN-3 With Statement Definition Node.
   *
   * Class contains all information about TTCN-3 With Statement Definition.
   */
  class CWithStatement : public CNode {
  public:
    CWithStatement(CFile &f, const YYLTYPE &loc);
    ~CWithStatement();
  };
  
}

#endif /* WITHSTATEMENT_H */
