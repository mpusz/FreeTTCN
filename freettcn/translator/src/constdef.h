#ifndef CONSTDEF_H
#define CONSTDEF_H

#include "module.h"

namespace TTCN3 {
  
  /**
   * @brief TTCN-3 Const Definition Node.
   * 
   * Class contains all information about TTCN-3 Const Definition.
   */
  class CConstDef : public CModule::CDefinition {
  public:
    CConstDef(CFile &f, const YYLTYPE &loc, CIdentifier &id, CModule &mod);
    ~CConstDef();
  };
  
  
}

#endif /* CONSTDEF_H */
