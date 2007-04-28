#ifndef GROUPDEF_H
#define GROUPDEF_H

#include "module.h"

namespace TTCN3 {
  
  /**
   * @brief TTCN-3 Group Definition Node.
   *
   * Class contains all information about TTCN-3 Group Definition.
   */
  class CGroupDef : public CModule::CDefinition {
  public:
    CGroupDef(CFile &f, const YYLTYPE &loc, CIdentifier &id, CModule &mod);
    ~CGroupDef();
  };
  
  
}

#endif /* GROUPDEF_H */
